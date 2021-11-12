#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "game.h"
#include "player.h"
#include "platform.h"
#include <iostream>

using namespace Splatformer;

void Platform::init(sf::Vector2f size, sf::Vector2f position)
{
    this->size = sf::Vector2f(size.x, size.y);
    this->position = sf::Vector2f(position.x, position.y);
    this->color = sf::Color::Green;

}

sf::RectangleShape Platform::getShape()
{
    sf::RectangleShape shape(sf::Vector2f(this->size.x, this->size.y));
    shape.setPosition(this->position.x, this->position.y);
    shape.setFillColor(this->color);
    return shape;
}

void Platform::draw(sf::RenderWindow &window)
{
    window.draw(this->getShape());
}
