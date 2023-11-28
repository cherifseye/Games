#include <SFML/Graphics.hpp>
using namespace sf;
class Zoombie{
private:
    // Zoombie Velocity
    const float BLOATER_SPEED = 40;
    const float CHASER_SPEED  = 80;
    const float CRAWLER_SPEED = 20;

    // Zoombie Damages
    const float BLOATER_HEALTH = 5;
    const float CHASER_HEALTH  = 1;
    const float CRAWLER_HEALTH = 3;

    const int MAX_VARIANCE = 30;
    const int OFFSET = 101 - MAX_VARIANCE;  

    Vector2f m_position;
    Sprite m_sprite;
    float m_speed;
    float m_health;
    bool  m_alive;

public:
    bool hit();
    bool isAlive();
    void spawn(float startX, float startY, int type, int seed);
    FloatRect getPosition();
    Sprite getSprite();
    void update(float elapsedTime, Vector2f playerLocation);

};
