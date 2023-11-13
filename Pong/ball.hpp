#pragma once
#include <SFML/Graphics.hpp>

class Ball{
private:
    sf::Vector2f m_position;
    sf::RectangleShape m_shape;
    float m_speed = 500;
    float m_DirectionX = .2f;
    float m_DirectionY = .2f;
public:
    Ball(float startX, float startY);
    sf::RectangleShape getShape();
    sf::FloatRect      getPosition();
    float getXVelocity();
    void  reboundsSides();
    void  reboundsBatorTop();
    void  reboundsBottom(float width);
    void  update(sf::Time dt);
};