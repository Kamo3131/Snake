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
std::pair<short, short> Snake::getHeadPosition() const {
    return m_snake_segments.at(0).m_position;
}
float Snake::getSpeed() const {
    return m_snake_speed;
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

void Snake::moveRight() {
    Direction head_direction = m_snake_segments[0].m_direction;
    short head_position_x = m_snake_segments[0].m_position.first;
    short head_position_y = m_snake_segments[0].m_position.second;
    switch (head_direction)
    {
    case Direction::UP:
        movement(std::make_pair(head_position_x+1, head_position_y), Direction::RIGHT);
        break;
    case Direction::RIGHT:
        movement(std::make_pair(head_position_x, head_position_y+1), Direction::DOWN);
        break;
    case Direction::DOWN:
        movement(std::make_pair(head_position_x-1, head_position_y), Direction::LEFT);
        break;
    case Direction::LEFT:
        movement(std::make_pair(head_position_x, head_position_y-1), Direction::UP);
        break;
    }
}
void Snake::moveLeft() {
    Direction head_direction = m_snake_segments[0].m_direction;
    short head_position_x = m_snake_segments[0].m_position.first;
    short head_position_y = m_snake_segments[0].m_position.second;
    switch (head_direction)
    {
    case Direction::UP:
        movement(std::make_pair(head_position_x-1, head_position_y), Direction::LEFT);
        break;
    case Direction::RIGHT:
        movement(std::make_pair(head_position_x, head_position_y-1), Direction::UP);
        break;
    case Direction::DOWN:
        movement(std::make_pair(head_position_x+1, head_position_y), Direction::RIGHT);
        break;
    case Direction::LEFT:
        movement(std::make_pair(head_position_x, head_position_y+1), Direction::DOWN);
        break;
    }
}

void Snake::moveStraight() {
    Direction head_direction = m_snake_segments[0].m_direction;
    short head_position_x = m_snake_segments[0].m_position.first;
    short head_position_y = m_snake_segments[0].m_position.second;
    switch (head_direction)
    {
    case Direction::UP:
        movement(std::make_pair(head_position_x, head_position_y-1), Direction::UP);
        break;
    case Direction::RIGHT:
        movement(std::make_pair(head_position_x+1, head_position_y), Direction::RIGHT);
        break;
    case Direction::DOWN:
        movement(std::make_pair(head_position_x, head_position_y+1), Direction::DOWN);
        break;
    case Direction::LEFT:
        movement(std::make_pair(head_position_x-1, head_position_y), Direction::LEFT);
        break;
    }
}