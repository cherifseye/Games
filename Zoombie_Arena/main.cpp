#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "zoombieArena.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
    enum class State {PAUSED, LEVELING_UP, GAME_OVER, PLAYING};
    State state = State::GAME_OVER;
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zoombie Arena", Style::Fullscreen);

    View mainView(FloatRect(0, 0, resolution.x, resolution.y));
    Clock clock;
    Time gameTimeTotal;
    Vector2f mouseWorldPosition;
    Vector2i mouseScreenPosition;
    Player player1;
    IntRect arena;
    VertexArray background;
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background_sheet.png");
    while (window.isOpen()){
        Event event;
        if(window.pollEvent(event)){
            if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::Return && state == State::PLAYING){
                    state = State::PAUSED;
                }else if(event.key.code == Keyboard::Return && state == State::PAUSED){
                    state = State::PLAYING;
                    clock.restart();
                }
                else if(event.key.code == Keyboard::Return && state == State::GAME_OVER){
                    state = State::LEVELING_UP;
                }
                if (state==State::PLAYING){};
            }
        } // Event polling
        if (Keyboard::isKeyPressed(Keyboard::Escape)){
            window.close();
        }
        if (state == State::PLAYING){
            if(Keyboard::isKeyPressed(Keyboard::A)){
                player1.moveLeft();
            }else{
                player1.stopLeft();
            }
            if (Keyboard::isKeyPressed(Keyboard::D)){
                player1.moveRight();
            }else{
                player1.stopRight();
            }
            if (Keyboard::isKeyPressed(Keyboard::W)){
                player1.moveUp();
            }else{
                player1.stopUp();
            }
            if (Keyboard::isKeyPressed(Keyboard::S)){
                player1.moveDown();
            }
            else{
                player1.stopDown();
            }
        }
        if(state == State::LEVELING_UP){
            if (event.key.code == Keyboard::Num1){
                state = State::PLAYING;
            }
            if (state == State::PLAYING){
                arena.width = resolution.x;
                arena.height = resolution.y;
                arena.left = 0;
                arena.top = 0;
                int tileSize = createBackground(background, arena);
                //int tileSize = 50;
                player1.spawn(arena, resolution, tileSize);
                clock.restart();
            }
        }

        if (state == State::PLAYING)
        {
            Time dt = clock.restart();

            gameTimeTotal += dt;
            float dtAsSeconds = dt.asSeconds();
            mouseScreenPosition = Mouse::getPosition();
            mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);

            Vector2f playerPosition(player1.getCenter());
            player1.update(dtAsSeconds, Mouse::getPosition());
            mainView.setCenter(player1.getCenter());
            
        }

        if (state == State::PLAYING)
        {
            window.clear();
            window.setView(mainView);
            window.draw(background, &textureBackground);
            window.draw(player1.getSprite());
        }
        if (state == State::LEVELING_UP)
        {
        }
        if (state == State::PAUSED)
        {
        }
        window.display();
    }
  
}