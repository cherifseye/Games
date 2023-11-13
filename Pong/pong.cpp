#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "bat.hpp"
#include "ball.hpp"
using namespace sf;

const float width  = 1000.0f;
const float height = 800.0f;

int score = 0;
int main(){
    
    Bat bat(width/2, height-5);
    Ball ball(width/2, 0);
    VideoMode vm(width, height);

    RenderWindow window(vm, "Pong", Style::Default);
    Clock clock;
    Font font;
    font.loadFromFile("fonts/DS-DIGI.TTF");
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(75);
    scoreText.setPosition(Vector2f(0, 0));
    scoreText.setFillColor(Color::White);
    SoundBuffer hitbuffer;
    hitbuffer.loadFromFile("sounds/Hit.wav");
    Sound hit;
    hit.setBuffer(hitbuffer);
    

    while (window.isOpen())
    {
        Time dt = clock.restart();
        Event event; 
        if (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
        }

    if (Keyboard::isKeyPressed(Keyboard::Left) && bat.getPosition().left > 0){
        bat.moveLeft();
    }else{
        bat.stopLeft();
    }
    if (Keyboard::isKeyPressed(Keyboard::Right )&& bat.getPosition().left+bat.getPosition().width<window.getSize().x){
        bat.moveRight();
    }else{
        bat.stopRight();
    }
    bat.update(dt);
    
    if (ball.getPosition().top > window.getSize().y){
        ball.reboundsBottom(window.getSize().x);
        score = 0;

    }
    if (ball.getPosition().left <= 0 || (ball.getPosition().left + ball.getPosition().width) > window.getSize().x){
        ball.reboundsSides();
        hit.play();
    }
    if (ball.getPosition().intersects(bat.getPosition())){
        ball.reboundsBatorTop();
        hit.play();
        score += 1;
    }
    if (ball.getPosition().top < 0){
        ball.reboundsBatorTop();
        hit.play();
    }
    window.clear();
    ball.update(dt);
    scoreText.setString("Score = " + std::to_string(score));
    window.draw(scoreText);
    window.draw(bat.getShape());
    window.draw(ball.getShape());
    window.display();
    }    
}