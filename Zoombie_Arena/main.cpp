#include <SFML/Graphics.hpp>
using namespace sf;

int main(){
    VideoMode Desktop = VideoMode::getDesktopMode();
    RenderWindow window(Desktop, "Rectangle Drag");
    RectangleShape rectangle;
    rectangle.setPosition(0.0f, 0.0f);
    rectangle.setSize(Vector2f(40, 40));
    rectangle.setFillColor(Color::White);
    bool dragging = false;
    Vector2f offset;

    while (window.isOpen())
    {
        Event event;
        while(window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
            if (event.type == Event::MouseButtonPressed){
                if (event.mouseButton.button == Mouse::Left && rectangle.getGlobalBounds().contains(window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)))){
                    dragging = true;
                    offset.x = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)).x - rectangle.getPosition().x;
                    offset.y = window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)).y - rectangle.getPosition().y;
                }
            }
            if(event.type == Event::MouseButtonReleased){
                dragging = false;
            }
            if(event.type == Event::Resized){
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            
            }
        }
        if (dragging){
            Vector2i mouse = Mouse::getPosition(window);
            rectangle.setPosition(std::max(0.0f, std::min(window.mapPixelToCoords(mouse).x - offset.x, window.getSize().x-rectangle.getGlobalBounds().width)),
                                std::max(0.0f, std::min(window.mapPixelToCoords(mouse).y - offset.y, window.getSize().y - rectangle.getGlobalBounds().height)));
        }
        window.clear();
        window.draw(rectangle);
        window.display();
    }
}
