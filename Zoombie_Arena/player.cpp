#include "player.hpp"
#include <iostream>
#include <cmath>
Player:: Player(){
    m_speed = START_SPEED;
    m_health = START_HEALTH;
    m_maxHealth = START_HEALTH;
    if (!m_texture.loadFromFile("graphics/player.png")) {
    std::cerr << "Failed to load player.png" << std::endl;
    }

    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);
}

void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize){
    m_position.x = arena.left + arena.width / 2;
    m_position.y = arena.top + arena.height / 2; //Place the player in the middle of the arena

    m_arena.left = arena.left;
    m_arena.width = arena.width;
    m_arena.top = arena.top;
    m_arena.height = arena.height;
    m_tileSize = tileSize;
    m_resolution.x = resolution.x;
    m_resolution.y = resolution.y;
    m_sprite.setPosition(m_position);
}

void Player::resetPlayerStats(){
    m_speed = START_SPEED;
    m_health = START_HEALTH;
    m_maxHealth = START_HEALTH;
}
bool Player::hit(sf::Time timeHit){
    if (timeHit.asMilliseconds() - m_lastHit.asMilliseconds() > 200){
        m_lastHit = timeHit;
        m_health -= 10;
        return true;
    }
    else{
        return false;
    }
}

sf::Time Player::getLastHitTime(){
    return m_lastHit;
}
sf::Sprite Player::getSprite(){
    return m_sprite;
}

sf::FloatRect Player::getPosition(){
    return m_sprite.getGlobalBounds();
}

sf::Vector2f Player::getCenter(){
    return m_position;
}

float Player::getRotation(){
    return m_sprite.getRotation();
}

void Player::moveLeft(){
    m_movingLeft = true;
    
}

void Player::moveRight(){
    m_movingRight = true;
    
}

void Player::moveUp(){
    m_movingUp = true;
    
}

void Player::moveDown(){
    m_movingDown = true;
    
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

void Player::upgradeSpeed(){
    m_speed += (START_SPEED * 0.2f);
}
void Player::upgradeHealth(){
    m_health += (START_HEALTH * 0.2f);
}
void Player::increaseHealthLevel(int amount){
    m_health += amount;
    if (m_health > m_maxHealth){
        m_health = m_maxHealth;
    }
}
int Player::getHealth(){
    return m_health;

}
void Player::update(float elapsedTime, sf::Vector2i mousePosition){
    if (m_movingLeft){
        m_position.x -= elapsedTime * m_speed;
    }
    if (m_movingRight){
        m_position.x += elapsedTime * m_speed;
    }
    if (m_movingUp){
        m_position.y -= elapsedTime * m_speed;
    }
    if(m_movingDown){
        m_position.y += elapsedTime * m_speed;
    }
    m_sprite.setPosition(m_position);

    // To do: set border of the player
    if (m_position.x > (m_arena.width - m_tileSize) || m_position.x < (m_arena.left + m_tileSize)){
        m_position.x = std::max((float) m_arena.left + m_tileSize, std::min(m_position.x, (float)m_arena.width - m_tileSize));
    }
    
    if (m_position.y > (m_arena.height - m_tileSize) || m_position.y < m_arena.top + m_tileSize){
        m_position.y = std::max((float) (m_arena.top + m_tileSize),  
                        std::min(m_position.y, (float)(m_arena.height - m_tileSize)));
    }
    
    float angle = (atan2(mousePosition.y - m_resolution.y /2, mousePosition.x - m_resolution.x)/2) * (180.0f / M_PI);
    m_sprite.setRotation(angle);
}