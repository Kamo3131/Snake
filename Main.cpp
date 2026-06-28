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
    if (!ImGui::SFML::Init(window)) {
        return -1;
    }
    std::shared_ptr<ResourceManager> resourceManager 
    = std::make_shared<ResourceManager>();
    // resourceManager.getTexture("../../assets/Floor.png");
    // resourceManager.getTexture("../../assets/Wall.png");
    // resourceManager.getTexture("../../assets/Apple.png");
    // resourceManager.getTexture("../../assets/Snake.png");
    sf::Clock deltaClock;
    Map map(std::make_unique<Snake>(5, 5), resourceManager);
    // bool game_active = false;
    map.generateNewApple();
    map.setDrawParameters(window.getSize());
    while (window.isOpen()) {
        
        while (const std::optional event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

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

        ImGui::SFML::Update(window, deltaClock.restart());
        map.moveSnakeStraight();
        window.clear(sf::Color::Black);
        window.draw(map);
        ImGui::SFML::Render(window);

        window.display();
    }
    deltaClock.restart();
    ImGui::SFML::Shutdown();

    return 0;
}