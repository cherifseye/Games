#include "ball.hpp"

Ball::Ball(float startX, float startY){
    m_position.x = startX;
    m_position.y = startY;
    m_shape.setSize(sf::Vector2f(10.0f, 10.0f));
    m_shape.setPosition(m_position);
    m_shape.setFillColor(sf::Color::Red);
}

sf::RectangleShape Ball::getShape(){
    return m_shape;
}
sf::FloatRect Ball::getPosition(){
    return m_shape.getGlobalBounds();
}

float Ball::getXVelocity(){
    return m_DirectionX;
}

void Ball::reboundsSides(){
    m_DirectionX = -m_DirectionX;
}

void Ball::reboundsBatorTop(){
    m_DirectionY = -m_DirectionY;
}

void Ball::reboundsBottom(float width){
    m_position.x = width/2.0f;
    m_position.y = 0;
    m_DirectionY = -m_DirectionY;

}

void Ball::update(sf::Time dt){
    m_position.x += m_speed * m_DirectionX * dt.asSeconds();
    m_position.y += m_speed * m_DirectionY * dt.asSeconds();
    m_shape.setPosition(m_position);
}