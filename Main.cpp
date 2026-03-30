#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    // 1. Create the SFML window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "ImGui + SFML Test");
    window.setFramerateLimit(60);

    // 2. Initialize ImGui-SFML
    if (!ImGui::SFML::Init(window)) {
        return -1;
    }

    sf::Clock deltaClock;
    while (window.isOpen()) {
        // 3. Handle Events
        while (const std::optional event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // 4. Update ImGui
        ImGui::SFML::Update(window, deltaClock.restart());

        // 5. Build your UI
        ImGui::Begin("Hello, Game Dev!");
        ImGui::Text("If you see this, ImGui is working!");
        static float color[3] = { 0.1f, 0.1f, 0.1f };
        ImGui::ColorEdit3("Background Color", color);
        
        if (ImGui::Button("Reset Color")) {
            color[0] = 0.1f; color[1] = 0.1f; color[2] = 0.1f;
        }
        ImGui::End();

        // 6. Render
        window.clear(sf::Color(
            static_cast<std::uint8_t>(color[0] * 255),
            static_cast<std::uint8_t>(color[1] * 255),
            static_cast<std::uint8_t>(color[2] * 255)
        ));
        
        ImGui::SFML::Render(window);
        window.display();
    }

    // 7. Shutdown
    ImGui::SFML::Shutdown();

    return 0;
}