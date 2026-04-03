#include "Map.hpp"
short generateNumber(short max) {
    return rand()%100+1;
}
Map::Map(std::unique_ptr<Snake> snake, std::shared_ptr<ResourceManager> resources) 
: m_snake{std::move(snake)}, m_resources{resources}{}

void Map::draw(sf::RenderTarget & target, sf::RenderStates states) const {

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
        new_pos_x = generateNumber(99);
        new_pos_y = generateNumber(99);
    }
    while(new_pos_x == lastPos.first && new_pos_y == lastPos.second);    
    setLastApplePos(std::make_pair(new_pos_x, new_pos_y));
}