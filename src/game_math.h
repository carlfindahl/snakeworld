#pragma once

#include <stdint.h>

// Size of each tile
extern const int TILE_SIZE;

// Size of the render texture that is blitted to the full screen
extern const int RENDER_SIZE;

uint32_t vec2(uint32_t x, uint32_t y);

uint32_t vec2_x(uint32_t v);

uint32_t vec2_y(uint32_t v);
