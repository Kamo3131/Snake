#include "Map.hpp"
short generateNumber(short max) {
    return rand()%max+1;
}
Map::Map(std::unique_ptr<Snake> snake, std::shared_ptr<ResourceManager> resources) 
: m_snake{std::move(snake)}, m_resources{resources}{}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {
    unsigned int size_y = target.getSize().y;
    sf::RectangleShape ground_tile(m_tile_size);
    ground_tile.setFillColor(sf::Color(50, 50, 50));
    sf::RectangleShape wall_tile(m_tile_size);
    wall_tile.setFillColor(sf::Color(150, 75, 0));
    for(int y = 0; y < m_size_y; ++y){
        for(int x = 0; x < m_size_x; ++x) {
            if(0 == x || 0 == y || (m_size_x - 1) == x || (m_size_y - 1) == y) {
                wall_tile.setPosition(sf::Vector2f(x * m_tile_size.x + m_offset.x, y * m_tile_size.y + m_offset.y));
                target.draw(wall_tile);
            } else {
                ground_tile.setPosition(sf::Vector2f(x * m_tile_size.x + m_offset.x, y * m_tile_size.y + m_offset.y));
                target.draw(ground_tile);
            }
        }
    }

    sf::RectangleShape apple_tile(m_tile_size);
    apple_tile.setFillColor(sf::Color::Red);
    if(m_last_apple_pos.first != -1) {
        apple_tile.setPosition(
            sf::Vector2f(m_last_apple_pos.first * m_tile_size.x  + m_offset.x, 
                m_last_apple_pos.second * m_tile_size.y  + m_offset.y));
        target.draw(apple_tile);
    }

    sf::RectangleShape snake_tile(m_tile_size);
    snake_tile.setFillColor(sf::Color::Green);
    short segments_number = m_snake->getSegmentsNumber();
    for(int i = 0; i < segments_number; ++i){
        std::pair<std::pair<short, short>, Direction> segmentData 
        = m_snake->getSegment(i);
        auto pos = segmentData.first;
        snake_tile.setPosition(sf::Vector2f(pos.first * m_tile_size.x + m_offset.x, pos.second * m_tile_size.y + m_offset.y));
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
        new_pos_x = generateNumber(m_size_x-2);
        new_pos_y = generateNumber(m_size_y-2);
    }
    while(new_pos_x == lastPos.first && new_pos_y == lastPos.second);    
    setLastApplePos(std::make_pair(new_pos_x, new_pos_y));
    std::cout << getLastApplePos().first << " " << getLastApplePos().second << std::endl;
}

void Map::setDrawParameters(sf::Vector2u draw_area_size) {
    float map_display_size = std::min(static_cast<float>(draw_area_size.x), static_cast<float>(draw_area_size.y));
    float t_tile_size = map_display_size / (m_size_x);
    m_tile_size = sf::Vector2f{t_tile_size, t_tile_size};
    m_offset.x = (draw_area_size.x - map_display_size) / 2.0f;
    m_offset.y = (draw_area_size.y - map_display_size) / 2.0f;
}