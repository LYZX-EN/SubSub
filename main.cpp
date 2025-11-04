#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class PLAYER {
public:
    float velocityYplayer;
    float xplayer;
    float yplayer;
    float jumpstrengh;
    float playerspeed;
};

class ENEMIE {
public:
    float xenemie;
    float yenemie;
};

class PLATTFORMS {
public:
    float xplattform;
    float yplattform;
};

//YXC
int main() {
    PLAYER player1;

    ENEMIE smallenemie;
    ENEMIE bigenemie;

    PLATTFORMS waytoroom1;
    PLATTFORMS plattform;
    PLATTFORMS ground;

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

    ground.xplattform = -2.0f;
    ground.yplattform = 570.0f;

    plattform.xplattform = ground.xplattform + 500;
    plattform.yplattform = ground.yplattform - 200;

    waytoroom1.xplattform = ground.xplattform + 868.0f;
    waytoroom1.yplattform = ground.yplattform - 100.0f;

    player1.velocityYplayer = 0.08f;
    player1.xplayer = ground.xplattform + 410.0f;
    player1.yplayer = ground.yplattform - 75.0f;
    player1.jumpstrengh = 250.0f;
    player1.playerspeed = 0.07f;

    smallenemie.xenemie = ground.xplattform + 1000.0f;
    smallenemie.yenemie = ground.yplattform - 73.0f;

    bigenemie.xenemie = ground.xplattform + 1500.0f;
    bigenemie.yenemie = ground.yplattform - 135.0f;

    bool showenemie = false;
    bool showplayer = true;
    bool isjumping = false;
    bool inroom1 = false;
    bool onground;

    int HP = 10;
    int leavecount = 4;
    float rightsite = 925.0f;
    float leftsite = 4.0f;
    float yplayeronwaytoroom1 = waytoroom1.yplattform - 75.0f;
    float yplayeronplattform = plattform.yplattform - 75.0f;

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

    sf::Sprite waytoroom1f;
    waytoroom1f.setTexture(groundtxto);

    Dies.setFont(font);
    Dies.setString(std::string("HP : ") + std::to_string(HP));
    Dies.setCharacterSize(30);
    Dies.setFillColor(sf::Color::White);
    Dies.setPosition(30, 50);

    plattformtxt.setPosition(plattform.xplattform, plattform.yplattform);
    plattformtxt.setScale(sf::Vector2f(0.5f, 0.1f));

    playertxt.setPosition(player1.xplayer, player1.yplayer);
    playertxt.setScale(0.1f, 0.1f);

    groundtxt.setPosition(ground.xplattform, ground.yplattform);
    groundtxt.setScale(1.5f, 0.5f);

    smallenemietxt.setPosition(smallenemie.xenemie, smallenemie.yenemie);
    smallenemietxt.setScale(0.2f, 0.18f);

    bigenemietxt.setPosition(bigenemie.xenemie, bigenemie.yenemie);
    bigenemietxt.setScale(0.8f, 0.72f);

    waytoroom1f.setPosition(waytoroom1.xplattform, waytoroom1.yplattform);
    waytoroom1f.setScale(0.2f, 0.2f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (playertxt.getGlobalBounds().intersects(waytoroom1f.getGlobalBounds())) {
            player1.yplayer = waytoroom1.yplattform - 75.0f;
        }
        
        if (playertxt.getGlobalBounds().intersects(plattformtxt.getGlobalBounds()) && inroom1) {
            player1.yplayer = plattform.yplattform - 75.0f;
        }

        if (player1.xplayer > rightsite && inroom1) {
            player1.xplayer -= 100.0f;
            HP -= 1;
            Dies.setString(std::string("HP : ") + std::to_string(HP));
            outofbounce.play();
        }

        if (player1.xplayer > rightsite) {
            player1.xplayer = leftsite;
            inroom1 = true;
            if (clock.getElapsedTime().asSeconds() >= 1.0f) {
                showenemie = true;
                clock.restart();
            }
        } else if (player1.xplayer < leftsite && inroom1) {
            player1.xplayer = rightsite;
            inroom1 = false;
            showenemie = false;
        } else if (player1.xplayer < leftsite && !inroom1) {
            player1.xplayer += 100.0f;
            HP -= 1;
            Dies.setString(std::string("HP : ") + std::to_string(HP));
            outofbounce.play();
        }

        if (player1.xplayer > smallenemie.xenemie && player1.xplayer < bigenemie.xenemie) {
            if (player1.jumpstrengh > 150.0f) {
                player1.jumpstrengh = 150.0f;
            }
        }

        if (showenemie) {
            smallenemie.xenemie -= 0.02f;
            smallenemietxt.setPosition(smallenemie.xenemie, smallenemie.yenemie);

            bigenemie.xenemie -= 0.02f;
            bigenemietxt.setPosition(bigenemie.xenemie, bigenemie.yenemie);

            if (playertxt.getGlobalBounds().intersects(smallenemietxt.getGlobalBounds())) {
                outofbounce.play();
                HP = 0;
            }

            if (playertxt.getGlobalBounds().intersects(bigenemietxt.getGlobalBounds())) {
                outofbounce.play();
                HP = 0;
            }
        }

        if (player1.yplayer == ground.yplattform - 75.0f) {
            onground = true;
        }

        if (showplayer) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player1.xplayer -= player1.playerspeed;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player1.xplayer += player1.playerspeed;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                if (!isjumping && onground || !isjumping && player1.yplayer == yplayeronwaytoroom1 || !isjumping && player1.yplayer == yplayeronplattform) {
                    isjumping = true;
                    onground = false;
                }
            }
        }

        if (isjumping) {
            player1.yplayer -= player1.velocityYplayer;

            if (player1.yplayer <= player1.jumpstrengh) {
                isjumping = false;
            }
        } else if (!onground) {
            player1.yplayer += player1.velocityYplayer;

            if (player1.yplayer >= ground.yplattform - 75.0f) {
                player1.yplayer = ground.yplattform - 75.0f;
                onground = true;
            }
        }

        playertxt.setPosition(player1.xplayer, player1.yplayer);

        if (player1.xplayer > 925.0f || player1.xplayer < 4.0f || smallenemietxt.getGlobalBounds().intersects(waytoroom1f.getGlobalBounds()) || bigenemietxt.getGlobalBounds().intersects(waytoroom1f.getGlobalBounds())) {
            if (smallenemietxt.getGlobalBounds().intersects(waytoroom1f.getGlobalBounds())) {
                smallenemie.xenemie = 1000.0f;
                smallenemietxt.setPosition(smallenemie.xenemie, smallenemie.yenemie);
            }

            if (bigenemietxt.getGlobalBounds().intersects(waytoroom1f.getGlobalBounds())) {
                bigenemie.xenemie = 1000.0f;
                bigenemietxt.setPosition(bigenemie.xenemie, bigenemie.yenemie);
            }
        }

        if (HP <= 0) {
            showplayer = false;
            showenemie = false;

            GameOver.setFont(font);
            GameOver.setString("GameOver");
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

        if (showplayer) {
            if (!inroom1) {
                waytoroom1f.setPosition(waytoroom1.xplattform, waytoroom1.yplattform);
                window.draw(waytoroom1f);
            } else if (inroom1) {
                waytoroom1f.setPosition(waytoroom1.xplattform - 870, waytoroom1.yplattform);
                window.draw(waytoroom1f);
            }
        }
        if (showplayer) {
            if (inroom1) {
                window.draw(plattformtxt);
            }
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