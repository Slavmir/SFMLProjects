#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cmath>
#include <vector>

//LENGTH_OF_VECTOR: |V| = sqrt(V.x^2 + V.y^2)
//NORMALIZE VECTOR: U = V / |V|

class Bullet
{
public:
    sf::CircleShape shape;
    sf::Vector2f currentVelocity;
    float maxSpeed;

    Bullet(float radius = 5.f)
        : currentVelocity(0.f, 0.f), maxSpeed(15.f) {
        this->shape.setRadius(radius);
        this->shape.setFillColor(sf::Color::Red);
    }
};

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "360 Shooter!");
    window.setFramerateLimit(60);

    //Player
    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::White);

    //Bullet
    Bullet b1;
    std::vector<Bullet> bullets;
    //bullets.push_back(Bullet(b1));

    //Enemy
    sf::RectangleShape enemy;
    std::vector<sf::RectangleShape> enemies;
    int spawnCounter = 20;
    enemy.setFillColor(sf::Color::Magenta);
    enemy.setSize(sf::Vector2f(22.f, 22.f));

    //Vectors
    sf::Vector2f playerCenter, mousePosWindow, aimDir, aimDirNormalised;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        //Update

        //Vectors
        playerCenter = sf::Vector2f(player.getPosition().x + player.getRadius(), player.getPosition().y + player.getRadius());
        mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
        aimDir = mousePosWindow - playerCenter;
        float length = std::sqrt(aimDir.x * aimDir.x + aimDir.y * aimDir.y);
        aimDirNormalised = aimDir / length;

        //Player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.move(-10.f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(10.f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0.f, 10.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0.f, -10.f);

        //Enemies
        if (spawnCounter < 20)
            spawnCounter++;

        if (spawnCounter >= 20 && enemies.size() < 50) {
            enemy.setPosition(rand() % window.getSize().x, rand() % window.getSize().y);
            enemies.push_back(sf::RectangleShape(enemy));
            spawnCounter = 0;
        }

        //Shooting
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            b1.shape.setPosition(playerCenter);
            b1.currentVelocity = aimDirNormalised * b1.maxSpeed;
            bullets.push_back(Bullet(b1));
        }

        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].shape.move(bullets[i].currentVelocity);
            if (bullets[i].shape.getPosition().x < 0 || bullets[i].shape.getPosition().x > window.getSize().x
                || bullets[i].shape.getPosition().y < 0 || bullets[i].shape.getPosition().y > window.getSize().y){
                bullets.erase(bullets.begin() + i);
                }
            std::cout << bullets.size() << "\n";
        }

        
        std::cout << aimDirNormalised.x << " " << aimDirNormalised.y << std::endl;

        //Draw
        window.clear();

        for (size_t i = 0; i < enemies.size(); i++) {
            window.draw(enemies[i]);
        }

        window.draw(player);

        for (size_t i = 0; i < bullets.size(); i++) {
            window.draw(bullets[i].shape);
        }
        window.draw(enemy);

        window.display();
    }

    return 0;
}