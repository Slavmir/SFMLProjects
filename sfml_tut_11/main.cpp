#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

//font Cornelia-BF64e2efc8d82d7

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text intro!", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::Font font;
    
    if (!font.loadFromFile("Fonts/Cornelia-BF64e2efc8d82d7.otf"))
        throw ("COULD NOT OPEN FONT!");

    //set -> draw below
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold);
    text.setString("HEY THERE SFML OPERATOR!");


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


        //DRAW
        window.clear();

        //Draw text
        window.draw(text);

        window.display();
    }

    return 0;
}