#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
//YXC
int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SubSub");

    sf::Texture bigenemietxto;
    sf::Texture playertxto;
    sf::Texture groundtxto;
    sf::Texture smallenemietxto;
    sf::Music outofbounce;
    sf::Font font;
    sf::Clock clock;
    sf::Text Dies;
    sf::Text GameOver;
    sf::Text leavecounter;

    if (!playertxto.loadFromFile("Assets/imgs/player.png")) return -1;
    if (!groundtxto.loadFromFile("Assets/imgs/grassblock.png")) return -1;
    if (!outofbounce.openFromFile("Assets/sounds/outofbounce.mp3")) return -1;
    if (!font.loadFromFile("Assets/fonts/Roboto/font.ttf")) return -1;
    if (!smallenemietxto.loadFromFile("Assets/imgs/smallenemie.png")) return -1;
    if (!bigenemietxto.loadFromFile("Assets/imgs/bigenemie.png")) return -1;

    int Diescount = 0;
    int leavecount = 4;

    float xground = -2.0f;
    float yground = 570.0f;
    float xplattform = xground + 500;
    float yplattform = yground - 200;
    float xwaytoroom1 = xground + 868.0f;
    float ywaytoroom1 = yground - 100.0f;

    float xsmallenemie = xground + 1000.0f;
    float ysmallenemie = yground - 73.0f;
    float xbigenemie = xground + 1500.0f;
    float ybigenemie = yground - 135.0f;
    bool showenemie = false;

    float playerspeed = 0.05f;
    bool showplayer = true;
    bool isjumping = false;
    bool onground;
    bool inroom1 = false;
    float jumpstrengh = 250.0f;
    float rightsite = 925.0f;
    float leftsite = 4.0f;
    float yplayeronwaytoroom1 = ywaytoroom1 - 75.0f;
    float yplayeronplattform = yplattform - 75.0f;
    float velocityYplayer = 0.08f;
    float xplayer = xground + 410.0f;
    float yplayer = yground - 75.0f;

    sf::Sprite playertxt;
    playertxt.setTexture(playertxto);

    sf::Sprite groundtxt;
    groundtxt.setTexture(groundtxto);

    sf::Sprite plattformtxt;
    plattformtxt.setTexture(groundtxto);

    sf::Sprite smallenemietxt;
    smallenemietxt.setTexture(smallenemietxto);

    sf::Sprite bigenemietxt;
    bigenemietxt.setTexture(bigenemietxto);

    sf::Sprite waytoroom1;
    waytoroom1.setTexture(groundtxto);

    Dies.setFont(font);
    Dies.setString(std::string("Dies : ") + std::to_string(Diescount));
    Dies.setCharacterSize(30);
    Dies.setFillColor(sf::Color::White);
    Dies.setPosition(30, 50);

    plattformtxt.setPosition(xplattform, yplattform);
    plattformtxt.setScale(sf::Vector2f(0.5f, 0.1f));

    playertxt.setPosition(xplayer, yplayer);
    playertxt.setScale(0.1f, 0.1f);

    groundtxt.setPosition(xground, yground);
    groundtxt.setScale(1.5f, 0.5f);

    smallenemietxt.setPosition(xsmallenemie, ysmallenemie);
    smallenemietxt.setScale(0.2f, 0.18f);

    bigenemietxt.setPosition(xbigenemie, ybigenemie);
    bigenemietxt.setScale(0.8f, 0.72f);

    waytoroom1.setPosition(xwaytoroom1, ywaytoroom1);
    waytoroom1.setScale(0.2f, 0.2f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (playertxt.getGlobalBounds().intersects(waytoroom1.getGlobalBounds()) && !inroom1) {
            yplayer = ywaytoroom1 - 75.0f;
        }

        if (playertxt.getGlobalBounds().intersects(plattformtxt.getGlobalBounds()) && inroom1) {
            yplayer = yplattform - 75.0f;
        }

        if (xplayer > rightsite && inroom1) {
            xplayer -= 100.0f;
            Diescount += 1;
            Dies.setString(std::string("Dies : ") + std::to_string(Diescount));
            outofbounce.play();
        }

        if (xplayer > rightsite) {
            xplayer = leftsite;
            inroom1 = true;
            if (clock.getElapsedTime().asSeconds() >= 1.0f) {
                showenemie = true;
                clock.restart();
            }
        } else if (xplayer < leftsite && inroom1) {
            xplayer = rightsite;
            inroom1 = false;
            showenemie = false;
        } else if (xplayer < leftsite && !inroom1) {
            xplayer += 100.0f;
            Diescount += 1;
            Dies.setString(std::string("Dies : ") + std::to_string(Diescount));
            outofbounce.play();
        }

        if (xplayer > xsmallenemie && xplayer < xbigenemie) {
            if (jumpstrengh > 150.0f) {
                jumpstrengh = 150.0f;
            }
        }

        if (showenemie) {
            xsmallenemie -= 0.02f;
            smallenemietxt.setPosition(xsmallenemie, ysmallenemie);

            xbigenemie -= 0.02f;
            bigenemietxt.setPosition(xbigenemie, ybigenemie);

            if (playertxt.getGlobalBounds().intersects(smallenemietxt.getGlobalBounds())) {
                outofbounce.play();
                Diescount = 10;
            }

            if (playertxt.getGlobalBounds().intersects(bigenemietxt.getGlobalBounds())) {
                outofbounce.play();
                Diescount = 10;
            }
        }

        if (yplayer == yground - 75.0f) {
            onground = true;
        }

        if (showplayer) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                xplayer -= playerspeed;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                xplayer += playerspeed;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!isjumping && onground || !isjumping && yplayer == yplayeronwaytoroom1 || !isjumping && yplayer == yplayeronplattform) {
                    isjumping = true;
                    onground = false;
                }
            }
        }

        if (isjumping) {
            yplayer -= velocityYplayer;

            if (yplayer <= jumpstrengh) {
                isjumping = false;
            }
        } else if (!onground) {
            yplayer += velocityYplayer;

            if (yplayer >= yground - 75.0f) {
                yplayer = yground - 75.0f;
                onground = true;
            }
        }

        playertxt.setPosition(xplayer, yplayer);

        if (xplayer > 925.0f || xplayer < 4.0f || xsmallenemie + smallenemietxt.getScale().x < 0 || xbigenemie + bigenemietxt.getScale().x < 0) {
            if (xsmallenemie + smallenemietxt.getScale().x < 0) {
                xsmallenemie = 1000.0f;
                smallenemietxt.setPosition(xsmallenemie, ysmallenemie);
            }

            if (xbigenemie + bigenemietxt.getScale().x < 0) {
                xbigenemie = 1000.0f;
                bigenemietxt.setPosition(xbigenemie, ybigenemie);
            }

            //rightside
            if (xplayer > rightsite) {
                /*
                xplayer = xplayer - 100;
                Diescount++;
                Dies.setString(std::string("Dies : ") + std::to_string(Diescount));
                outofbounce.play();
                */
            }

            //leftside
            if (xplayer < leftsite) {
                /*
                xplayer = xplayer + 100;
                Diescount++;
                Dies.setString(std::string("Dies : ") + std::to_string(Diescount));
                outofbounce.play();
                */
            }
        }

        if (Diescount >= 10) {
            showplayer = false;
            showenemie = false;

            GameOver.setFont(font);
            GameOver.setString("Gameover");
            GameOver.setCharacterSize(170);
            GameOver.setFillColor(sf::Color::Red);
            GameOver.setPosition(120, 200);

            leavecounter.setFont(font);
            leavecounter.setString(std::to_string(leavecount));
            leavecounter.setCharacterSize(70);
            leavecounter.setFillColor(sf::Color::Red);
            leavecounter.setPosition(500, 90);

            if (clock.getElapsedTime().asSeconds() >= 1.0f) {
                if (leavecount > 0) {
                    leavecount--;
                    leavecounter.setString(std::to_string(leavecount));
                }
                clock.restart();
            }

            if (leavecount <= 0) {
                window.close();
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(groundtxt);
        window.draw(Dies);
        window.draw(GameOver);
        window.draw(leavecounter);

        if (!inroom1) {
            window.draw(waytoroom1);
        }

        if (inroom1) {
            window.draw(plattformtxt);
        }

        if (showplayer) {
            window.draw(playertxt);
        }

        if (showenemie) {
            window.draw(smallenemietxt);
        }

        if (showenemie) {
            window.draw(bigenemietxt);
        }

        window.display();
    }

    return 0;
}