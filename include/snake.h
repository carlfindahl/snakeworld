#ifndef H_MENU_H
#define H_MENU_H

#include <stdint.h>
#include <stdio.h>

#define SNAKE_MAX_LENGTH 128

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct Snake
{
    char name[16];
    int length;
    int life;
    int invulnerable;
    uint32_t positions[SNAKE_MAX_LENGTH];
    enum Direction direction;
} Snake;

// Initialize a snake at the given position
Snake init_snake(uint32_t x, uint32_t y);

// Update the snake's position
void snake_update(Snake *s);

// Increase length of snake
void snake_increment(Snake *s);

// Decrease length of snake
void snake_decrement(Snake *s);

// Return the X coordinate of the snake at the given position
uint32_t snake_x(Snake *s, uint32_t position);

// Return the Y coordinate of the snake at the given position
uint32_t snake_y(Snake *s, uint32_t position);

#endif
