#include <SFML/Graphics.hpp>
#include "player.hpp"
using namespace sf;

int main(){
    VideoMode Desktop = VideoMode::getDesktopMode();
    RenderWindow window(Desktop, "Zoombie Arena");
    
    Player player1(window.getSize().x/2, window.getSize().y/2);
    Clock clock;
    while (window.isOpen()){
        Time dt = clock.restart();
        Event event;
        if(window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
            if (event.type == Event::Resized){
                FloatRect viewArea(0, 0, event.size.width, event.size.height);
                window.setView(View(viewArea));
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::A) && player1.getPosition().left > 0){
            player1.moveLeft();
        }else{
            player1.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::D) && player1.getPosition().left + player1.getPosition().width < window.getSize().x){
            player1.moveRight();
        }else{
            player1.stopRight();
        }
        if (Keyboard::isKeyPressed(Keyboard::W) && player1.getPosition().top > 0){
            player1.moveUp();
        }else{
            player1.stopUp();
        }
        if (Keyboard::isKeyPressed(Keyboard::S) && player1.getPosition().top + player1.getPosition().height < window.getSize().y){
            player1.moveDown();
        }
        else{
            player1.stopDown();
        }
        window.clear();
        window.draw(player1.getSprite());
        window.display();
    }
}
