#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Snake.hpp"
#include "ResourceManager.hpp"
#include <cstdlib>

class Map {
    private:
    std::unique_ptr<Snake> m_snake;
    std::shared_ptr<ResourceManager> m_resources;
    // bool moving = false;
    const short m_size_x = 22;
    const short m_size_y = 22;
    sf::Vector2f m_tile_size;
    sf::Vector2f m_offset;
    std::pair<short, short> m_last_apple_pos = {-1, -1};
    std::pair<short, short> getLastApplePos() const;
    void setLastApplePos(std::pair<short, short>);

    public:
    Map(std::unique_ptr<Snake> snake, std::shared_ptr<ResourceManager> resources);
    void update(const float delta, sf::RenderTarget & target) const;
    void setDrawParameters(sf::Vector2u draw_area_size);
    short getSizeX() const;
    short getSizeY() const;
    void generateNewApple();
    void moveSnakeRight();
    void moveSnakeLeft();
    void moveSnakeStraight();
    void makeSnakeEat();
    // void changeMoving();
    // bool moving();
    bool nextMoveOutMap() const;
};