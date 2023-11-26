#include "player.hpp"
#include <iostream>
Player:: Player(float startX, float startY){
    m_position.x = startX;
    m_position.y = startY;
    if (!m_texture.loadFromFile("graphics/player.png")) {
    std::cerr << "Failed to load player.png" << std::endl;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
    m_sprite.setPosition(m_position);
}

sf::Sprite Player::getSprite(){
    return m_sprite;
}

sf::FloatRect Player::getPosition(){
    return m_sprite.getGlobalBounds();
}

void Player::moveLeft(){
    m_movingLeft = true;
    m_sprite.setRotation(180);
}

void Player::moveRight(){
    m_movingRight = true;
    m_sprite.setRotation(0);
}

void Player::moveUp(){
    m_movingUp = true;
    m_sprite.setRotation(270);
}

void Player::moveDown(){
    m_movingDown = true;
    m_sprite.setRotation(90);
}

void Player::stopLeft(){
    m_movingLeft = false;
}

void Player::stopRight(){
    m_movingRight = false;
}

void Player::stopUp(){
    m_movingUp = false;
}

void Player::stopDown(){
    m_movingDown = false;
}

void Player::update(sf::Time dt){
    if (m_movingLeft){
        m_position.x -= dt.asSeconds() * m_speed;
    }
    if (m_movingRight){
        m_position.x += dt.asSeconds() * m_speed;
    }
    if (m_movingDown){
        m_position.y += dt.asSeconds() * m_speed;
    }
    if (m_movingUp){
        m_position.y -= dt.asSeconds() * m_speed;
    }
    m_sprite.setPosition(m_position);
}