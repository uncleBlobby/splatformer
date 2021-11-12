#include <SFML/Graphics.hpp>
namespace Splatformer
{
    class Platform
    {
        public:
        sf::Vector2f size = size;
        sf::Vector2f position = position;
        //sf::Vector2f velocity = velocity;     enable for mobile platforms?
        sf::Color color = color;
        void init(sf::Vector2f size, sf::Vector2f position);
        sf::RectangleShape getShape();
        void draw(sf::RenderWindow &window);
    };
};