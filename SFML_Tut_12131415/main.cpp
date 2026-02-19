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

    Bullet(sf::Texture* texture) {
        this->shape.setTexture(*texture);
        this->shape.setScale(0.12f, 0.12f);
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

    //Player init
    Player player(&playerTex);

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

        //Player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.shape.move(0.f, -10.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.shape.move(0.f, 10.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.shape.move(-5.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.shape.move(5.f, 0.f);
        
        //player collision with window
        if (player.shape.getPosition().x <= 0) //Left
            player.shape.setPosition(0.f, player.shape.getPosition().y);

        else if (player.shape.getPosition().x >= window.getSize().x) //Right
            player.shape.setPosition(window.getSize().x + player.shape.getGlobalBounds().width, player.shape.getPosition().y);

        else if (player.shape.getPosition().y <= 0) //Top
            player.shape.setPosition(player.shape.getPosition().y, 0.f);

        else if (player.shape.getPosition().y >= window.getSize().y) //Bottom
            player.shape.setPosition(player.shape.getPosition().x, window.getSize().y - player.shape.getGlobalBounds().height);

        //UPDATE
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { //shooting
            player.bullet.push_back(Bullet(&missileTex));
        }
        //Bullets
        //erase bullet when out of the right side of screen
        for (size_t i = 0; player.bullet.size(); i++) {
            if (player.bullet[i].shape.getPosition().x > window.getSize().x)
                player.bullet.erase(player.bullet.begin() + i);
        }

        //Enemy collision

        //Enemy

        //-----END-OF-UPDDATE----
        //DRAW
        window.clear();

        window.draw(player.shape);
        for (size_t i = 0; i < player.bullet.size(); i++) {
            window.draw(player.bullet[i].shape);
        }

        window.display();
        //-----END-OF-DRAW-------
    }

    return 0;
}