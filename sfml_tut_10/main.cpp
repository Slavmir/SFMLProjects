#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <cmath>
#include <vector>

//LENGTH_OF_VECTOR: |V| = sqrt(V.x^2 + V.y^2)
//NORMALIZE VECTOR: U = V / |V|

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "360 Shooter!");
    sf::CircleShape player;
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


        //Draw
        window.clear();

        window.display();
    }

    return 0;
}