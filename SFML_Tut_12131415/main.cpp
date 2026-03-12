#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Bullet
{
public:
    sf::Sprite shape;

    Bullet(sf::Texture* texture, sf::Vector2f pos) {
        this->shape.setTexture(*texture);
        this->shape.setScale(0.12f, 0.12f);
        this->shape.setPosition(pos);
    }

    ~Bullet() {}
};

class Player
{
public:
    sf::Sprite shape;
    sf::Texture* texture;
    int HP;
    int HPMax;

    std::vector<Bullet> bullet;

    Player(sf::Texture *texture) {
        this->HPMax = 10; 
        this->HP = this->HPMax;

        this->texture = texture;
        this->shape.setTexture(*texture);

        this->shape.setScale(0.23f, 0.23f);
    }
    ~Player() {}
};

class Enemy
{
public:
    sf::Sprite shape;

    int HP;
    int HPMax;

    Enemy(sf::Texture* texture, sf::Vector2u windowSize) {
        this->HPMax = rand() % 3 + 1;
        this->HP = this->HPMax;
        this->shape.setTexture(*texture);
        this->shape.setScale(0.23f, 0.23f);
        this->shape.setPosition(windowSize.x - this->shape.getGlobalBounds().width, rand() % (int)(windowSize.y - this->shape.getGlobalBounds().height));
    }
    ~Enemy() {}

};


int main()
{

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "3D shooter!");
    window.setFramerateLimit(60);

    //Init text
    sf::Font font;
    font.loadFromFile("C:/Users/SJani/source/repos/SFMLProjects/SFML_Tut_12131415/sfmlSetup/Fonts/Dosis-Light.ttf");

    //Init Textures
    sf::Texture playerTex;
    playerTex.loadFromFile("C:/Users/SJani/source/repos/SFMLProjects/SFML_Tut_12131415/sfmlSetup/Textures/toppng.com-spaceship-png-548x754.png");

    sf::Texture enemyTex;
    enemyTex.loadFromFile("C:/Users/SJani/source/repos/SFMLProjects/SFML_Tut_12131415/sfmlSetup/Textures/toppng.com-spaceship-fighter-ipod-opengameart-space-ship-2d-422x372.png");

    sf::Texture missileTex;
    missileTex.loadFromFile("C:/Users/SJani/source/repos/SFMLProjects/SFML_Tut_12131415/sfmlSetup/Textures/toppng.com-missile-png-600x3198.png");

    //UI Text
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10.f, 10.f);
    
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(55);
    gameOverText.setFillColor(sf::Color::Cyan);
    gameOverText.setPosition(150.f, window.getSize().y / 2);
    gameOverText.setString("GAME OVER");

    //Player init
    int score = 0;
    Player player(&playerTex);
    int shootTimer = 20;
    sf::Text hpText;
    hpText.setFont(font);
    hpText.setCharacterSize(12);
    hpText.setFillColor(sf::Color::White);

    //Enemy init
    int enemySpawnTimer = 0;
    std::vector <Enemy> enemies;
    sf::Text eHpText;
    eHpText.setFont(font);
    eHpText.setCharacterSize(12);
    eHpText.setFillColor(sf::Color::Red);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        if (player.HP > 0) {
            //Player
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                player.shape.move(0.f, -10.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                player.shape.move(0.f, 10.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                player.shape.move(-5.f, 0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                player.shape.move(5.f, 0.f);

            hpText.setPosition(player.shape.getPosition().x, player.shape.getPosition().y - hpText.getGlobalBounds().height);
            hpText.setString(std::to_string(player.HP) + "/" + std::to_string(player.HPMax));

            //player collision with window
            if (player.shape.getPosition().x <= 0) //Left
                player.shape.setPosition(0.f, player.shape.getPosition().y);

            if (player.shape.getPosition().x >= window.getSize().x - player.shape.getGlobalBounds().width) //Right
                player.shape.setPosition(window.getSize().x - player.shape.getGlobalBounds().width, player.shape.getPosition().y);

            if (player.shape.getPosition().y <= 0) //Top
                player.shape.setPosition(player.shape.getPosition().x, 0.f);

            if (player.shape.getPosition().y >= window.getSize().y - player.shape.getGlobalBounds().height) //Bottom
                player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);

            //UPDATE CONTROLS
            if (shootTimer < 20)
                shootTimer++;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootTimer >= 20) { //shooting
                player.bullet.push_back(Bullet(&missileTex, player.shape.getPosition()));
                shootTimer = 0;
            }

            //Erase bullet when out of the right side of screen
            for (size_t i = 0; i < player.bullet.size(); i++) {
                //Move bullet
                player.bullet[i].shape.move(17.f, 0.f);

                //out of window bounds
                if (player.bullet[i].shape.getPosition().x > window.getSize().x)
                    player.bullet.erase(player.bullet.begin() + i);

                //Enemy collision
                for (size_t k = 0; k < enemies.size(); k++) {
                    if (player.bullet[i].shape.getGlobalBounds().intersects(enemies[k].shape.getGlobalBounds())) {
                        if (enemies[k].HP <= 1) {
                            score += enemies[k].HPMax;
                            enemies.erase(enemies.begin() + k);
                        }
                        else
                            enemies[k].HP--; //take DMG

                        enemies.erase(enemies.begin() + k);
                        player.bullet.erase(player.bullet.begin() + i);
                        break;
                    }
                }
            }

            //Enemy collision

            //Enemy
            if (enemySpawnTimer < 25)
                enemySpawnTimer++;

            //Enemy spawn
            if (enemySpawnTimer >= 25) {
                enemies.push_back(Enemy(&enemyTex, window.getSize()));
                enemySpawnTimer = 0;
            }


            //enemy moving
            for (size_t i = 0; i < enemies.size(); i++) {
                enemies[i].shape.move(-5.f, 0.f);

                if (enemies[i].shape.getPosition().x <= 0 - enemies[i].shape.getGlobalBounds().width) {
                    enemies.erase(enemies.begin() + i);
                    break;
                }

                if (enemies[i].shape.getGlobalBounds().intersects(player.shape.getGlobalBounds())) {
                    enemies.erase(enemies.begin() + i);
                    player.HP--; //dmg to player
                    break;
                }
            }

            //-----END-OF-UPDDATE----
            //UI update 
            scoreText.setString("Score: " + std::to_string(score));
        }
        //##########################DRAW#####################################
        window.clear();

        

        //player
        window.draw(player.shape);
        //bullets
        for (size_t i = 0; i < player.bullet.size(); i++) {
            window.draw(player.bullet[i].shape);
        }

        //enemy
        for (size_t i = 0; i < enemies.size(); i++) {
            eHpText.setString(std::to_string(enemies[i].HP) + "/" + std::to_string(enemies[i].HPMax));
            eHpText.setPosition(enemies[i].shape.getPosition().x, enemies[i].shape.getPosition().y - eHpText.getGlobalBounds().height);
            window.draw(eHpText);

            window.draw(enemies[i].shape);
        }

        //UI
        window.draw(hpText);
        window.draw(scoreText);
        if (player.HP <= 0)
            window.draw(gameOverText);
        window.display();
        //-----END-OF-DRAW-------
    }

    return 0;
}