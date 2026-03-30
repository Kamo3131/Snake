#pragma once
#include <iostream>

class Snake {
    private:
        int m_apples_eaten = 0;
        int m_snake_segments = 2;
    public:
        Snake();
        Snake(const int snake_segments);
        /**
         * @brief getter for apples eaten.
         * @returns number of apples eaten.
         */
        int getApplesEaten() const;
        /**
         * @brief getter for snake segments.
         * @returns number of snake segments.
         */
        int getSnakeSegments() const;
        /**
         * @brief setter for apples eaten.
         * @param apples_eaten new value for m_apples_eaten.
         */
        void setApplesEaten(const int apples_eaten);
        /**
         * @brief setter for snake segments.
         * @param snake_segments new value for m_snake_segments.
         */
        void setSnakeSegments(const int snake_segments);
        /**
         * @brief makes snake grow.
         * @param new_segments dictate how many segments will be added to snake.
         */
        void grow(const int new_segments);
        /**
         * @brief increases apples eaten.
         */
        void eatApple();
};