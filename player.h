#include <SFML/Graphics.hpp>
namespace Splatformer
{
    class Player 
    {
        public:
            sf::Vector2f size = size;
            sf::Vector2f position = position;
            sf::Vector2f velocity = velocity;
            sf::Color color = color;    
            float speed = speed;
            float friction = friction;
            bool isGrounded = isGrounded;
            void init();
            sf::RectangleShape getShape();
            void draw(sf::RenderWindow &window);
            void setPosition(sf::Vector2f position);
            void setPosition(sf::Vector2f velocity, float delta);
            void affectFriction(sf::Vector2f &velocity);
            void affectGravity(sf::Vector2f &velocity);
            void setVelocity(sf::Vector2f changeVelocity);
            void inputController(float delta);
            void stopMovement(sf::Vector2f &velocity);
    };
};