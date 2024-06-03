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

struct snake
{
    char name[16];
    int length;
    int life;
    int invulnerable;
    uint32_t positions[SNAKE_MAX_LENGTH];
    enum Direction direction;
};

// Initialize a snake at the given position
struct snake init_snake(uint32_t x, uint32_t y);

// Update the snake's position
void snake_update(struct snake *s);

// Increase length of snake
void snake_increment(struct snake *s);

// Decrease length of snake
void snake_decrement(struct snake *s);

// Return the X coordinate of the snake at the given position
uint32_t snake_x(struct snake *s, uint32_t position);

// Return the Y coordinate of the snake at the given position
uint32_t snake_y(struct snake *s, uint32_t position);

#endif
