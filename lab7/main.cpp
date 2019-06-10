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
    "B1   CCCC                         B              BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "B E E E E  E  O                   B              B                                                      B",
    "BSSSSSSSSSSSGG    LL              B       B      B                                                      B",
    "B                                 BOE E O B      B                                                      B",
    "B                                 BSBBSB  BBBB   B                                                      B",
    "B    CC                           B       BBBBB  B          O E  O    O  E    O   E   EO  E    E  OE   4B",
    "B                                 B OE E  B       BBBBMMBBBBGGBBGGBBGGBBGGBBGGBBGGBBGGBBGGBBGGBBGGBBGGBBB",
    "B                 GG              B  BSBSBB              BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                 B       B             3BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B          C                      BOE E O B      BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                 BSBSBS  B      MMMMMMMMMMMMMMMMMMMMMMMMBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                     CCC                 B      MMMMMMMMMMMMMMMMMMMMMMMMBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B            GG                     OE E  B      BBBBBBBBBBBBBBBBBBBBBBMMBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B                                    BSBSBB      BBBBBBBBBBBBBBBBBBBBBBMMBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    "B     CCC           GGBBBBBBBBBBBBBB      BBBBBBB             B                                         B",
    "B                                                             B                                         B",
    "B            GGB                    CC                        B                                         B",
    "B                                                             B                                         B",
    "B                                                             B                            BBBBBBBBBBBBBB",
    "BBBBBBA                                                       B                                         B",
    "B                                                             B                                         B",
    "BF8765                         O                   O          B                                         B",
    "BBBBWWBBBBBBBBGGBBLLBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBGGGBBBBBBBBBBLLLBBBBBBBBBBBBBGGBBBBBBBBBBBB  B",
    "BWWWWWWWLWWWWWWWLWWWWWWWWWWWWWLWWLWWWWWLWWLWWWWWWWWWWWWWWWWWWLWWWWWWLWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWLWWWWWWWLWWWWWWWWWWWWWLWWWWWWWLWWWWWWWWWWWWWWWWWWWWWWLWWWWWWLWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWB",
    "BWWWWWWWLWWWLWWWLWWWWWLLLLWWWLWWWWWWWWLWWWWWWWWWWWWWWWLLLLLWWLWWLWWWLWWWWWWWWWWWLLWWWWWLLWWWWWLLWWWWWWWWB",
    "BWWWWLWWLWWWLWWWLWWWWWLWWWLWWLWWWWWWWWLWWWWWWWWWWWWWWWLWWWWWWLWWLWWWLWWWWWWWWWWLWWLWWWLWWLWWWLWWLWWWWWWWB",
    "BWWWWLWWLWWWLWWWLWWWWWLWWWLWWLLLWWLLWWLWWLLLWWWWWWWWWWLWWWWWWLWWLWWWLWWWWWWWWWWWWLWWWWWWWLWWWWWLWWWWWWWWB",
    "BWWWWLWWLWWWLWWWLWWWWWLWWWLWWLWWWWWLWWLWWWLWWWWWWWWWWWLWWWWWWLWWLWWWLWWWWWWWWWWWWLWWWWWWLWWWWWWLWWWWWWWWB",
    "B2WWWLWWWWWWLWWWWWWWWWLWWWLWWWWWWWWLWWWWWWWLWWWWWWWWWWLWWWLLLLWWLWWWWWWWWWWWWWWWWWWWWWWWLWWWWWWWWWWWWWWWB",
    "BWWWWLWWWWWWLWWWWWWWWWLLLLWWWWWWWWWLWWWWWWWLWWWWWWWWWWLWWWWWWWWWLWWWWWWWWWWWWWWWWLWWWWWWWWWWWWWLWWWWWWWWB",
    "BWWWWLWWWWWWLWWWWWWWWWWWWWWWWWWWWWWLWWWWWWWWWWWWWWWWWWLWWWWWWWWWLWWWWWWWWWWWWWWWWWWWWWWWLWWWWWWWWWWWWWWWB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLWWWWWWWWWLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB",
    "BLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLB"
};

class PLAYER
{
public:
    float dx, dy;
    float limit_x = 0.2;
    float limit_y = 0.2;
    FloatRect rect;
    bool onGround, isAlive;
    Sprite sprite;
    float currentFrame;
    int lives = 3;
    bool win = false, is_secret = false;

    bool blue_key=false, red_key=false, yellow_key=false, green_key=false;

    double slow = 1;
    double slow_water = 1;

    PLAYER(Texture &image)
    {
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(0, 0, 75, 96));
        rect = FloatRect(70*6,22*70, 75, 96);

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
        if(module(dy)>limit_y && slow_water!=1)
        {
            if(dy>0 && dy>limit_y) dy = limit_y;
            else if(dy<0 && dy<(-2*limit_y)) dy = -2*limit_y;
        }
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
        {
            for(int j=rect.left/70; j<(rect.left+rect.width)/70; j++)
            {
                if(TileMap[i][j]=='G')
                {
                    if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}
                    if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=-0.65;   onGround=true;}
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
                    if (dx>0 && num==0){ rect.left =  j*70 -  rect.width; }
                    if (dx<0 && num==0){ rect.left =  j*70 + 70;}

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
                else if(TileMap[i][j]=='1')
                {
                    blue_key = true;
                    TileMap[i][j] = ' ';
                }
                else if(TileMap[i][j]=='2')
                {
                    red_key = true;
                    TileMap[i][j] = 'W';
                }
                else if(TileMap[i][j]=='3')
                {
                    yellow_key = true;
                    TileMap[i][j] = ' ';
                }
                else if(TileMap[i][j]=='4')
                {
                    green_key = true;
                    TileMap[i][j] = ' ';
                }
                else if(TileMap[i][j]=='5')
                {
                    if(blue_key)
                    {
                        TileMap[i][j] = ' ';
                        blue_key = false;
                    }
                    else
                    {
                        if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=0;   onGround=true;}
                        if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}
                        if (dx>0 && num==0){ rect.left =  j*70 -  rect.width; }
                        if (dx<0 && num==0){ rect.left =  j*70 + 70;}
                    }
                }
                else if(TileMap[i][j]=='6')
                {
                    if(red_key)
                    {
                        TileMap[i][j] = ' ';
                        red_key = false;
                    }
                    else
                    {
                        if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=0;   onGround=true;}
                        if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}
                        if (dx>0 && num==0){ rect.left =  j*70 -  rect.width; }
                        if (dx<0 && num==0){ rect.left =  j*70 + 70;}
                    }
                }
                else if(TileMap[i][j]=='7')
                {
                    if(yellow_key)
                    {
                        TileMap[i][j] = ' ';
                        yellow_key = false;
                    }
                    else
                    {
                        if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=0;   onGround=true;}
                        if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}
                        if (dx>0 && num==0){ rect.left =  j*70 -  rect.width; }
                        if (dx<0 && num==0){ rect.left =  j*70 + 70;}
                    }
                }
                else if(TileMap[i][j]=='8')
                {
                    if(green_key)
                    {
                        TileMap[i][j] = ' ';
                        green_key = false;
                    }
                    else
                    {
                        if (dy>0 && num==1){ rect.top =   i*70 -  rect.height;  dy=0;   onGround=true;}
                        if (dy<0 && num==1){ rect.top = i*70 + 70;   dy=0;}
                        if (dx>0 && num==0){ rect.left =  j*70 -  rect.width; }
                        if (dx<0 && num==0){ rect.left =  j*70 + 70;}
                    }
                }
                else if(TileMap[i][j]=='F')
                {
                    win = true;
                }
                else if(TileMap[i][j]=='M')
                {
                    is_secret = true;
                    TileMap[i][j] = ' ';
                }
                else if(TileMap[i][j]==' ')
                {
                    slow_water = 1;
                }
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

        dx=0.15;
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
    Font font;
    font.loadFromFile("font.ttf");
    Text text("YOU DEFEAT\n Press Tab", font, 50);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    Texture t;
    t.loadFromFile("walk0001.png");

    Texture Live;
    Live.loadFromFile("coin_bronze.png");
    Sprite live(Live);

    PLAYER hero(t);

    Texture enemy_walk;
    enemy_walk.loadFromFile("slime_normal.png");
    std::vector<ENEMY> enemies(1);
    enemies[0].set(enemy_walk, 34*70, 22*70+70-28);


    RenderWindow window(VideoMode(1330, 700), "Test");

    Clock clock;

    Texture Blue;
    Blue.loadFromFile("key_blue.png");
    Sprite blue(Blue);

    Texture Lock_b;
    Lock_b.loadFromFile("lock_blue.png");
    Sprite lock_b(Lock_b);

    Texture Red;
    Red.loadFromFile("key_red.png");
    Sprite red(Red);

    Texture Lock_r;
    Lock_r.loadFromFile("lock_red.png");
    Sprite lock_r(Lock_r);

    Texture Green;
    Green.loadFromFile("key_green.png");
    Sprite green(Green);

    Texture Lock_g;
    Lock_g.loadFromFile("lock_green.png");
    Sprite lock_g(Lock_g);

    Texture Yellow;
    Yellow.loadFromFile("key_yellow.png");
    Sprite yellow(Yellow);

    Texture Lock_y;
    Lock_y.loadFromFile("lock_yellow.png");
    Sprite lock_y(Lock_y);


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

    Texture Lava;
    Lava.loadFromFile("lava.png");
    Sprite lava(Lava);

    Texture Water;
    Water.loadFromFile("water.png");
    Sprite water(Water);

    int time_hero = 0;
    bool direct;
    while(window.isOpen())
    {
        if(hero.win)
        {
            window.clear();
            Font font;
            font.loadFromFile("font.ttf");
            Text text("YOU WIN\n Press Esc", font, 50);
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            text.setPosition(70*4, 70*3);
            window.draw(text);
            window.display();
            while(!Keyboard::isKeyPressed(Keyboard::Escape));
            return 0;
        }
        if(hero.lives <= 0)
        {
            text.setPosition(70*6, 70*4);
            window.clear();
            window.draw(text);
            window.display();
            while(!Keyboard::isKeyPressed(Keyboard::Tab));
            return 0;
        }

        if(time_hero) time_hero++;
        if(time_hero>100)
        {
            time_hero = 0;
            hero.sprite.setColor(Color::White);
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
            if(hero.onGround) {hero.dy=-0.50; hero.onGround = false;}
            else if(hero.slow_water!=1)
            {
               // if(hero.dy>0) hero.dy = 0;
                hero.dy-=0.02;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) // Boost speed of falling
        {
            if(!hero.onGround) {hero.dy+=0.005;}
            else if(hero.slow_water!=1) {hero.dy+=0.003;}
        }


        hero.update(time, direct);
        for(auto& enemy:enemies) enemy.update(time);

        text.setPosition(35*3, 0);//задаем позицию текста, центр камеры
		window.draw(text);


    window.clear();

    for(int i=0; i<H; i++)
    {
        for(int j=0; j<W; j++)
            {
                if(TileMap[i][j]=='B' || TileMap[i][j]=='M')
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
                else if(TileMap[i][j]=='1')
                {
                    blue.setTextureRect(IntRect(0, 0, 60, 37));
                    blue.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(blue);
                }
                else if(TileMap[i][j]=='2')
                {
                    red.setTextureRect(IntRect(0, 0, 70, 70));
                    red.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(red);
                }
                else if(TileMap[i][j]=='3')
                {
                    yellow.setTextureRect(IntRect(0, 0, 60, 37));
                    yellow.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(yellow);
                }
                else if(TileMap[i][j]=='4')
                {
                    green.setTextureRect(IntRect(0, 0, 70, 70));
                    green.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(green);
                }
                else if(TileMap[i][j]=='5')
                {
                    lock_b.setTextureRect(IntRect(0, 0, 70, 70));
                    lock_b.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(lock_b);
                }
                else if(TileMap[i][j]=='6')
                {
                    lock_r.setTextureRect(IntRect(0, 0, 70, 70));
                    lock_r.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(lock_r);
                }
                else if(TileMap[i][j]=='7')
                {
                    lock_y.setTextureRect(IntRect(0, 0, 70, 70));
                    lock_y.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(lock_y);
                }
                else if(TileMap[i][j]=='8')
                {
                    lock_g.setTextureRect(IntRect(0, 0, 70, 70));
                    lock_g.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(lock_g);
                }
                else if(TileMap[i][j]=='E')
                {
                    ENEMY new_enemy;
                    new_enemy.set(enemy_walk, j*70-offsetX, i*70 - offsetY+42);
                    enemies.push_back(new_enemy);
                    TileMap[i][j] = ' ';
                }
                else if(TileMap[i][j]=='F')
                {
                    Font font;
                    font.loadFromFile("font.ttf");
                    Text finish("FINISH", font, 20);
                    finish.setStyle(sf::Text::Bold | sf::Text::Underlined);
                    finish.setPosition(j*70 - offsetX, i*70 - offsetY);
                    window.draw(finish);
                }
                else if(TileMap[i][j]=='A')
                {
                    Font font;
                    font.loadFromFile("font.ttf");
                    Text start("GO TO FINISH\n it's on the left\n (find keys to open locks)", font, 15);
                    start.setStyle(sf::Text::Bold | sf::Text::Underlined);
                    start.setPosition(j*70 - offsetX, i*70 -offsetY);
                    window.draw(start);
                }
            }
    }

        if (hero.rect.left>300)
        {
            offsetX = hero.rect.left-300;
        }

        offsetY = hero.rect.top-300;

        for(int i=0; i<enemies.size(); i++)
        {
            if(hero.rect.intersects(enemies[i].rect))
            {
                if(hero.dy>0)
                {
                    enemies.erase(enemies.begin()+i);
                }
                else if(time_hero == 0)
                {
                    hero.sprite.setColor(Color::Red);
                    hero.lives--;
                    time_hero = 1;
                }
                break;
            }
        }
        window.draw(hero.sprite); // draw hero

        for(int i=0; i<hero.lives; i++)
        {
            live.setPosition(i*35, 0);
            window.draw(live);
        }

        if(hero.blue_key)
        {
            RectangleShape rectangle(Vector2f(6, 6));
            rectangle.setFillColor(Color::Blue);
            rectangle.setPosition(hero.rect.left - offsetX, hero.rect.top - offsetY-10);
            window.draw(rectangle);
        }

        if(hero.red_key)
        {
            RectangleShape rectangle(Vector2f(6, 6));
            rectangle.setFillColor(Color::Red);
            rectangle.setPosition(hero.rect.left+9-offsetX, hero.rect.top - offsetY-10);
            window.draw(rectangle);
        }

        if(hero.yellow_key)
        {
            RectangleShape rectangle(Vector2f(6, 6));
            rectangle.setFillColor(Color::Yellow);
            rectangle.setPosition(hero.rect.left+18-offsetX, hero.rect.top-offsetY-10);
            window.draw(rectangle);
        }

        if(hero.green_key)
        {
            RectangleShape rectangle(Vector2f(6, 6));
            rectangle.setFillColor(Color::Green);
            rectangle.setPosition(hero.rect.left+27-offsetX, hero.rect.top-offsetY-10);
            window.draw(rectangle);
        }

        for(const auto& enemy:enemies) window.draw(enemy.sprite);
        window.display();
    }
    return 0;
}
