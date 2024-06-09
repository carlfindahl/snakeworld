#pragma once

#include <stdint.h>

#include <raylib.h>

// Size of each tile
extern const int TILE_SIZE;

// Size of the render texture that is blitted to the full screen
extern const int RENDER_SIZE;

// Highest coordinate on the map in either direction (RENDER_SIZE / TILE_SIZE)
extern const int MAP_SIZE;

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    DIR_COUNT,
};

uint32_t vec2(uint32_t x, uint32_t y);

uint32_t vec2_x(uint32_t v);

uint32_t vec2_y(uint32_t v);

Rectangle vec2_to_tile_rect(uint32_t v);
