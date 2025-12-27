#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <string>

#include "SoundManager.h"

using namespace std;
using namespace sf;

SoundManager soundManager;

void Speech(string num) {
    soundManager.playSound(num);
}

int randomise(int x) {
    std::random_device rd;  // Источник случайности
    std::mt19937 gen(rd()); // Генератор случайных чисел
    std::uniform_int_distribution<int> dist(1, x); // Диапазон [0, 99]

    int random_number = dist(gen);
    return random_number;
}

short inp = 0;
short attempts = 3;
string score_string = "";
bool otklik = true;
bool isGame = false;
bool onceTrigger = false;



int main()
{
    sf::Clock clock;
    srand(time(nullptr));
    soundManager.loadSound("correct", "rs/Correct.wav");
    soundManager.loadSound("button", "rs/but1.ogg");
    soundManager.loadSound("wrong", "rs/wrong.ogg");
    soundManager.loadSound("1", "rs/Red.wav");
    soundManager.loadSound("2", "rs/Orange.wav");
    soundManager.loadSound("3", "rs/Yellow.wav");
    soundManager.loadSound("4", "rs/Green.wav");
    soundManager.loadSound("5", "rs/Aqua.wav");
    soundManager.loadSound("6", "rs/Blue.wav");
    soundManager.loadSound("7", "rs/Pink.wav");
    soundManager.loadSound("8", "rs/Violet.wav");
    soundManager.loadSound("9", "rs/White.wav");

    std::cout << "Please, don't close this termunal. I'm weak at application programs, so terminal is important for Sleep();" << std::endl;
    vector<int> colors;
    vector<int> player_color;

    //while (true) {
    //    short inp = 0;
    //    system("cls");
    //    player_color.clear();
    //    int ran = randomise(9);
    //    cout << "New number: "; cout << ran << endl;
    //    colors.push_back(ran);
    //    cout << size(colors) << endl;
    //    for (int a = 0; a!= size(colors); a++) {
    //        cout << "Input> "; cin >> inp; cout << "\n";
    //        player_color.push_back(inp);
    //    }
    //    if (colors == player_color) {
    //        cout << "Correct." << endl;
    //    }
    //    else {
    //        break;
    //    }
    //    
    //}
    

    Font font;
    Text text;
    font.loadFromFile("rs/comic.ttf");
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(24); // in pixels, not points!
    text.setPosition(608, 448);



    RenderWindow window(VideoMode(640, 480), "Project: Deuterium | Electron Corporation");
    RectangleShape red(Vector2f(100,100));
    red.setFillColor(Color::Red);
    red.setPosition(0, 0);
    RectangleShape orange(Vector2f(100, 100));
    orange.setFillColor(Color{255, 145, 0});
    orange.setPosition(100, 0);
    RectangleShape yellow(Vector2f(100, 100));
    yellow.setFillColor(Color::Yellow);
    yellow.setPosition(200, 0);
    RectangleShape green(Vector2f(100, 100));
    green.setFillColor(Color::Green);
    green.setPosition(0, 100);
    RectangleShape cyan(Vector2f(100, 100));
    cyan.setFillColor(Color{ 0, 255, 255 });
    cyan.setPosition(100, 100);
    RectangleShape blue(Vector2f(100, 100));
    blue.setFillColor(Color{ 0, 50, 255 });
    blue.setPosition(200, 100);
    RectangleShape pink(Vector2f(100, 100));
    pink.setFillColor(Color{ 255, 94, 239 });
    pink.setPosition(0, 200);
    RectangleShape purple(Vector2f(100, 100));
    purple.setFillColor(Color{ 105, 0, 198 });
    purple.setPosition(100, 200);
    RectangleShape white(Vector2f(100, 100));
    white.setFillColor(Color::White);
    white.setPosition(200, 200);
    
    Texture HeartText;
    HeartText. loadFromFile("rs/heart.png");
    Sprite heart(HeartText);

    Texture ImpulseText;
    ImpulseText.loadFromFile("rs/brain_impulse.png");
    Sprite impulse(ImpulseText);

    Texture MenuText;
    MenuText.loadFromFile("rs/menu.png");
    Sprite menu_sprite(MenuText);
    menu_sprite.setPosition(0, 0);

    Texture ScoreTexture;
    ScoreTexture.loadFromFile("rs/empty.png");
    Sprite ScoreSprite(ScoreTexture);

    std::vector<sf::Vector2f> impulsePositions = {
    {453,310}, {593,328}, {468,356}, {561,259},
    {521,211}, {303,312}, {313,235}, {343, 200}, {497,325}
    };

    std::vector<sf::Clock> flickerClocks;
    std::vector<bool> brightStates;
    std::vector<sf::Sprite> impulses;

    sf::Clock spawnClock;
    size_t currentImpulse = 0;






    //int ran = randomise(9);
    //colors.push_back(ran);
    //std::cout << "New number: "; std::cout << ran << endl;
    //Speech(to_string(ran));



    bool mouseReleased = true;
    int currentIndex = 0;

    //sf::CircleShape shape(5.f);
    //shape.setFillColor(Color{0, 0, 255});
    //shape.setPosition(10, 10);

    RectangleShape color_display(Vector2f(220, 220));
    //color_display.setFillColor(Color::White);
    color_display.setPosition(360, 50);
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) { window.close(); }
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                mouseReleased = true;  // Разрешаем обработку нового нажатия
            }
                
        }
        
        
        if (isGame == false) {
            sf::Time elapsed = clock.getElapsedTime();
            float dt = clock.restart().asSeconds();
            //if (onceTrigger == false) {
            //    std::cout << isGame << std::endl;
            //    window.clear(Color::Black);
            //    window.draw(menu_sprite);
            //    onceTrigger = true;
            //}
            if (spawnClock.getElapsedTime().asSeconds() >= 0.5f &&
                currentImpulse < impulsePositions.size())
            {
                sf::Sprite s(ImpulseText);
                s.setPosition(impulsePositions[currentImpulse]);
                impulses.push_back(s);
                flickerClocks.emplace_back();
                brightStates.push_back(rand() % 2);
                currentImpulse++;
                spawnClock.restart();
                
            }

            for (size_t i = 0; i < impulses.size(); i++) {

                if (flickerClocks[i].getElapsedTime().asSeconds() >=
                    (0.1f + (rand() % 100) / 1000.f))   // чуть разный ритм
                {
                    brightStates[i] = !brightStates[i];
                    flickerClocks[i].restart();
                }

                sf::Uint8 alpha = brightStates[i] ? 220 : 120;
                impulses[i].setColor(sf::Color(255, 255, 255, alpha));
            }


            window.clear(sf::Color::Black);
            window.draw(menu_sprite);

            for (auto& s : impulses)
                window.draw(s);

            window.display();

            
            
            if (Mouse::isButtonPressed(Mouse::Left) && mouseReleased) {
                window.clear();
                mouseReleased = false;
                isGame = true;
                //std::cout << sf::Mouse::getPosition(window).x; std::cout << " "; std::cout << sf::Mouse::getPosition(window).y << std::endl;
            }
            
        }


        if (isGame) {
            if (Mouse::isButtonPressed(Mouse::Left) && mouseReleased) {
                if (attempts > 0) {
                    
                    mouseReleased = false;  // Блокируем повторные срабатывания
                    soundManager.playSound("button");

                    Vector2i mousePos = Mouse::getPosition(window);

                    //std::cout << sf::Mouse::getPosition(window).x; std::cout << " "; std::cout << sf::Mouse::getPosition(window).y << std::endl;

                    //shape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

                    int inp = 0;

                    if (IntRect(0, 0, 100, 100).contains(mousePos)) {
                        inp = 1;
                    }
                    if (IntRect(100, 0, 200, 100).contains(mousePos)) {
                        inp = 2;
                    }
                    if (IntRect(200, 0, 300, 100).contains(mousePos)) {
                        inp = 3;
                    }
                    if (IntRect(0, 100, 100, 200).contains(mousePos)) {
                        inp = 4;
                    }
                    if (IntRect(100, 100, 200, 200).contains(mousePos)) {
                        inp = 5;
                    }
                    if (IntRect(200, 100, 300, 200).contains(mousePos)) {
                        inp = 6;
                    }
                    if (IntRect(0, 200, 100, 100).contains(mousePos)) {
                        inp = 7;
                    }
                    if (IntRect(100, 200, 200, 100).contains(mousePos)) {
                        inp = 8;
                    }
                    if (IntRect(200, 200, 300, 100).contains(mousePos)) {
                        inp = 9;
                    }

                    if (inp != 0) {  // Если игрок нажал на правильную область
                        player_color.push_back(inp);
                        //cout << "Player input: " << inp << endl;

                        // Проверяем, соответствует ли текущий ввод правильной последовательности
                        if (player_color.back() != colors[currentIndex]) {
                            cout << "Wrong! Try again." << endl;
                            attempts -= 1;
                            soundManager.playSound("wrong");
                            player_color.clear();
                            currentIndex = 0;
                            otklik = false;
                            continue;  // Прерываем выполнение, чтобы не идти дальше
                        }

                        currentIndex++;

                        // Если игрок ввёл всю последовательность верно
                        if (currentIndex == colors.size()) {
                            cout << "Correct!" << endl;
                            soundManager.playSound("correct");
                            otklik = true;
                            score_string = to_string(colors.size());
                            text.setString(score_string);
                        }
                    }
                }
            }

            if (otklik) {
                int ran = randomise(9);
                colors.push_back(ran);
                
                Sleep(1500);
                system("cls");
                //cout << "Score: "; cout << colors.size()-1 << endl;



                short sisya = 0;
                while (sisya < colors.size()) {
                    //std::cout << colors[sisya] << std::endl;
                    switch (colors[sisya])
                    {
                    case 1: 
                        color_display.setFillColor(Color::Red);
                        break;
                    case 2: 
                        color_display.setFillColor(Color{ 255, 180, 0 });
                        break;
                    case 3: 
                        color_display.setFillColor(Color::Yellow);
                        break;
                    case 4: 
                        color_display.setFillColor(Color::Green);
                        break;
                    case 5: 
                        color_display.setFillColor(Color{ 0, 255, 255 });
                        break;
                    case 6: 
                        color_display.setFillColor(Color{ 0, 50, 255 });
                        break;
                    case 7: 
                        color_display.setFillColor(Color{ 255, 94, 239 });
                        break;
                    case 8: 
                        color_display.setFillColor(Color{ 105, 0, 198 });
                        break;
                    case 9: 
                        color_display.setFillColor(Color::White);
                        break;
                    default:
                        break;
                    }
                    window.draw(color_display);
                    window.display();
                    Speech(to_string(colors[sisya]));
                    //if (colors[sisya] == 5) {
                //    Sleep(800);
                //}
                //else {
                //    Sleep(500);
                //}
                    Sleep(600);
                    sisya += 1;

                }
                color_display.setFillColor(Color::Black);

                //cout << "New sequence: ";
            //for (int num : colors) cout << num << " ";
            //cout << endl;

                player_color.clear();
                currentIndex = 0;
                otklik = false;

            }

            if (attempts <= 0) {
                if (colors.size() >= 1) {
                    ScoreTexture.loadFromFile("rs/Weak.png");
                    Sprite ScoreSprite(ScoreTexture);
                }
                if (colors.size() >= 3) {
                    ScoreTexture.loadFromFile("rs/mdauzh.png");
                    Sprite ScoreSprite(ScoreTexture);
                }
                if (colors.size() >= 5) {
                    ScoreTexture.loadFromFile("rs/notbad.png");
                    Sprite ScoreSprite(ScoreTexture);
                }
                if (colors.size() >= 10) {
                    ScoreTexture.loadFromFile("rs/good.png");
                    Sprite ScoreSprite(ScoreTexture);
                }
                if (colors.size() >= 15) {
                    ScoreTexture.loadFromFile("rs/epic.png");
                    Sprite ScoreSprite(ScoreTexture);
                }
                if (colors.size() >= 20) {
                    ScoreTexture.loadFromFile("rs/lega.png");
                    Sprite ScoreSprite(ScoreTexture);
                }
                ScoreSprite.setPosition(8, 439);
                window.draw(ScoreSprite);
            }

            //
        //if (otklik == true) {
        //    for (int a = 0; a == size(colors); a++) {
        //        //player_color.push_back(inp);
        //        player_color.clear();
        //        ran = randomise(9);
        //        cout << "New number: "; cout << ran << endl;
        //        cout << "Correct." << endl;
        //        otklik = false;
        //    }
        //    //if (colors == player_color) {
        //    //    cout << "Correct." << endl;
        //    //}
        //    //player_color.clear();
        //    //ran = randomise(9);
        //    //cout << "New number: "; cout << ran << endl;
        //    //otklik = false;
        //}
            
            window.clear();



            window.draw(red);
            window.draw(orange);
            window.draw(yellow);

            window.draw(green);
            window.draw(cyan);
            window.draw(blue);

            window.draw(pink);
            window.draw(purple);
            window.draw(white);
            window.draw(text);
            window.draw(color_display);

            for (char i = 0; i < attempts; i++) {
                heart.setPosition(8 + 70 * i, 408);
                window.draw(heart);
            }
            window.draw(ScoreSprite);
            window.display();
        }
    }

    return 0;
}