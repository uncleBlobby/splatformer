#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <iostream>
#include "game.h"
#include "player.h"

Splatformer::Player player;

const sf::Vector2 GRAVITY = sf::Vector2f(0.f, 50.f);


void drawGroundBox(float width, float height, sf::Vector2f origin, sf::RenderWindow &window);

void drawEnemyRectangle(sf::RectangleShape enemyRect, sf::RenderWindow &window);
sf::RectangleShape initEnemyRect(sf::Vector2f position);
void update(float delta, sf::RenderWindow &window, Splatformer::Player &player);

void movePlayer(Splatformer::Player &player, float delta);
void inputController(Splatformer::Player &player, float delta);

void stopPlayerMovement(Splatformer::Player &player);


int main()
{
    player.init();
    // create the window
    sf::RenderWindow window(sf::VideoMode(Splatformer::SCREEN_SIZE.x, Splatformer::SCREEN_SIZE.y), "SplatFormer");
    window.setFramerateLimit(60);

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
    
    sf::Time elapsed = clock.restart();
    float delta = elapsed.asSeconds();
    update(delta, window, player);

    }
    return 0;
}

void update(float delta, sf::RenderWindow &window, Splatformer::Player &player)
{
    window.clear(sf::Color::Black);
    drawGroundBox(Splatformer::SCREEN_SIZE.x, 200.f, sf::Vector2f(0.f, 800.f), window);

    //check collisions!
    /*
    sf::RectangleShape currentPlayer = player.getShape();
    sf::RectangleShape currentEnemy = initEnemyRect((sf::Vector2f(1200.f, 800.f)));
    if(currentPlayer.getGlobalBounds().intersects(currentEnemy.getGlobalBounds()))
    {
        stopPlayerMovement(player);
    }
    */ 
    player.inputController(delta);
    //inputController(player, delta);
    drawEnemyRectangle(initEnemyRect(sf::Vector2f(1200.f, 800.f)), window);
    player.draw(window);

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

/*
void inputController(Splatformer::Player &player, float delta)
{
    if (player.position.y + player.size.y >= 800.f)
    {
        player.setPosition(sf::Vector2f(player.position.x, 800.f - player.size.y));
        player.isGrounded = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player.setVelocity(sf::Vector2f(50.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player.setVelocity(sf::Vector2f(-50.f, 0.f));
    }
    if (player.isGrounded && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player.setVelocity(sf::Vector2f(0.f, -1000.f));
        player.isGrounded = false;

    }

    player.affectFriction(player.velocity);

    player.setPosition(player.velocity, delta);


    if(player.isGrounded == false)
    {

        player.affectGravity(player.velocity);
        std::cout << "player position y: " << player.position.y << std::endl;
    }
        


}
*/
void stopPlayerMovement(Splatformer::Player &player)
{
    player.velocity = sf::Vector2f(0.f, 0.f);
}
