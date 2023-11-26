#pragma once
#include <SFML/Graphics.hpp>

class Player{
private:
   const float START_SPEED  = 200;
   const float START_HEALTH = 100;

   sf::Sprite m_sprite;
   sf::Texture m_texture;

   sf::Vector2f m_position;
   sf::Vector2f m_resolution; //Screen resolution

   sf::IntRect m_Arena;

   int m_TileSize; // Size of each tile
   bool m_movingLeft = false;
   bool m_movingRight = false;
   bool m_movingDown = false;
   bool m_movingUp = false;
   float m_speed = 100.0f;

   int m_health;
   int m_maxHealth;

   sf::Time m_lastHit;

public:
   Player(float startX, float startY);
   void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
   void resetPlayerStats();
   bool hit(sf::Time timeHit);
   sf::Time getLastHitTime();
   sf::Sprite getSprite();
   sf::FloatRect getPosition();
   sf::Vector2f getCenter();
   float getRotation();
   void moveLeft();
   void moveRight();
   void moveUp();
   void moveDown();
   void stopLeft();
   void stopRight();
   void stopUp();
   void stopDown();
   void update(float elapsedTime, sf::Vector2f mousePosition);
   void upgradeSpeed();
   void upgradeHealth();
   void increaseHealthLevel(int amount);
   int getHealth();
};
