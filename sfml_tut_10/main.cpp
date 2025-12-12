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
            : currentVelocity(0.f, 0.f), maxSpeed(15.f){
            this->shape.setRadius(radius);
            this->shape.setFillColor(sf::Color::Red);
        }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "360 Shooter!");
    window.setFramerateLimit(60);
    sf::CircleShape player(25.f);
    player.setFillColor(sf::Color::White);

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
            player.move(-.f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.move(10.f, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.move(0.f, 10.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.move(0.f,-10.f);


        
        std::cout << aimDirNormalised.x << " " << aimDirNormalised.y << std::endl;

        //Draw
        window.clear();

        window.draw(player);

        window.display();
    }

    return 0;
}