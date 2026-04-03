#pragma once
#include <iostream>
#include <vector>
#include <deque>

enum Direction {
    UP, LEFT, RIGHT, DOWN
};

struct SnakeSegment {
    SnakeSegment(short x, short y, Direction direction);
    std::pair<short, short> m_position;
    Direction m_direction = UP;
};

class Snake {
    private:
        int m_apples_eaten = 0;
        int m_segments_number = 2;
        std::deque<SnakeSegment> m_snake_segments;
    public:
        Snake();
        Snake(const int segments_number);
        /**
         * @brief getter for apples eaten.
         * @returns number of apples eaten.
         */
        int getApplesEaten() const;
        /**
         * @brief getter for snake segments.
         * @returns number of snake segments.
         */
        int getSegmentsNumber() const;
        /**
         * @brief setter for apples eaten.
         * @param apples_eaten new value for m_apples_eaten.
         */
        void setApplesEaten(const int apples_eaten);
        /**
         * @brief setter for snake segments.
         * @param snake_segments new value for m_snake_segments.
         */
        void setSegmentsNumber(const int segmentsNumber);
        /**
         * @brief makes snake grow.
         * @param new_segments dictate how many segments will be added to snake.
         */
        void grow(const int new_segments);
        /**
         * @brief increases apples eaten.
         */
        void eatApple();
        std::pair<std::pair<short, short>, Direction> getSegment(int index) const;
        void movement(std::pair<short, short> head_position, Direction head_direction);
};