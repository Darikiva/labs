#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace sf;

float offsetX = 0, offsetY = 0;

const int ground = 320;
const int H = 20;
const int W = 105;

std::string TileMape[H] =
{
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB                                                       ",
    "B                                                B                                                       ",
    "B                                                B                                                       ",
    "B                                                B                                                       ",
    "BBBBBBBBBBB                                      B                                                       ",
    "B                                                B                                                       ",
    "B                                BBBBBBBBBBB     B                                                       ",
    "B                                                B                                                       ",
    "B                                                B                                                       ",
    "B                                                B                                                       ",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                   BBBBBBBBBB                                                                          B",
    "B                                                                                                       B",
    "B                                                                                                       B",
    "B                                                                                                       B",
    "BBBBBBBBBBB                                                                                BBBBBBBBBBBBBB",
    "B                                                                                                       B",
    "B                                                                                                       B",
    "B                                                                                                       B",
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"
};

class ENEMY{
public:
    Sprite sprite;
    bool isAlive = false;
    float dx;
    FloatRect rect;
    float currentFrame;
    float hp;

    ENEMY(Texture &image, int x, int y, float hitpoints)
    {
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(6,1,32,32));
        rect = FloatRect(x, y, 32, 32);

        isAlive = true;
        dx = 0.1;
        currentFrame = 0;
        hp = hitpoints;
    }

    void update(float time)
    {
        //dx = 0.1;
        if(rect.left<0)
        {
            dx = -dx;
            rect.left = 0;
        }
        if(rect.left+rect.width > W*16)
        {
            dx = -dx;
            rect.left = W*16 - rect.width;
        }
        if(dx==0) return;
        rect.left+= dx*time;

        currentFrame+=0.005*time;
        if(currentFrame>4) currentFrame-=4;

        if(dx<0) sprite.setTextureRect(IntRect(40*(int)currentFrame, 0, 32, 32));
        if(dx>0) sprite.setTextureRect(IntRect(40*(int)currentFrame+32, 0, -32, 32));


        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
    }

    void CollisionX()
    {
        if (rect.left<0) {rect.left = 0;}
        else if(rect.left+rect.width>W*16) {rect.left=W*16-rect.width;}

    }

};

class ATTACK{
public:
    float dx;
    Sprite sprite;
    FloatRect rect;
    ATTACK(Texture &image, int x, int y, bool direct)
    {
        sprite.setTexture(image);
        rect = FloatRect(x, y, 12, 12);

        if(direct) dx = 0.2;
        else dx = -0.2;
    }
    void update(float time)
    {
        rect.left+= dx*time;
        sprite.setPosition(rect.left, rect.top);
    }
};

class PLAYER{
public:
    float dx, dy;
    FloatRect rect;
    bool onGround, isAlive;
    Sprite sprite;
    float hp;
    float damage;
    float currentFrame;
    bool is_single_weapon;
    std::vector<ATTACK> fire_list;

    PLAYER(Texture &image, bool weapon)
    {
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(0, 27, 40, 40));
        rect = FloatRect(400,100, 40, 40);

        hp = 20;
        is_single_weapon = weapon;
        if(is_single_weapon) damage = 4;
        else damage = 0.01;
        dx=dy=0;
        currentFrame = 0;
        isAlive = true;
    }

    void update(float time)
    {
        rect.left += dx * time;
        Collision(0);


        if (!onGround) dy=dy+0.0005*time;
        rect.top += dy*time;
        onGround=false;
        Collision(1);

        currentFrame += 0.005*time; // draw hero
        if(currentFrame>6) currentFrame-=6;

        if(dx>0) sprite.setTextureRect(IntRect(40*(int)currentFrame, 27, 39, 40)); // animation of
        if(dx<0) sprite.setTextureRect(IntRect(40*(int)currentFrame+38, 27, -39, 40)); // moving

        for(int i=0; i<fire_list.size(); i++)
        {
            fire_list[i].update(time);
            if(fire_list[i].rect.left>800||fire_list[i].rect.left<0) fire_list.erase(fire_list.begin()+i); // delete fire, if it gets over the limit of map
        }

        sprite.setPosition(rect.left, rect.top);

        if(hp<=0) isAlive = false;
        dx = 0;
    }

    void Collision(int num)
    {
        for(int i=rect.top/16; i<(rect.top+rect.height)/16; i++)
            for(int j=rect.left/16; j<(rect.left+rect.width)/16; j++)
            {
                if(TileMape[i][j]=='B')
                {
                    if (dy>0 && num==1){ rect.top =   i*16 -  rect.height;  dy=0;   onGround=true; }
                    if (dy<0 && num==1){ rect.top = i*16 + 16;   dy=0;}
                    if (dx>0 && num==0){ rect.left =  j*16 -  rect.width; }
                    if (dx<0 && num==0){ rect.left =  j*16 +16;}
                }
            }
    }
};

template <typename T>
void print_hp(T person, RenderWindow& window)
{
    RectangleShape rectangle(Vector2f(2, 2));
    for(int i=0; i<person.hp; i++)
    {
        rectangle.setFillColor(Color::Red);
        rectangle.setPosition(person.rect.left+i*2, person.rect.top-person.rect.height);
        window.draw(rectangle);
    }
}

int main()
{
    std::cout << "If enemy touches you, you lose health point\n";
    std::cout << "Green blocks increase your health\n";
    std::cout << "Blue blocks increase your damage\n";
    std::cout << "Press A to attack\n";
    std::cout << "Use arrows to move\n";
    std::cout << "Do you want to have single weapon (enter 1) or not (enter 0)?";
    bool weapon;
    std::cin >> weapon;


    Texture t;
    t.loadFromFile("running.png");

    PLAYER hero(t, weapon);

   // std::vector <ENEMY> enemy;

    RenderWindow window(VideoMode(800, ground), "Test!");

    Texture s;
    s.loadFromFile("enemy_running.png");

    Texture attack;
    attack.loadFromFile("attack_player.png");

    RectangleShape rectangle(Vector2f(16, 16));

    Clock clock;

    float speed_fire = 0;
    float max_count = 0;
    int bonus_damage = 0;
    float bonus_count = 0;
    int bonus_number;
    float max_enemy = 10;
    float enemy_hp = 10;

    int side;

    bool direct;
    while(window.isOpen())
    {
        if(!hero.isAlive) // If hp<=0, you're dead
        {
            std::cout << "YOU DEFEAT";
            system("pause");
            return 0;
        }
        side = rand()%2; // Where new enemy will appear

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time/800;
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) // Go left
        {
            hero.dx = -0.1;
            direct = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) // Go right
        {
            hero.dx = 0.1;
            direct = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) // Jump
        {
            if(hero.onGround) {hero.dy=-0.4; hero.onGround = false;}
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) // Boost speed of falling
        {
            if(!hero.onGround) {hero.dy+=0.005;}
        }

        speed_fire+=0.005; // limit of shots number
        if (Keyboard::isKeyPressed(Keyboard::A)&&(speed_fire>=1||speed_fire==0))
        {
            ATTACK new_attack(attack, hero.rect.left, hero.rect.top, direct);
            hero.fire_list.push_back(new_attack); // Add new shot
            speed_fire = 0;
        }

        max_count+=0.001; // time when new enemy appears
        if (max_count>=1||max_count==0)
        {
            max_enemy+=0.1; // with every 10 new enemies increase max enemies on the map at the same time
            enemy_hp+=0.1; // every new enemy has more health points
            int start_position;
            if(side==1) start_position = 0; // from which side
            else start_position = W*16; // new enemy will appear
            //ENEMY new_enemy(s, start_position, ground-48, enemy_hp);
            //if(enemy.size()<max_enemy) enemy.push_back(new_enemy);
            max_count = 0;
        }

        hero.update(time);

        window.clear();

        for(int i=0; i<H; i++)
            for(int j=0; j<W; j++) // draw map
                {
                    if(TileMape[i][j]=='B') rectangle.setFillColor(Color::Green);
                    if(TileMape[i][j]==' ')
                    {
                        rectangle.setFillColor(Color::Black);
                    }
                    rectangle.setPosition(j*16 - offsetX, i*16);
                    window.draw(rectangle);
                }

       /* for(int i=0; i<hero.fire_list.size(); i++) // draw shots and check for intersections with enemies
        {
            window.draw(hero.fire_list[i].sprite);
            for(int j=0; j<enemy.size(); j++)
            {
                if(hero.fire_list[i].rect.intersects(enemy[j].rect))
                {
                    enemy[j].hp-=hero.damage;
                    if(enemy[j].hp<=0) enemy.erase(enemy.begin()+j);
                    if(hero.is_single_weapon) hero.fire_list.erase(hero.fire_list.begin()+i);
                }
            }
        }*/



        if (hero.rect.left>200)
        {
            offsetX = hero.rect.left-200;
            //cout << offsetX;
        }



       /* for(int i=0; i<enemy.size(); i++) // draw enemies and check for intersections with our hero
        {
            enemy[i].update(time);
            window.draw(enemy[i].sprite);
            print_hp(enemy[i], window);
            if(enemy[i].rect.intersects(hero.rect))
            {
                hero.hp-=0.01;
            }
        }*/

        window.draw(hero.sprite); // draw hero
        print_hp(hero, window); // draw hero's health
        window.display();
    }
    return 0;
}
