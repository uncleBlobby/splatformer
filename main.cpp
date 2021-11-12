#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <iostream>
#include "game.h"
#include "player.h"

Splatformer::Player player;
const sf::Vector2 GRAVITY = sf::Vector2f(0.f, 50.f);

// TODO: convert ground objects to class type
void drawGroundBox(float width, float height, sf::Vector2f origin, sf::RenderWindow &window);

// TODO: convert enemy to class type
void drawEnemyRectangle(sf::RectangleShape enemyRect, sf::RenderWindow &window);
sf::RectangleShape initEnemyRect(sf::Vector2f position);

// declare update function
void update(float delta, sf::RenderWindow &window, Splatformer::Player &player);

int main()
{
    player.init();
    // create the window
    sf::RenderWindow window(sf::VideoMode(Splatformer::SCREEN_SIZE.x, Splatformer::SCREEN_SIZE.y), "SplatFormer");
    window.setFramerateLimit(60);

    // init clock for frame timer
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
    
        // reset clock every frame
        sf::Time elapsed = clock.restart();
        float delta = elapsed.asSeconds();
        update(delta, window, player);
    }
    return 0;
}

// define update function
void update(float delta, sf::RenderWindow &window, Splatformer::Player &player)
{
    window.clear(sf::Color::Black);
    drawGroundBox(Splatformer::SCREEN_SIZE.x, 200.f, sf::Vector2f(0.f, 800.f), window);
    player.inputController(delta);
    drawEnemyRectangle(initEnemyRect(sf::Vector2f(1200.f, 800.f)), window);
    player.draw(window);
    sf::RectangleShape currentEnemy = initEnemyRect((sf::Vector2f(1200.f, 800.f)));
    if(player.getShape().getGlobalBounds().intersects(currentEnemy.getGlobalBounds()))
    {
        player.stopMovement(player.velocity);
    }
    window.display();
}

void drawEnemyRectangle(sf::RectangleShape enemyRect, sf::RenderWindow &window)
{
    window.draw(enemyRect);
}

sf::RectangleShape initEnemyRect(sf::Vector2f position)
{
    sf::RectangleShape enemyRect(sf::Vector2f(50.f, 50.f));
    enemyRect.setPosition(sf::Vector2f(position.x, position.y - 50.f));
    enemyRect.setFillColor(sf::Color::Blue);
    return enemyRect;
}

void drawGroundBox(float width, float height, sf::Vector2f origin, sf::RenderWindow &window)
{
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(origin.x, origin.y);
    rectangle.setOutlineThickness(-1.f);
    rectangle.setOutlineColor(sf::Color::Yellow);
    rectangle.setFillColor(sf::Color::Black);
    //window.draw(rectangle);

    sf::Vertex collider[] = 
    {
        sf::Vertex(sf::Vector2f(origin.x, origin.y)),
        sf::Vertex(sf::Vector2f(origin.x + width, origin.y))
    };

    window.draw(collider, 2, sf::Lines);
}
