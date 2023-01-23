#pragma execution_character_set("utf-8")
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>
#include <Windows.h>
using namespace sf;
using namespace std;

const unsigned int		SCREEN_WIDTH		= 1920;		// �������
const unsigned int		SCREEN_HEIGHT		= 1080;		// �������� ����
const float				SPEED				= 0.15;		// �������� ������
unsigned int			SCORE				= 0;		// ����
unsigned int			score               = 0;		// ����, �� ������
float                   DIFFICULT           = 1;        // ��������� ���� (������� ��������� ����)
unsigned int            CORES_NUM           = 0;        // ����� ���������� ����
bool					ISDEAD;
class					Cores;
class					Chests;
vector<Cores>			all_cores;						// ��������� �����������
vector<Chests>			all_chests;						// ��������� �����

class Player {
public:
    float speedx, speedy;   // �������� �� ����
    FloatRect rect;         // ���� ���� ������ � ��������� � ������� ���� ��� ���� ��� ���
    Sprite sprite;          // ������ ���� �����
    Player(Texture& texture) {
        sprite.setTexture(texture);                                     // �������� ��������
        sprite.setTextureRect(IntRect(0, 0, 64, 64));                   // ����������� �������� �� ������
        rect = FloatRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64);  // �������� �����
        sprite.setPosition(rect.left, rect.top);                        // ������������ ������� �� ������
        speedx = speedy = 0;                                            // ��������� �������� = 0
        ISDEAD = false;                                                 // ��������� ���������: ���
    }
    void update(float time) {
        rect.left += speedx * time;
        rect.top += speedy * time;
        sprite.setPosition(rect.left, rect.top);
        speedy = 0; speedx = 0;
    }
    void movie() {
        if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up) && rect.left > 0 && rect.top > 0 && !ISDEAD)
        { sprite.setTextureRect(IntRect(64 * 7, 0, 64, 64)); speedx = -(SPEED * 0.7); speedy = -(SPEED * 0.7);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up) && rect.left < SCREEN_WIDTH - 64 && rect.top > 0 && !ISDEAD)
        { sprite.setTextureRect(IntRect(64 * 1, 0, 64, 64)); speedx = (SPEED * 0.7); speedy = -(SPEED * 0.7);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right) && rect.left < SCREEN_WIDTH - 64 && rect.top < SCREEN_HEIGHT - 64 && !ISDEAD)
        { sprite.setTextureRect(IntRect(64 * 3, 0, 64, 64)); speedx = (SPEED * 0.7); speedy = (SPEED * 0.7);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left) && rect.top < SCREEN_HEIGHT - 64 && rect.left > 0 && !ISDEAD)
        { sprite.setTextureRect(IntRect(64 * 5, 0, 64, 64)); speedx = -(SPEED * 0.7); speedy = (SPEED * 0.7);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left) && rect.left > 0 && !ISDEAD) {
            sprite.setTextureRect(IntRect(64 * 6, 0, 64, 64)); speedx = -SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Right) && rect.left < SCREEN_WIDTH - 64 && !ISDEAD) {
            sprite.setTextureRect(IntRect(64 * 2, 0, 64, 64)); speedx = SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Up) && rect.top > 0 && !ISDEAD) {
            sprite.setTextureRect(IntRect(64 * 0, 0, 64, 64)); speedy = -SPEED;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) && rect.top < SCREEN_HEIGHT - 64 && !ISDEAD) {
            sprite.setTextureRect(IntRect(64 * 4, 0, 64, 64)); speedy = SPEED;
        }
    }
};

class Cores {
public:
    float speedx, speedy;   // �������� �� ����
    FloatRect rect;         // ���� ���� ������ � ��������� � ������� ���� ��� ���� ��� ���
    Sprite sprite;          // ������ ���� �����
    Texture txt;
    Cores(Texture& texture) {
        txt = texture;
        sprite.setTexture(txt);
        sprite.setTextureRect(IntRect(0, 0, 16, 16));
        bool left = rand() % 2, top = rand() % 2;                                           // ��������� ����� 
        if (left) { if (top) { rect = FloatRect(rand() % SCREEN_WIDTH, 0, 64, 64); }        // ����������
        else { rect = FloatRect(SCREEN_WIDTH, rand() % SCREEN_HEIGHT, 64, 64); }}           // �����������
        else { if (top) { rect = FloatRect(rand() % SCREEN_WIDTH, SCREEN_HEIGHT, 64, 64);}  // �� ���������
        else { rect = FloatRect(0, rand() % SCREEN_HEIGHT, 64, 64); }}           // �����
        sprite.setPosition(rect.left, rect.top); speedx = speedy = 0;                       // ��������� ����
    }
    
    void update(float time) {
        if (!ISDEAD) {                                                                      // ������������� ��������
            rect.left += speedx * time;
            rect.top += speedy * time;
        }
        else { speedy = 0; speedx = 0; }
        sprite.setPosition(rect.left, rect.top);
    }
};

class Chests {
public:
    FloatRect rect;         // ���� ���� ������ � ��������� � ������� ���� ��� ���� ��� ���
    Sprite sprite;          // ������ ���� �����
    bool collect;           // ���� ������ ��� ���
    Chests(Texture& texture) {
        collect = false;
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
        rect = FloatRect(rand() % (SCREEN_WIDTH - 32), rand() % (SCREEN_HEIGHT - 32), 32, 32);
        sprite.setPosition(rect.left, rect.top);
    }
    void update() {if (!collect) { sprite.setPosition(rect.left, rect.top); }}
};

void create_core(Clock& clock, Texture& tCore, Player& ship, Cores*& pCore) {
    if (clock.getElapsedTime().asSeconds() > DIFFICULT && !ISDEAD) {
        pCore = new Cores(tCore);
        pCore->speedx = -(pCore->rect.left - 32 - ship.rect.left) / 6000;       // ������� �������� � ����������� 
        pCore->speedy = -(pCore->rect.top - 32 - ship.rect.top) / 6000;         // �� � � � � ������ ���������
        all_cores.push_back(*pCore); ++CORES_NUM; int i = 0;
        for (auto& el : all_cores) {
            if ((el.rect.left > 1920 || el.rect.left < 0) && (el.rect.top > 1080 || el.rect.top < 0)) { all_cores.erase(all_cores.begin() + i); }
            else { ++i; }
        }
        clock.restart();
    }
}

void create_chest(Clock& clock, Texture& tChest, Chests*& pChest) {
    if (CORES_NUM > 5 && all_chests.size() <= 5 && !ISDEAD) {
        pChest = new Chests(tChest);
        all_chests.push_back(*pChest);
        clock.restart();
        CORES_NUM = 0;
    }
    int i = 0;
    for (auto& el : all_chests) {
        if (el.collect) { all_chests.erase(all_chests.begin() + i); }
        else { ++i; }
    }
}

void diff_up() {
    
    if (DIFFICULT > 0.4 && score % 2 == 0 && score != 0) { DIFFICULT -= 0.2; score = 0; }
}

bool is_BDUM(Player& ship, Texture& tBoom) {
    if (Keyboard::isKeyPressed(Keyboard::Left) && Keyboard::isKeyPressed(Keyboard::Up))
    {
        for (int k = 3; k >= 0; --k) {
            for (int i = ship.rect.left + 11 + 8 * (3 - k); i < (ship.rect.left + ship.rect.width) - 11 - 8 * k; ++i) {
                for (int j = ship.rect.top + 11 + 8 * (3 - k); j < (ship.rect.top + ship.rect.height) - 11 - 8 * k; ++j) {
                    for (auto& el : all_cores) {
                        if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right) && Keyboard::isKeyPressed(Keyboard::Up))
    {
        for (int k = 3; k >= 0; --k) {
            for (int i = ship.rect.left + 11 + 8 * k; i < (ship.rect.left + ship.rect.width) - 11 - 8 * (3 - k); ++i) {
                for (int j = ship.rect.top + 11 + 8 * (3 - k); j < (ship.rect.top + ship.rect.height) - 11 - 8 * k; ++j) {
                    for (auto& el : all_cores) {
                        if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Right))
    {
        for (int k = 3; k >= 0; --k) {
            for (int i = ship.rect.left + 11 + 8 * (3 - k); i < (ship.rect.left + ship.rect.width) - 11 - 8 * k; ++i) {
                for (int j = ship.rect.top + 11 + 8 * (3 - k); j < (ship.rect.top + ship.rect.height) - 11 - 8 * k; ++j) {
                    for (auto& el : all_cores) {
                        if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Down) && Keyboard::isKeyPressed(Keyboard::Left))
    {
        for (int k = 3; k >= 0; --k) {
            for (int i = ship.rect.left + 11 + 8 * k; i < (ship.rect.left + ship.rect.width) - 11 - 8 * (3 - k); ++i) {
                for (int j = ship.rect.top + 11 + 8 * (3 - k); j < (ship.rect.top + ship.rect.height) - 11 - 8 * k; ++j) {
                    for (auto& el : all_cores) {
                        if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Up))
    {
        for (int i = ship.rect.left + 18; i < (ship.rect.left + ship.rect.width) - 20; ++i) {
            for (int j = ship.rect.top + 1; j < (ship.rect.top + ship.rect.height) - 1; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                        return true;
                    }
                }
            }
        }

    }
    else if (Keyboard::isKeyPressed(Keyboard::Down)) {
        for (int i = ship.rect.left + 18; i < (ship.rect.left + ship.rect.width) - 20; ++i) {
            for (int j = ship.rect.top + 1; j < (ship.rect.top + ship.rect.height) - 1; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                        return true;
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Left)) {
        for (int i = ship.rect.left + 1; i < (ship.rect.left + ship.rect.width) - 1; ++i) {
            for (int j = ship.rect.top + 18; j < (ship.rect.top + ship.rect.height) - 20; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                        return true;
                    }
                }
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        for (int i = ship.rect.left + 1; i < (ship.rect.left + ship.rect.width) - 1; ++i) {
            for (int j = ship.rect.top + 18; j < (ship.rect.top + ship.rect.height) - 20; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                        return true;
                    }
                }
            }
        }
    }
    else {
        for (int i = ship.rect.left + 21; i < (ship.rect.left + ship.rect.width) - 21; ++i) {
            for (int j = ship.rect.top + 21; j < (ship.rect.top + ship.rect.height) - 21; ++j) {
                for (auto& el : all_cores) {
                    if (((int)el.rect.left + 8 == i && (int)el.rect.top + 8 == j)) {
                        el.sprite.setTexture(tBoom);el.sprite.setTextureRect(IntRect(0, 0, 32, 32)); return true;
                    }
                }

            }
        }
        return false;
    } 
    return false;
}

bool is_COLLECTED(Player& ship) {
    for (int i = ship.rect.left + 10; i < (ship.rect.left + ship.rect.width) - 10; ++i) {
        for (int j = ship.rect.top + 10; j < (ship.rect.top + ship.rect.height) - 10; ++j) {
            for (auto& el : all_chests) {
                if ((int)el.rect.left + 16 == i && (int)el.rect.top + 16 == j) {
                    el.collect = true; return true;
                }
            }
        }
    }
    return false;
}

void RESTART(Player& ship) {
    all_cores.clear();
    all_chests.clear();
    ship.rect = FloatRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64);  
    ship.sprite.setPosition(ship.rect.left, ship.rect.top);                        
    ship.speedx = ship.speedy = 0;   
    SCORE = 0;
    DIFFICULT = 1;
    ISDEAD = false;
}

SoundBuffer shootBuffer;
Sound shoot;

int main() {
    srand(time(0)); RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "A COOL PIRATE SHIP IS FLOATING AND TRYING TO SURVIVE FROM THE LAST 2D FORCES AND TREASURES");
//-----------------------------------------------------------------------------------------------------------
    Clock clock;                                                    // ���� ��� ������� �� �������� ��
    Clock cores_clock;                                              // ���� ��� ������ ����
    Clock chests_clock;                                             // ���� ��� ������ ��������
//-----------------------------------------------------------------------------------------------------------
    SoundBuffer buffer;
    buffer.loadFromFile("music.mp3");                               // �������� ������ �������
    Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(30);
    sound.play();

    shootBuffer.loadFromFile("boom.mp3");
    shoot.setBuffer(shootBuffer);

    SoundBuffer holeraBuffer;
    holeraBuffer.loadFromFile("holera.mp3");
    Sound holera(holeraBuffer);
    
//-----------------------------------------------------------------------------------------------------------
    Font font;                                                      // �������� ������ ��� ������
    if (!font.loadFromFile("impact.ttf")) { cout << "ERROR FONT!!!"; };
    Text text; text.setFont(font);
    string report;
//-----------------------------------------------------------------------------------------------------------
    Texture tship; tship.loadFromFile("ship.png");                  // �������� ���������
    Player ship(tship);                                             // �������� (�����)

    Texture tWater; tWater.loadFromFile("water.jpg");               // �������� ���� (����)
    Sprite sWater; sWater.setTexture(tWater);                       // ������ ����
    sWater.setPosition(0, 0);

    Texture tCore; tCore.loadFromFile("core.png");                  // �������� ���� (�����������)
    Cores* pCore;

    Texture tBoom; tBoom.loadFromFile("boom.png");

    Texture tChest; tChest.loadFromFile("chest.png");               // �������� ������� (���� �����)
    Chests* pChest;
//-----------------------------------------------------------------------------------------------------------
    while (window.isOpen()) {
        {Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
        }} 
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart(); time = time / 500;                         // �������� ���������� ��������
//-----------------------------------------------------------------------------------------------------------
// ��������:
        text.setPosition(0, 0);
        create_core(cores_clock, tCore, ship, *&pCore);
        diff_up();
        create_chest(chests_clock, tChest, *&pChest);
        ship.movie();
        if (is_BDUM(ship, tBoom)) { shoot.play(); holera.play(); ISDEAD = true; }
        if (is_COLLECTED(ship)) { ++SCORE; ++score; }
        string score = "Score: ", diff = ". Diff: ";
        report += score += to_string(SCORE) += diff += to_string(DIFFICULT);
        text.setString(report);
//-----------------------------------------------------------------------------------------------------------
// update-�������:
        ship.update(time);                                          // ���������� ���������
        for (auto& el : all_cores) { el.update(time); }             // ���������� ���� ����
        for (auto& el : all_chests) { el.update(); }                // ���������� ���� ��������
//-----------------------------------------------------------------------------------------------------------
// ���������:
        if (!ISDEAD) { window.draw(sWater); }                       // ��������� ���� �� ����� ����
        else { window.clear(Color::Red);                            // � ��� ���������
        report += "Press ENTER to restart";
        text.setString(report);
        text.setPosition(1920 / 2 - 100, 1080 / 2 - 25);
        window.draw(text);
        if (Keyboard::isKeyPressed(Keyboard::Enter)) {
            
            RESTART(ship);
        }
        }                          
        window.draw(ship.sprite);                                   // ��������� ���������
        for (auto& el : all_cores) { window.draw(el.sprite); }      // ��������� ���� ����
        for (auto& el : all_chests) { window.draw(el.sprite); }     // ��������� ���� ��������
        window.draw(text);                                          // ��������� �����
        report.clear();                                             // ������� ������
        window.display();

    }
}
