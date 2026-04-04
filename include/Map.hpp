#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "ResourceManager.hpp"
#include <cstdlib>

class Map : public sf::Drawable{
    private:
    std::unique_ptr<Snake> m_snake;
    std::shared_ptr<ResourceManager> m_resources;
    const short m_size_x = 20;
    const short m_size_y = 20;
    sf::Vector2f m_tile_size;
    std::pair<short, short> m_last_apple_pos = {-1, -1};
    std::pair<short, short> getLastApplePos() const;
    void setLastApplePos(std::pair<short, short>);
    public:
    Map(std::unique_ptr<Snake> snake, std::shared_ptr<ResourceManager> resources);
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    void setDrawParameters(sf::Vector2u draw_area_size);
    short getSizeX() const;
    short getSizeY() const;
    void generateNewApple();
};