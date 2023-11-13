#include "bat.hpp"
#include <SFML/Graphics.hpp>

Bat::Bat(float start_x, float start_y){
    m_position.x = start_x;
    m_position.y = start_y;
    sf::Vector2f size(50.0f, 5.0f);
    m_shape.setSize(size);
    m_shape.setPosition(m_position.x, m_position.y);
    

}

sf::FloatRect Bat::getPosition(){
    return m_shape.getGlobalBounds();
}

sf::RectangleShape Bat::getShape(){
    return m_shape;
}

void Bat::moveLeft(){
    m_MovingLeft = true;
}

void Bat::moveRight(){
    m_MovingRight = true;
}

void Bat::stopLeft(){
    m_MovingLeft = false;
}

void Bat::stopRight(){
    m_MovingRight =false;
}

void Bat::update(sf::Time dt){
    if (m_MovingLeft)
    {
        m_position.x -= m_speed *dt.asSeconds();
    }
    else if (m_MovingRight){
        m_position.x += m_speed * dt.asSeconds();
    }
    m_shape.setPosition(m_position.x, m_position.y);
}