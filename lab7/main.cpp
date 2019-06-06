#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>

using namespace sf;

float offsetX = 0, offsetY = 0;

const int H = 38;
const int W = 105;

template <typename T>
T module(const T& number)
{
    if(number<0) return -number;
    else return number;
}

std::string TileMap[H] =
{
    "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B          CCC                                   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                     CCC                        BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                                BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B     CCC           GGBBBBBBBB                                                                          B",
    "B                                                                                                       B",
    "B            GGB                    CC                                                                  B",
    "B                                                                                                       B",
    "BBBBBBBBBGB                                                                                BBBBBBBBBBBBBB",
    "B                                                                                                       B",
    "B                                                                                                       B",
    "B                              O                   O                                                    B",
    "BBBBBBBBBBBBBBGGBBLLBB  BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBSSSBBBBBBBBBBBBGGBBBBBBBBBBBBBBB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB"
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
    float limit_x = 0.2;
    FloatRect rect;
    bool onGround, isAlive;
    Sprite sprite;
    float currentFrame;
    int lives = 3;

    double slow = 1;
    double slow_water = 1;

    PLAYER(Texture &image)
    {
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(0, 0, 75, 96));
        rect = FloatRect(70,22*70, 53, 96);

        dx=dy=0;
        currentFrame = 0;
        isAlive = true;
    }

    void update(float time, bool direct)
    {
        if(module(dx)>limit_x)
        {
            if(dx>0) dx = limit_x;
            else dx = -limit_x;
        }
        rect.left += dx * time * slow;
        Collision(0);

        if (!onGround) dy=dy+0.0005*time*slow_water;
        rect.top += dy*time*slow_water;
        onGround=false;
        Collision(1);

        currentFrame += 0.007*time; // draw hero
        if(currentFrame>11) currentFrame-=11;

        if(dx>0) sprite.setTextureRect(IntRect(75*(int)currentFrame, 0, 75, 96)); // animation of
        if(dx<0) sprite.setTextureRect(IntRect(75*(int)currentFrame+75, 0, -75, 96)); // moving

        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

        if(module(dx)<0.02)
        {
            dx = 0;
        }

        if(dx!=0)
        {
            if(dx-0.02>0)dx -= 0.02;
            else if(dx+0.02<0) dx+=0.02;
        }
    }

    void Collision(int num)
    {
        for(int i=rect.top/70; i<(rect.top+rect.height)/70; i++)
            for(int j=rect.left/70; j<(rect.left+rect.width)/70; j++)
            {
                if(TileMap[i][j]=='G')
                {
                    if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}
                    if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=-0.7;   onGround=true;}
                    if (dx>0 && num==0){ rect.left =  j*70 -  rect.width; }
                    if (dx<0 && num==0){ rect.left =  j*70 + 70;}

                    slow = 1;
                    slow_water = 1;
                    return;
                }
                else if(TileMap[i][j]=='B')
                {
                    if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=0;   onGround=true;}
                    if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}
                    if (dx>0 && num==0){ rect.left =  j*70 -  rect.width; }
                    if (dx<0 && num==0){ rect.left =  j*70 + 70;}

                    slow = 1;
                    slow_water = 1;
                }
                else if(TileMap[i][j]=='S')
                {
                    if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=0;   onGround=true;}
                    if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}

                    slow = 0.5;
                    slow_water = 1;
                }
                else if(TileMap[i][j]=='W')
                {
                    onGround = false;
                    slow_water = 0.5;
                }
                else if(TileMap[i][j]=='L')
                {
                    lives--;
                    if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=0;   onGround=true;}
                    if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}
                    if (dx>0 && num==0){ rect.left =  j*70 -  rect.width; }
                    if (dx<0 && num==0){ rect.left =  j*70 + 70;}
                }
                else if(TileMap[i][j]==' ')
                {
                    slow_water = 1;
                }
            }
    }
};

class ENEMY
{
public:
    float dx,dy;
    FloatRect rect;
    Sprite sprite;
    float currentFrame;
    bool life;


    void set(Texture &image, int x, int y)
    {
        sprite.setTexture(image);
        rect = FloatRect(x,y,43,28);

        dx=0.1;
        currentFrame = 0;
        life=true;
    }

    void update(float time)
    {
        rect.left += dx * time;

        Collision();


        currentFrame += time * 0.005;
        if (currentFrame > 2)
            currentFrame -= 2;

        if(dx>0) sprite.setTextureRect(IntRect(43*int(currentFrame)+43,   0, -43, 28));
        if(dx<0) sprite.setTextureRect(IntRect(43*int(currentFrame), 0, 43, 28));
        if (!life)
            sprite.setTextureRect(IntRect(97, 0, 60, 28));


        sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

    }


    void Collision()
    {

        for (int i = rect.top/70 ; i<(rect.top+rect.height)/70; i++)
            for (int j = rect.left/70; j<(rect.left+rect.width)/70; j++)
                if ((TileMap[i][j]=='B') || (TileMap[i][j]=='O'))
                {
                    if (dx>0)
                    {
                        rect.left =  j*70 - rect.width;
                        dx*=-1;
                    }
                    else if (dx<0)
                    {
                        rect.left =  j*70 + 70;
                        dx*=-1;
                    }

                }
    }
};

int main()
{
    Texture t;
    t.loadFromFile("walk0001.png");

    Texture Ground;
    Ground.loadFromFile("ground.png");
    Sprite ground(Ground);

    Texture Cloud;
    Cloud.loadFromFile("cloud_1.png");
    Sprite cloud(Cloud);

    Texture Cave;
    Cave.loadFromFile("ground_cave.png");
    Sprite cave(Cave);

    Texture Sand;
    Sand.loadFromFile("ground_sand.png");
    Sprite sand(Sand);

    Texture Live;
    Live.loadFromFile("coin_bronze.png");
    Sprite live(Live);

    Texture Lava;
    Lava.loadFromFile("lava.png");
    Sprite lava(Lava);

    Texture Water;
    Water.loadFromFile("water.png");
    Sprite water(Water);

    PLAYER hero(t);

    Texture enemy_walk;
    enemy_walk.loadFromFile("slime_normal.png");
    ENEMY enemy;
    enemy.set(enemy_walk, 34*70, 22*70+70-28);


    RenderWindow window(VideoMode(1330, 700), "Test");

    RectangleShape rectangle(Vector2f(70, 70));

    Clock clock;

    float speed_fire = 0;
    float max_count = 0;
    int bonus_damage = 0;
    float bonus_count = 0;
    int bonus_number;
    float max_enemy = 10;
    float enemy_hp = 10;

    int side;

    bool flag = true;

    int time_hero = 0;
    bool direct;
    while(window.isOpen())
    {
        if(!enemy.life)
            flag = false;

        for(int i=0; i<H; i++)
        {
            for(int j=0; j<W; j++)
            {
                rectangle.setFillColor(Color::Red);
                rectangle.setPosition(j*70 - offsetX, i*70 - offsetY);
                window.draw(rectangle);
            }
        }

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

       // if(time_hero>0) time_hero++;

        //if(time_hero>50000000) time_hero=0;
        time = time/800;
        Event event;
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) // Go left
        {
            hero.dx -= 0.04;
            direct = false;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) // Go right
        {
            hero.dx += 0.04;
            direct = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) // Jump
        {
            if(hero.onGround) {hero.dy=-0.45; hero.onGround = false;}
            else if(hero.slow_water!=1) {hero.dy-=0.02;}
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) // Boost speed of falling
        {
            if(!hero.onGround) {hero.dy+=0.005;}
            else if(hero.slow_water!=1) {hero.dy+=0.003;}
        }


        hero.update(time, direct);
        if(flag) enemy.update(time);

        window.clear();

        for(int i=0; i<H; i++)
            for(int j=0; j<W; j++) // draw map
                {
                    if(TileMap[i][j]=='B')
                    {
                        ground.setTextureRect(IntRect(0, 0, 70, 70));
                        ground.setPosition(j*70 - offsetX, i*70 - offsetY);
                        window.draw(ground);
                    }
                    else if(TileMap[i][j]=='C')
                    {
                        cloud.setTextureRect(IntRect(0, 0, 129, 63));
                        cloud.setPosition(j*70 - offsetX, i*70 - offsetY);
                        window.draw(cloud);
                    }
                    else if(TileMap[i][j]=='G')
                    {
                        cave.setTextureRect(IntRect(0, 0, 70, 70));
                        cave.setPosition(j*70 - offsetX, i*70 - offsetY);
                        window.draw(cave);
                    }
                    else if(TileMap[i][j]=='S')
                    {
                        sand.setTextureRect(IntRect(0, 0, 70, 70));
                        sand.setPosition(j*70 - offsetX, i*70 - offsetY);
                        window.draw(sand);
                    }
                    else if(TileMap[i][j]=='W')
                    {
                        water.setTextureRect(IntRect(0, 0, 70, 70));
                        water.setPosition(j*70 - offsetX, i*70 - offsetY);
                        window.draw(water);
                    }
                    else if(TileMap[i][j]=='L')
                    {
                        lava.setTextureRect(IntRect(0, 0, 70, 70));
                        lava.setPosition(j*70 - offsetX, i*70 - offsetY);
                        window.draw(lava);
                    }
                }


        if(flag && hero.rect.intersects(enemy.rect))
        {
            if(hero.dy>0)
            {
                enemy.life = false;
            }
            else
            {
                hero.lives--;
                hero.dy -=0.3;
            }
        }

        if (hero.rect.left>200)
        {
            offsetX = hero.rect.left-200;
        }

        offsetY = hero.rect.top-300;

        window.draw(hero.sprite); // draw hero

        for(int i=0; i<hero.lives; i++)
        {
            live.setPosition(i*35, 0);
            window.draw(live);
        }

        if(flag) window.draw(enemy.sprite);
        window.display();
    }
    return 0;
}
