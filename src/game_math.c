#include "game_math.h"

uint32_t vec2(uint32_t x, uint32_t y)
{
    return x | (y << 16);
}

uint32_t vec2_x(uint32_t v)
{
    return v & 0xFFFF;
}

uint32_t vec2_y(uint32_t v)
{
    return v >> 16;
}