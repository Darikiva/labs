#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace sf;

int ground = 400;

std::string TileMape =
{
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
};

std::string Bonuses(TileMape.length(), ' ');

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

        sprite.setPosition(rect.left, rect.top);
        if(rect.left>1000||rect.left<0) dx = -dx;
        if(dx==0) return;
        rect.left+= dx*time;

        currentFrame+=0.005*time;
        if(currentFrame>4) currentFrame-=4;

        if(dx<0) sprite.setTextureRect(IntRect(40*(int)currentFrame, 0, 32, 32));
        if(dx>0) sprite.setTextureRect(IntRect(40*(int)currentFrame+32, 0, -32, 32));
    }

    void CollisionX()
    {
        if (rect.left<0) {rect.left = 0;}
        else if(rect.left+rect.width>1000) {rect.left=1000-rect.width;}
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
        sprite.setTextureRect(IntRect(0, 27, 39, 40));
        rect = FloatRect(800,100,39,40);

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
        rect.left += dx*time;

        CollisionX(); // don't go over the limit of map
        if(!onGround) dy=dy+0.0005*time; // acceleration
        rect.top += dy*time;
        onGround = false;

        //CollisionY();

        if(rect.top > ground) {rect.top = ground; dy=0; onGround = true;}

        currentFrame += 0.005*time; // draw hero
        if(currentFrame>6) currentFrame-=6;

        if(dx>0) sprite.setTextureRect(IntRect(40*(int)currentFrame, 27, 39, 40)); // animation of
        if(dx<0) sprite.setTextureRect(IntRect(40*(int)currentFrame+38, 27, -39, 40)); // moving

        for(int i=0; i<fire_list.size(); i++)
        {
            fire_list[i].update(time);
            if(fire_list[i].rect.left>1000||fire_list[i].rect.left<0) fire_list.erase(fire_list.begin()+i); // delete fire, if it gets over the limit of map
        }

        sprite.setPosition(rect.left, rect.top);

        if(onGround) isBonus();
        if(hp<=0) isAlive = false;
        dx = 0;
    }

    void CollisionX()
    {
        if (rect.left<0) {rect.left = 0;}
        else if(rect.left+rect.width>1000) {rect.left=1000-rect.width;}
    }

    void isBonus()
    {
        for(int i=rect.left/(1000/Bonuses.length())-3; i<(rect.left+rect.width)/(1000/Bonuses.length())-4; i++)
        {
            if (Bonuses[i]=='0')
            {
                hp+=2;
                Bonuses[i] = ' ';
            }
            else if (Bonuses[i]=='1')
            {
                if(is_single_weapon) damage+=0.4;
                else damage+=0.003;
                Bonuses[i] = ' ';
            }
            else continue;
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

    PLAYER p(t, weapon);

    std::vector <ENEMY> enemy;

    RenderWindow window(VideoMode(1000, 500), "Test!");

    Texture s;
    s.loadFromFile("enemy_running.png");

    Texture attack;
    attack.loadFromFile("attack_player.png");

    RectangleShape rectangle(Vector2f(16, 16));
    RectangleShape bonus_rectangle(Vector2f(20, 20));

    Clock clock;

    float speed_fire = 0;
    float max_count = 0;
    float bonus_count = 0;
    int bonus_number;
    float max_enemy = 10;
    float enemy_hp = 10;

    int side;

    bool direct;
    while(window.isOpen())
    {
        if(!p.isAlive) // If hp<=0, you're dead
        {
            std::cout << "YOU DEFEAT";
            system("pause");
            return 0;
        }
        side = rand()%2; // Where new enemy will appear
        bonus_number = rand()%TileMape.length(); // Where new health_bonus appear

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
            p.dx = -0.1;
            direct = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) // Go right
        {
            p.dx = 0.1;
            direct = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) // Jump
        {
            if(p.onGround) {p.dy=-0.4; p.onGround = false;}
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) // Boost speed of falling
        {
            if(!p.onGround) {p.dy+=0.005;}
        }

        speed_fire+=0.005; // limit of shots number
        if (Keyboard::isKeyPressed(Keyboard::A)&&(speed_fire>=1||speed_fire==0))
        {
            ATTACK new_attack(attack, p.rect.left, p.rect.top, direct);
            p.fire_list.push_back(new_attack); // Add new shot
            speed_fire = 0;
        }

        max_count+=0.001; // time when new enemy appears
        if (max_count>=1||max_count==0)
        {
            max_enemy+=0.1; // with every 10 new enemies increase max enemies on the map at the same time
            enemy_hp+=0.1; // every new enemy has more health points
            int start_position;
            if(side==1) start_position = 0; // from which side
            else start_position = 1000; // new enemy will appear
            ENEMY new_enemy(s, start_position, ground, enemy_hp);
            if(enemy.size()<max_enemy) enemy.push_back(new_enemy);
            max_count = 0;
        }

        bonus_count+=0.0005; // new bonus in certain interval
        if(bonus_count>=1)
        {
            //int j = rand()%bonus_number;
            Bonuses[bonus_number] = '0'; // add new medicine bonus
            Bonuses[5] = '1'; // add new attack bonus
            bonus_count = 0;
        }

        p.update(time);

        window.clear();

        for(int i=0; i<TileMape.length(); i++) // draw map
                {
                    if(TileMape[i]=='B') rectangle.setFillColor(Color::Red);
                    if(TileMape[i]==' ') continue;
                    rectangle.setPosition(i*16, ground+40);
                    window.draw(rectangle);
                }

        for(int i=0; i<TileMape.length(); i++) // draw bonuses
                {
                    if(Bonuses[i]=='0')
                    {
                        bonus_rectangle.setFillColor(Color::Green);
                        bonus_rectangle.setPosition(i*16+32, ground+24);
                        window.draw(bonus_rectangle);
                    }
                    else if(Bonuses[i]=='1')
                    {
                        bonus_rectangle.setFillColor(Color::Blue);
                        bonus_rectangle.setPosition(5*16+48, ground+24);
                        window.draw(bonus_rectangle);
                    }
                    else if(Bonuses[i]==' ') continue;
                }

        for(int i=0; i<p.fire_list.size(); i++) // draw shots and check for intersections with enemies
        {
            window.draw(p.fire_list[i].sprite);
            for(int j=0; j<enemy.size(); j++)
            {
                if(p.fire_list[i].rect.intersects(enemy[j].rect))
                {
                    enemy[j].hp-=p.damage;
                    if(enemy[j].hp<=0) enemy.erase(enemy.begin()+j);
                    if(p.is_single_weapon) p.fire_list.erase(p.fire_list.begin()+i);
                }
            }
        }

        for(int i=0; i<enemy.size(); i++) // draw enemies and check for intersections with our hero
        {
            enemy[i].update(time);
            window.draw(enemy[i].sprite);
            print_hp(enemy[i], window);
            if(enemy[i].rect.intersects(p.rect))
            {
                p.hp-=0.01;
            }
        }

        window.draw(p.sprite); // draw hero
        print_hp(p, window); // draw hero's health
        window.display();
    }
    return 0;
}
