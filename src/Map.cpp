#include "Map.hpp"
short generateNumber(short max) {
    return rand()%100+1;
}
Map::Map(std::unique_ptr<Snake> snake, std::shared_ptr<ResourceManager> resources) 
: m_snake{std::move(snake)}, m_resources{resources}{}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    sf::RectangleShape ground_tile(m_tile_size);
    ground_tile.setFillColor(sf::Color(50, 50, 50));
    for(int y = 0; y < m_size_y; ++y){
        for(int x = 0; x < m_size_x; ++x) {
            ground_tile.setPosition(sf::Vector2f(x*m_tile_size.x, y*m_tile_size.y));
            target.draw(ground_tile);
        }
    }


    sf::RectangleShape apple_tile(m_tile_size);
    apple_tile.setFillColor(sf::Color::Red);
    if(m_last_apple_pos.first != -1) {
        apple_tile.setPosition(
            sf::Vector2f(m_last_apple_pos.first*m_tile_size.x, 
                m_last_apple_pos.second*m_tile_size.y));
        target.draw(apple_tile);
    }

    sf::RectangleShape snake_tile(m_tile_size);
    snake_tile.setFillColor(sf::Color::Green);
    short segments_number = m_snake->getSegmentsNumber();
    for(int i = 0; i < segments_number; ++i){
        std::pair<std::pair<short, short>, Direction> segmentData 
        = m_snake->getSegment(i);
        auto pos = segmentData.first;
        snake_tile.setPosition(sf::Vector2f(pos.first * m_tile_size.x, pos.second * m_tile_size.y));
        if (0 == i) {
            snake_tile.setFillColor(sf::Color(0, 200, 0));
        } else {
            snake_tile.setFillColor(sf::Color::Green);
        }
        target.draw(snake_tile);
    }
}
short Map::getSizeX() const {
    return m_size_x;
}
short Map::getSizeY() const {
    return m_size_y;
}
std::pair<short, short> Map::getLastApplePos() const {
    return m_last_apple_pos;
}
void Map::setLastApplePos(std::pair<short, short> new_apple_pos) {
    m_last_apple_pos = new_apple_pos;
}
void Map::generateNewApple() {
    std::pair<short, short> lastPos = getLastApplePos();
    short new_pos_x = 0, new_pos_y = 0;
    do {
        new_pos_x = generateNumber(20);
        new_pos_y = generateNumber(20);
    }
    while(new_pos_x == lastPos.first && new_pos_y == lastPos.second);    
    setLastApplePos(std::make_pair(new_pos_x, new_pos_y));
}

void Map::setDrawParameters(sf::Vector2u draw_area_size) {
    m_tile_size.x = static_cast<float>(draw_area_size.x) / m_size_x;
    m_tile_size.y = static_cast<float>(draw_area_size.y) / m_size_y; 
}