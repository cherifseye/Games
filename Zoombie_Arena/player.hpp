#pragma once
#include <SFML/Graphics.hpp>
class Player{
private:
   sf::Sprite m_sprite;
   sf::Texture m_texture;
   sf::Vector2f m_position;
   bool m_movingLeft = false;
   bool m_movingRight = false;
   bool m_movingDown = false;
   bool m_movingUp = false;
   float m_speed = 100.0f;

public:
   Player(float startX, float startY);
   sf::Sprite getSprite();
   sf::FloatRect getPosition();
   void moveLeft();
   void moveRight();
   void moveUp();
   void moveDown();
   void stopLeft();
   void stopRight();
   void stopUp();
   void stopDown();
   void update(sf::Time dt);
};
