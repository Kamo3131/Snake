#include <memory>
#include <imgui.h>
#include <imgui-SFML.h>
#include "ResourceManager.hpp"
#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <sstream>
#include <iomanip>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Snake", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(300);
    std::shared_ptr<ResourceManager> resourceManager 
    = std::make_shared<ResourceManager>();
    
    
    // ===================== Text init =========================
    sf::Text text(resourceManager->getFont("assets/SaH1Outline.ttf"));
    text.setFillColor(sf::Color::Cyan);
    text.setStyle(sf::Text::Bold);
    text.setCharacterSize(20);

    // ===================== Map init ==========================
    Map map(std::make_unique<Snake>(5, 5), resourceManager);
    map.generateNewApple();
    map.setDrawParameters(window.getSize());
    map.makeSnakeEat();
    map.makeSnakeEat();
    map.makeSnakeEat();
    map.makeSnakeEat();
    Direction currentDirection = UP;
    // ==================== Clock init ========================
    sf::Clock deltaClock;
    float timer = 0.f;
    // 1/10 of a second for tile jump (value in miliseconds)
    while (window.isOpen()) {
        
        sf::Time deltaTimeTimer = deltaClock.restart();
        const float deltaTime = deltaTimeTimer.asSeconds();
        timer += deltaTime;
        const float framerate = 1.0f / deltaTime;
        // std::cout << framerate << std::endl;
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                currentDirection = LEFT;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                currentDirection = RIGHT;
            }
            if (const auto resized = event->getIf<sf::Event::Resized>())
            {
                window.setView(sf::View(sf::FloatRect({ 0, 0 }, static_cast<sf::Vector2f>(resized->size))));
                map.setDrawParameters(window.getSize());
            }
        }
        const float speed = map.getSnakeSpeed();
        if(timer >= speed) {    
            timer -= speed;

            if(map.nextMoveOutMap()) {
                map.moveSnakeRight();
            } else {
                switch(currentDirection) {
                    case UP:
                        map.moveSnakeStraight();
                        break;
                    case LEFT:
                        map.moveSnakeLeft();
                        break;
                    case RIGHT:
                        map.moveSnakeRight();
                        break;
                    case DOWN:
                        break;
                }
                currentDirection = UP;
            }
        }
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(0) << framerate;

        text.setString(ss.str());

        window.clear(sf::Color::Black);
        map.update(timer, window);
        window.draw(text);
        window.display();
    }

    return 0;
}