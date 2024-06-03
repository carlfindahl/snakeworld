#include <raylib.h>

#include "menu.h"

struct snake init_snake(uint32_t x, uint32_t y)
{
    struct snake s;
    s.length = 2;
    s.invulnerable = 0;
    s.life = 3;
    s.positions[0] = x | (y << 16);
    s.positions[1] = x | (y << 16);
    s.direction = RIGHT;
    return s;
}

void snake_update(struct snake *s)
{
    if (s->invulnerable > 0)
    {
        --s->invulnerable;
    }

    // Move the snake
    for (int i = s->length - 1; i > 0; i--)
    {
        s->positions[i] = s->positions[i - 1];
    }

    // Move the head
    s->positions[0] = s->positions[0] + (s->direction == RIGHT) - (s->direction == LEFT) + ((s->direction == DOWN) << 16) - ((s->direction == UP) << 16);

    // Check for collision
    if (s->invulnerable <= 0)
    {
        bool damaged = false;
        for (int i = 1; i < s->length; i++)
        {
            if (s->positions[0] == s->positions[i])
            {
                damaged = true;
                s->length = i;
                break;
            }
        }

        // Check for out of bounds
        if (snake_x(s, 0) < 0 || snake_x(s, 0) >= 30 || snake_y(s, 0) < 0 || snake_y(s, 0) >= 30)
        {
            damaged = true;
            s->positions[0] = 5 | (5 << 16);
        }

        if (damaged)
        {
            --s->life;
            s->invulnerable = 4;
        }
    }
}

void snake_increment(struct snake *s)
{
    s->positions[s->length] = s->positions[s->length - 1];
    ++s->length;
}

void snake_decrement(struct snake *s)
{
    --s->length;
}

uint32_t snake_x(struct snake *s, uint32_t position)
{
    if (position >= SNAKE_MAX_LENGTH)
    {
        return 0;
    }

    return s->positions[position] & 0xFFFF;
}

uint32_t snake_y(struct snake *s, uint32_t position)
{
    if (position >= SNAKE_MAX_LENGTH)
    {
        return 0;
    }

    return s->positions[position] >> 16;
}