#pragma once
#include <SFML/Graphics.hpp>
class Bat{

public:
    Bat(float start_x, float start_y);
    sf::FloatRect getPosition();
    sf::RectangleShape getShape();
    void moveLeft();
    void moveRight();
    void stopLeft();
    void stopRight();
    void update(sf::Time dt);

private:
    float m_speed = 1000.0f;
    sf::Vector2f m_position;
    sf::RectangleShape m_shape;
    bool m_MovingRight = false;
    bool m_MovingLeft  = false;
};