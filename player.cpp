#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "game.h"
#include "player.h"
#include <iostream>

using namespace Splatformer;

void Player::init()
{
    size = sf::Vector2f(25.f, 25.f);
    position = sf::Vector2f(SCREEN_SIZE.x/2, SCREEN_SIZE.y/2);
    velocity = sf::Vector2f(0.f, 0.f);
    color = sf::Color::Red;
    speed = 2.f;
    friction = 0.94f;
    isGrounded = false;
}

sf::RectangleShape Player::getShape()
{
    sf::RectangleShape shape(sf::Vector2f(25.f, 25.f));
    shape.setPosition(this->position.x, this->position.y);
    shape.setFillColor(this->color);
    return shape;
}

void Player::draw(sf::RenderWindow &window)
{
    sf::RectangleShape shape(sf::Vector2f(this->size.x, this->size.y));
    shape.setPosition(this->position.x, this->position.y);
    shape.setFillColor(this->color);
    window.draw(shape);
}

void Player::setPosition(sf::Vector2f velocity, float delta)
{
    this->position += velocity * delta;
}

void Player::setPosition(sf::Vector2f position)
{
    this->position = sf::Vector2f(this->position.x, 800.f - this->size.y);
}

void Player::affectFriction(sf::Vector2f &velocity)
{
    this->velocity.x *= this->friction;
    this->velocity.y *= this->friction;
}

void Player::affectGravity(sf::Vector2f &velocity)
{
    this->velocity.y += 50.f;
}
void Player::setVelocity(sf::Vector2f changeVelocity)
{
    this->velocity += changeVelocity;
}

void Player::inputController(float delta)
{
    if (this->position.y + this->size.y >= 800.f)
    {
        this->setPosition(sf::Vector2f(this->position.x, 800.f - this->size.y));
        this->isGrounded = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->setVelocity(sf::Vector2f(50.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->setVelocity(sf::Vector2f(-50.f, 0.f));
    }
    if (this->isGrounded && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->setVelocity(sf::Vector2f(0.f, -2000.f));
        this->isGrounded = false;
    }

    this->affectFriction(this->velocity);

    this->setPosition(this->velocity, delta);

    if(this->isGrounded == false)
    {
        this->affectGravity(this->velocity);
    }     
}

void Player::stopMovement(sf::Vector2f &velocity)
{
    this->velocity = sf::Vector2f(0.f, 0.f);
}

void Player::setGrounded(sf::Vector2f &velocity)
{
    if((this->velocity.y < 0.1f) || (this->velocity.y > -0.1f))
    {
        this->isGrounded = true;
        this->velocity.y = 0.f;
    }
}
