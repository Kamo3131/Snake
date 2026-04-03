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
    const short m_size_x = 100;
    const short m_size_y = 100;
    std::pair<short, short> m_last_apple_pos = {-1, -1};
    std::pair<short, short> getLastApplePos() const;
    void setLastApplePos(std::pair<short, short>);
    public:
    Map(std::unique_ptr<Snake> snake, std::shared_ptr<ResourceManager> resources);
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
    short getSizeX() const;
    short getSizeY() const;
    void generateNewApple();
};