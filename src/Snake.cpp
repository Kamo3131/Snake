#include "Snake.hpp"
SnakeSegment::SnakeSegment(short x, short y, Direction direction) : m_position{x, y}, m_direction{direction}{}
Snake::Snake(short x, short y) : m_apples_eaten{0}, m_segments_number{2} {
    m_snake_segments.emplace_back(x, y, Direction::UP);
    m_snake_segments.push_back(m_snake_segments.back());
}
Snake::Snake(short x, short y, const int segments_number) : m_apples_eaten{0}, m_segments_number{segments_number} {
    m_snake_segments.emplace_back(x, y, Direction::UP);
    grow(segments_number-1);
}
int Snake::getApplesEaten() const {
    return m_apples_eaten;
}
int Snake::getSegmentsNumber() const {
    return m_segments_number;
}
void Snake::setApplesEaten(const int apples_eaten) {
    m_apples_eaten = apples_eaten;
}
void Snake::setSegmentsNumber(const int segments_number) {
    m_segments_number = segments_number;
}
void Snake::grow(const int new_segments) {
    for(int i = 0; i < new_segments; ++i) {
        m_snake_segments.push_back(m_snake_segments.back());
    }
    m_segments_number = m_snake_segments.size();
}
void Snake::eatApple(){
    ++m_apples_eaten;
    grow(1);
}

std::pair<std::pair<short, short>, Direction> Snake::getSegment(int index) const {
    SnakeSegment segment = m_snake_segments.at(index);
    return std::make_pair(segment.m_position, segment.m_direction);
}

void Snake::movement(std::pair<short, short> head_position, Direction head_direction) {
    m_snake_segments.emplace_front(head_position.first, head_position.second, head_direction);
    if(m_snake_segments.size() > m_segments_number) {
        m_snake_segments.pop_back();
    }
}