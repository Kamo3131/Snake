#include <memory>
#include <imgui.h>
#include <imgui-SFML.h>
#include "ResourceManager.hpp"
#include "Map.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Snake", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    window.setFramerateLimit(60);
    std::shared_ptr<ResourceManager> resourceManager 
    = std::make_shared<ResourceManager>();
    sf::Clock deltaClock;
    Map map(std::make_unique<Snake>(5, 5), resourceManager);
    map.generateNewApple();
    map.setDrawParameters(window.getSize());
    map.makeSnakeEat();
    map.makeSnakeEat();
    map.makeSnakeEat();
    map.makeSnakeEat();
    while (window.isOpen()) {
        sf::Time deltaTimeTimer = deltaClock.restart();
        const float deltaTime = deltaTimeTimer.asMilliseconds();
        const float framerate = 1000.0f / deltaTime;
        std::cout << framerate << std::endl;
        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                map.moveSnakeLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                map.moveSnakeRight();
            }
            if (const auto resized = event->getIf<sf::Event::Resized>())
            {
                window.setView(sf::View(sf::FloatRect({ 0, 0 }, static_cast<sf::Vector2f>(resized->size))));
                map.setDrawParameters(window.getSize());
            }
        }

        map.moveSnakeStraight();

        window.clear(sf::Color::Black);
        map.update(deltaTime, window);

        window.display();
    }

    return 0;
}