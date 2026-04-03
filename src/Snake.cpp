#include "Snake.hpp"
SnakeSegment::SnakeSegment(short x, short y) : position{x, y}{}

Snake::Snake() : m_apples_eaten{0}, m_snake_segments{2} {}
Snake::Snake(const int snake_segments) : m_apples_eaten{0}, m_snake_segments{snake_segments} {

}
int Snake::getApplesEaten() const {
    return m_apples_eaten;
}
int Snake::getSnakeSegments() const {
    return m_snake_segments;
}
void Snake::setApplesEaten(const int apples_eaten) {
    m_apples_eaten = apples_eaten;
}
void Snake::setSnakeSegments(const int snake_segments) {
    m_snake_segments = snake_segments;
}
void Snake::grow(const int new_segments) {
    m_snake_segments += new_segments;
}
void Snake::eatApple(){
    ++m_apples_eaten;
}