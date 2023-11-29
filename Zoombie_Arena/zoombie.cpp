#include "zoombie.hpp"
#include "textureHolder.hpp"
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

void Zoombie::spawn(float startX, float startY, int type, int seed)
{
    switch (type)
    {
    case 0:
        m_sprite.setTexture(TextureHolder::getTexture("graphics/bloater.png"));
        m_speed = BLOATER_SPEED;
        m_health = BLOATER_SPEED;
        break;

    case 1:
        m_sprite.setTexture(TextureHolder::getTexture("graphics/chaser.png"));
        m_speed = CHASER_SPEED;
        m_health = CHASER_HEALTH;
        break;
    
    case 3:
    m_sprite.setTexture(TextureHolder::getTexture("graphics/crawler.png"));
    m_speed = CRAWLER_SPEED;
    m_health = CRAWLER_HEALTH;
    default:
        break;
    }
    srand((int) time(0) * seed);
    float modifier = (rand() % MAX_VARIANCE)  + OFFSET;
    modifier /= 100;
    m_speed *= modifier; //Make each Zoombie unique;
    m_position.x = startX;
    m_position.y = startY;
    m_sprite.setOrigin(Vector2f(25, 25));
    m_sprite.setPosition(m_position);
}

bool Zoombie::hit()
{
    m_health --;
    if(m_health <=0)
    {
        m_alive = false;
        m_sprite.setTexture(TextureHolder::getTexture("graphics/blood.png"));
        return true;
    }
    return false; // Still alive;
}

bool Zoombie::isAlive()
{
    return m_alive;
}

FloatRect Zoombie::getPosition()
{
    return m_sprite.getGlobalBounds();
}

Sprite Zoombie::getSprite()
{
    return m_sprite;
}

void Zoombie::update(float elapsedTime, Vector2f playerLocation)
{
    float playerX = playerLocation.x;
    float playerY = playerLocation.y;

    if(playerX > m_position.x)
    {
        m_position.x += m_speed * elapsedTime;
    }

    if(playerX < m_position.x)
    {
        m_position.x -= m_speed * elapsedTime;
    }

    if (playerY > m_position.y)
    {
        m_position.y += m_speed * elapsedTime;
    }

    if (playerY < m_position.y)
    {
        m_position.y -= m_speed * elapsedTime;
    }

    m_sprite.setPosition(m_position);
    float angle = atan2(playerY - m_position.y, playerX-m_position.y) * (180 / M_PI);
    m_sprite.setRotation(angle);
}