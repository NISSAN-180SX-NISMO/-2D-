#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>


using namespace sf;

const int SCREEN_WIDTH = 1920, SCREEN_HEIGHT = 1080;
const float SPEED = 0.15;
unsigned int SCORE = 0;
bool ISDIE;




class Player {
public:
    float speedx, speedy;   // скорость по осям
    FloatRect rect;         // рект типа спрайт с текстурой и размеры есть еще чето там вот
    Sprite sprite;          // спрайт типа фанта
    
   
   
    Player(Texture& image) {
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(0,0,64,64));
        rect = FloatRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64);
        sprite.setPosition(rect.left, rect.top);
        speedx = 0; speedy = 0;
        
        
    }
    void update(float time) {
        rect.left += speedx * time;
        rect.top += speedy * time;
        sprite.setPosition(rect.left, rect.top);

        
      
        speedy = 0; speedx = 0;
        
    }
};

class Cores {
public:
    float speedx, speedy;   // скорость по осям
    FloatRect rect;         // рект типа спрайт с текстурой и размеры есть еще чето там вот
    Sprite sprite;          // спрайт типа фанта
    
    Texture  txt;
    Cores(Texture& image) {
        txt = image;
        bool left = rand() % 2, top = rand() % 2;
        sprite.setTexture(txt);
        sprite.setTextureRect(IntRect(0, 0, 16, 16));


        if (left) {
            if (top) {
                rect = FloatRect(rand() % SCREEN_WIDTH,0, 64, 64);
            }
            else {
                rect = FloatRect(SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 64, 64);
            }
        }
        else {
            if (top) {
                rect = FloatRect(rand() % SCREEN_WIDTH,SCREEN_HEIGHT, 64, 64);
            }
            else {
                rect = FloatRect(SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 64, 64);
            }
        }



       
        //rect = FloatRect(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2, 64, 64);


        sprite.setPosition(rect.left, rect.top);
        
        

    }
    void update(float time, Player& ball) {
        if (!ISDIE) {
            rect.left += -(rect.left - 32 - ball.rect.left) / 6000 * time;
            rect.top += -(rect.top - 32 - ball.rect.top) / 6000 * time;
        }
        else {
            speedy = 0;
            speedx = 0;
           
        }

        sprite.setPosition(rect.left, rect.top);



        

    }
    void update(float time) {
        if (!ISDIE) {
            rect.left += speedx * time;
            rect.top += speedy * time;
        }
        else {
            speedy = 0;
            speedx = 0;

        }

        sprite.setPosition(rect.left, rect.top);





    }
};

class Chest {
public:
    
    FloatRect rect;         // рект типа спрайт с текстурой и размеры есть еще чето там вот
    Sprite sprite;          // спрайт типа фанта
    bool collect;
    Chest(Texture& image) {
        collect = false;
        sprite.setTexture(image);
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
        rect = FloatRect(rand() % (SCREEN_WIDTH - 32), rand() % (SCREEN_WIDTH - 32), 32, 32);
        sprite.setPosition(rect.left, rect.top);
    }
    void update() {
        if (!collect) { sprite.setPosition(rect.left, rect.top); }
    }
};
std::vector<Chest> all_chests;
void GETCHEST(Player& ball) {
    for (int i = ball.rect.left + 10; i < (ball.rect.left + ball.rect.width) - 10; ++i) {
        for (int j = ball.rect.top + 10; j < (ball.rect.top + ball.rect.height) - 10; ++j) {
            for (auto& el : all_chests) {
                if ((int)el.rect.left + 16 == i && (int)el.rect.top + 16 == j) {
                    el.collect = true; ++SCORE;
                }
            }
        }
    }
}

std::vector<Cores> all_cores;
void BDUM(Player& ball) {
    if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))
    {
        for (int k = 3; k >= 0; --k) {
            for (int i = ball.rect.left + 11 + 8 * (3 - k); i < (ball.rect.left + ball.rect.width) - 11 - 8 * k; ++i) {
                for (int j = ball.rect.top + 11 + 8 * (3 - k); j < (ball.rect.top + ball.rect.height) - 11 - 8 * k; ++j) {
                    for (auto& el : all_cores) {
                        if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                           
                            ISDIE = true;
                        }
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))
    {
        for (int k = 3; k >= 0; --k) {
            for (int i = ball.rect.left + 11 + 8 * k; i < (ball.rect.left + ball.rect.width) - 11 - 8 * (3 - k); ++i) {
                for (int j = ball.rect.top + 11 + 8 * (3 - k); j < (ball.rect.top + ball.rect.height) - 11 - 8 * k; ++j) {
                    for (auto& el : all_cores) {
                        if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                            ISDIE = true;
                        }
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right))
    {
        for (int k = 3; k >= 0; --k) {
            for (int i = ball.rect.left + 11 + 8 * (3 - k); i < (ball.rect.left + ball.rect.width) - 11 - 8 * k; ++i) {
                for (int j = ball.rect.top + 11 + 8 * (3 - k); j < (ball.rect.top + ball.rect.height) - 11 - 8 * k; ++j) {
                    for (auto& el : all_cores) {
                        if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                             ISDIE = true;
                        }
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left))
    {
        for (int k = 3; k >= 0; --k) {
            for (int i = ball.rect.left + 11 + 8 * k; i < (ball.rect.left + ball.rect.width) - 11 - 8 * (3 - k); ++i) {
                for (int j = ball.rect.top + 11 + 8 * (3 - k); j < (ball.rect.top + ball.rect.height) - 11 - 8 * k; ++j) {
                    for (auto& el : all_cores) {
                        if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                            ISDIE = true;
                        }
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        for (int i = ball.rect.left + 18; i < (ball.rect.left + ball.rect.width) - 20; ++i) {
            for (int j = ball.rect.top + 1; j < (ball.rect.top + ball.rect.height) - 1; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                        ISDIE = true;
                    }
                }
            }
        }

    }
    else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        for (int i = ball.rect.left + 18; i < (ball.rect.left + ball.rect.width) - 20; ++i) {
            for (int j = ball.rect.top + 1; j < (ball.rect.top + ball.rect.height) - 1; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                        ISDIE = true;
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        for (int i = ball.rect.left + 1; i < (ball.rect.left + ball.rect.width) - 1; ++i) {
            for (int j = ball.rect.top + 18; j < (ball.rect.top + ball.rect.height) - 20; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                        ISDIE = true;
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        for (int i = ball.rect.left + 1; i < (ball.rect.left + ball.rect.width) - 1; ++i) {
            for (int j = ball.rect.top + 18; j < (ball.rect.top + ball.rect.height) - 20; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                        ISDIE = true;
                    }
                }
            }
        }
    } else {
    for (int i = ball.rect.left + 21; i < (ball.rect.left + ball.rect.width) - 21; ++i) {
        for (int j = ball.rect.top + 21; j < (ball.rect.top + ball.rect.height) - 21; ++j) {
            for (auto& el : all_cores) {
                if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                    
                    ISDIE = true;
                }
            }

        }
    }
}


   /* for (int i = player.rect.left; i < (player.rect.left + player.rect.width); ++i) {
        for (int j = player.rect.top; j < (player.rect.top + player.rect.height); ++j) {
            for (auto &el : all_cores) {
                if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {

                    Texture fail; fail.loadFromFile("fail.png");
                    el.sprite.setTexture(fail); ISDIE = true;
                }
            }
            
        }
    }*/
}

//int main()
//{
//    srand(time(0));
//    ISDIE = false;
//
//    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "");
//
//    Texture tPlayer; tPlayer.loadFromFile("ship.png");
//    Player ball(tPlayer);
//    
//    Texture tWater; tWater.loadFromFile("water.jpg");
//    Sprite sWater; sWater.setTexture(tWater);
//    sWater.setPosition(0, 0);
//
//    Texture tCore; tCore.loadFromFile("core.png");
//    Cores* pCore;
//   
//    Texture tChest; tChest.loadFromFile("chest.png");
//    Chest* pChest;
//
//    Clock clock;
//    Clock CLOCK1, CLOCK2;
//    //int global_time = global_clock.getElapsedTime().asMilliseconds();
//
//    Font font; 
//    if (!font.loadFromFile("impact.ttf")) { std::cout << "ERROR FONT!!!"; };
//    Text text; text.setFont(font);
//    
//    float TIME1 = 0, TIME2 = 0;
//
//    std::string report;
//    float difficult = 0.5;
//
//    while (window.isOpen()) {
//       
//        float time = clock.getElapsedTime().asMicroseconds();
//        clock.restart();
//        time = time / 500;  // скорость обновления анимации
//        
//        
//        
//        
//        if (CLOCK1.getElapsedTime().asSeconds() > difficult && !ISDIE) {
//            pCore = new Cores(tCore); 
//            pCore->speedx = -(pCore->rect.left - 32 - ball.rect.left) / 6000;
//            pCore->speedy = -(pCore->rect.top - 32 - ball.rect.top) / 6000;
//            all_cores.push_back(*pCore);
//            int i = 0;
//            for (auto &el : all_cores) {
//                if ((el.rect.left > 1920 || el.rect.left < 0) && (el.rect.top > 1080 || el.rect.top < 0)) { all_cores.erase(all_cores.begin() + i); }
//                else { ++i;}
//            }
//            CLOCK1.restart();
//           
//        }
//        //if (TIME1 > 3000 && difficult > 100) { difficult -= 100; TIME1 = 0;}
//       
//       
//        
//        if (CLOCK2.getElapsedTime().asSeconds() > 2 && all_chests.size() <= 5 && !ISDIE) {
//            pChest = new Chest(tChest);
//            all_chests.push_back(*pChest);
//            CLOCK2.restart();
//        }
//
//        int i = 0;
//        for (auto& el : all_chests) {
//            if (el.collect) { all_chests.erase(all_chests.begin() + i); }
//            else { ++i; }
//        }
//       
//        {
//            sf::Event event;
//            while (window.pollEvent(event))
//            {
//                if (event.type == sf::Event::Closed)
//                    window.close();
//            } }
//        
//       
//        if (Keyboard::isKeyPressed(Keyboard::Left) && ball.rect.left > 0 && !ISDIE) {
//            ball.sprite.setTextureRect(IntRect(64*6, 0, 64, 64));
//            ball.speedx = -SPEED;
//            
//           
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Right) && ball.rect.left < SCREEN_WIDTH - 64 && !ISDIE) {
//            ball.sprite.setTextureRect(IntRect(64*2, 0, 64, 64));
//            ball.speedx = SPEED;
//          
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Up) && ball.rect.top > 0 && !ISDIE) {
//            ball.sprite.setTextureRect(IntRect(64*0, 0, 64, 64));
//            ball.speedy = -SPEED;
//            
//        }
//        if (Keyboard::isKeyPressed(Keyboard::Down) && ball.rect.top < SCREEN_HEIGHT - 64 && !ISDIE) {
//            ball.sprite.setTextureRect(IntRect(64*4, 0, 64, 64));
//            ball.speedy = SPEED;
//           
//        }
//    
//        //////////////////////////////////////////////////////////////////
//        
//        if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up)) {ball.sprite.setTextureRect(IntRect(64 * 7, 0, 64, 64));}
//        if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)) {ball.sprite.setTextureRect(IntRect(64 * 1, 0, 64, 64));}
//        if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right)) {ball.sprite.setTextureRect(IntRect(64 * 3, 0, 64, 64));}
//        if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left)) {ball.sprite.setTextureRect(IntRect(64 * 5, 0, 64, 64));}
//       
//        if (!ISDIE) { window.draw(sWater); }
//        else { window.clear(Color::Red); }
//        
//        
//        //std::string col = ".\t cores: ";
//        
//        //report += x += std::to_string(ball.rect.left) += y += std::to_string(ball.rect.top);
//        //report += std::to_string((int)global_clock.getElapsedTime().asSeconds()) += col += std::to_string(all_cores.size());
//        std::string score = "Score: ";
//        report += score += std::to_string(SCORE);
//        text.setString(report);
//        text.setCharacterSize(50);
//        text.setFillColor(Color::Black);
//
//        ball.update(time);
//        BDUM(ball);
//        GETCHEST(ball);
//        
//        for (auto& el : all_cores) {
//            el.update(time);
//        }
//
//        for (auto& el : all_chests) {
//            el.update();
//        }
//
//        //window.clear(Color::Cyan);
//
//        
//      
//       
//
//       /* if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up)) 
//        {
//            for (int k = 3; k >= 0; --k) {
//                for (int i = ball.rect.left + 11 + 8 *(3-k); i < (ball.rect.left + ball.rect.width) - 11 - 8 * k; ++i) {
//                    for (int j = ball.rect.top + 11 + 8*(3-k); j < (ball.rect.top + ball.rect.height) - 11 - 8 * k; ++j) {
//                        sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                        window.draw(&point, 1, sf::Points);
//                    }
//                }
//            }
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up)) 
//        {
//            for (int k = 3; k >= 0; --k) {
//                for (int i = ball.rect.left + 11 + 8 * k; i < (ball.rect.left + ball.rect.width) - 11 - 8 * (3 - k); ++i) {
//                    for (int j = ball.rect.top + 11 + 8 * (3 - k); j < (ball.rect.top + ball.rect.height) - 11 - 8 * k; ++j) {
//                        sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                        window.draw(&point, 1, sf::Points);
//                    }
//                }
//            }
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right)) 
//        {
//            for (int k = 3; k >= 0; --k) {
//                for (int i = ball.rect.left + 11 + 8 * (3 - k); i < (ball.rect.left + ball.rect.width) - 11 - 8 * k; ++i) {
//                    for (int j = ball.rect.top + 11 + 8 * (3 - k); j < (ball.rect.top + ball.rect.height) - 11 - 8 * k; ++j) {
//                        sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                        window.draw(&point, 1, sf::Points);
//                    }
//                }
//            }
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left)) 
//        {
//            for (int k = 3; k >= 0; --k) {
//                for (int i = ball.rect.left + 11 + 8 * k; i < (ball.rect.left + ball.rect.width) - 11 - 8 * (3 - k); ++i) {
//                    for (int j = ball.rect.top + 11 + 8 * (3 - k); j < (ball.rect.top + ball.rect.height) - 11 - 8 * k; ++j) {
//                        sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                        window.draw(&point, 1, sf::Points);
//                    }
//                }
//            }
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Up))
//        {
//            for (int i = ball.rect.left + 18; i < (ball.rect.left + ball.rect.width) - 20; ++i) {
//                for (int j = ball.rect.top + 1; j < (ball.rect.top + ball.rect.height) - 1; ++j) {
//                    sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                    window.draw(&point, 1, sf::Points);
//                }
//            }
//            
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Down))
//        {
//            for (int i = ball.rect.left + 18; i < (ball.rect.left + ball.rect.width) - 20; ++i) {
//                for (int j = ball.rect.top + 1; j < (ball.rect.top + ball.rect.height) - 1; ++j) {
//                    sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                    window.draw(&point, 1, sf::Points);
//                }
//            }
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Left)) {
//            for (int i = ball.rect.left + 1; i < (ball.rect.left + ball.rect.width) - 1; ++i) {
//                for (int j = ball.rect.top + 18; j < (ball.rect.top + ball.rect.height) - 20; ++j) {
//                    sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                    window.draw(&point, 1, sf::Points);
//                }
//            }
//        }
//        else if (Keyboard::isKeyPressed(Keyboard::Right)) {
//            for (int i = ball.rect.left + 1; i < (ball.rect.left + ball.rect.width) - 1; ++i) {
//                for (int j = ball.rect.top + 18; j < (ball.rect.top + ball.rect.height) - 20; ++j) {
//                    sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                    window.draw(&point, 1, sf::Points);
//                }
//            }
//        }
//        else {
//            for (int i = ball.rect.left + 21; i < (ball.rect.left + ball.rect.width) - 21; ++i) {
//                for (int j = ball.rect.top + 21; j < (ball.rect.top + ball.rect.height) - 21; ++j) {
//                    sf::Vertex point(sf::Vector2f(i, j), sf::Color::Blue);
//                    window.draw(&point, 1, sf::Points);
//                }
//            }
//        }*/
//        
//
//        for (auto& el : all_chests) {
//            window.draw(el.sprite);
//        }
//
//        window.draw(ball.sprite);
//
//        for (auto &el : all_cores){
//            window.draw(el.sprite);
//        }
//
//      
//
//       /* for (auto& el : all_cores) {
//            sf::CircleShape shape2(2);
//            shape2.setFillColor(sf::Color::Green);
//            shape2.setPosition(el.rect.left + 8, el.rect.top + 8);
//
//            window.draw(shape2);
//        }*/
//
//        
//        window.draw(text);
//        window.display();
//        report.clear();
//    }
//
//    return 0;
//}