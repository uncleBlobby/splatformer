#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <iostream>

const sf::Vector2 SCREEN_SIZE = sf::Vector2f(1600.f, 900.f);

const sf::Vector2 GRAVITY = sf::Vector2f(0.f, 50.f);

struct Player {
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    float friction;
    float jumpHeight;
    bool isGrounded;
    bool isJumping;
};

Player player;


void initPlayer(Player &player){
    player.position.x = SCREEN_SIZE.x / 2.f;
    player.position.y = SCREEN_SIZE.y / 2.f;
    player.size = sf::Vector2f(25.f, 25.f);
    player.velocity = sf::Vector2f(0.f, 0.f);
    player.speed = 2.f;
    player.friction = 0.94f;
    player.jumpHeight = 500.f;
    bool isGrounded = false;
    bool isJumping = false;
}

void drawGroundBox(float width, float height, sf::Vector2f origin, sf::RenderWindow &window);

void drawPlayer(sf::RectangleShape playerRect, sf::RenderWindow &window);
sf::RectangleShape initPlayerRect(sf::Vector2f position);
void drawEnemyRectangle(sf::RectangleShape enemyRect, sf::RenderWindow &window);
sf::RectangleShape initEnemyRect(sf::Vector2f position);
void update(float delta, sf::RenderWindow &window, Player &player);

void movePlayer(Player &player, float delta);
void inputController(Player& player, float delta);

void stopPlayerMovement(Player &player);


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y), "SplatFormer");
    window.setFramerateLimit(60);

    sf::Clock clock;

    initPlayer(player);

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

void update(float delta, sf::RenderWindow &window, Player &player)
{
    window.clear(sf::Color::Black);
    drawGroundBox(SCREEN_SIZE.x, 200.f, sf::Vector2f(0.f, 800.f), window);

    //check collisions!
    sf::RectangleShape currentPlayer = initPlayerRect((player.position));
    sf::RectangleShape currentEnemy = initEnemyRect((sf::Vector2f(1200.f, 800.f)));
    if(currentPlayer.getGlobalBounds().intersects(currentEnemy.getGlobalBounds()))
    {
        stopPlayerMovement(player);
    } 
    inputController(player, delta);
    drawEnemyRectangle(initEnemyRect(sf::Vector2f(1200.f, 800.f)), window);
    drawPlayer(initPlayerRect(player.position), window);

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

void drawPlayer(sf::RectangleShape playerRect, sf::RenderWindow &window)
{
    window.draw(playerRect);
}

sf::RectangleShape initPlayerRect(sf::Vector2f position)
{
    sf::RectangleShape playerRect(sf::Vector2f(25.f, 25.f));
    playerRect.setPosition(position.x, position.y);
    playerRect.setFillColor(sf::Color::Red);
    return playerRect;
}


void inputController(Player& player, float delta)
{
    if (player.position.y + player.size.y >= 800.f)
    {
        player.position.y = 800.f - player.size.y;
        player.isGrounded = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player.velocity += sf::Vector2f(50.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player.velocity -= sf::Vector2f(50.f, 0.f);
    }
    if (player.isGrounded && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        player.velocity -= sf::Vector2f(0.f, 1000.f);
        player.isGrounded = false;

    }

    //player.velocity.x *= player.speed;
    
    player.velocity *= player.friction;

    player.position += player.velocity * delta;


    if(player.isGrounded == false)
        player.velocity += GRAVITY;


}

void stopPlayerMovement(Player &player)
{
    player.velocity = sf::Vector2f(0.f, 0.f);
}
