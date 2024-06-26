#include "snake.h"
#include "game_math.h"
#include "message_queue.h"
#include "resources.h"

#include <raylib.h>
Snake init_snake(uint32_t x, uint32_t y, uint32_t base_length)
{
    Snake s;
    s.length             = base_length;
    s.invulnerable       = 0;
    s.life               = 3;
    s.positions[0]       = x | (y << 16);
    s.positions[1]       = x | (y << 16);
    s.direction          = RIGHT;
    s.previous_direction = RIGHT;
    return s;
}

void snake_update(Snake* s)
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
    s->positions[0] = s->positions[0] + (s->direction == RIGHT) - (s->direction == LEFT) + ((s->direction == DOWN) << 16) -
                      ((s->direction == UP) << 16);

    // Check for collision
    if (s->invulnerable <= 0)
    {
        bool damaged = false;
        for (int i = 1; i < s->length; i++)
        {
            if (s->positions[0] == s->positions[i])
            {
                damaged   = true;
                s->length = i;
                break;
            }
        }

        // Check for out of bounds
        if (snake_x(s, 0) < 0 || snake_x(s, 0) >= 30 || snake_y(s, 0) < 0 || snake_y(s, 0) >= 30)
        {
            damaged         = true;
            s->positions[0] = 13 | (15 << 16);
            s->direction    = RIGHT;
        }

        if (damaged)
        {
            snake_damage(s);
        }
    }
}

void snake_damage(Snake* s)
{
    --s->life;
    s->invulnerable = 4;

    // Send damage event
    struct GameEvent event              = {.identifier = GME_SNAKE_DAMAGED};
    event.data.snake_damaged.damage     = 1;
    event.data.snake_damaged.new_health = s->life;
    mq_push(event);
}

void snake_increment(Snake* s)
{
    s->positions[s->length] = s->positions[s->length - 1];
    ++s->length;
}

void snake_decrement(Snake* s)
{
    --s->length;
}

uint32_t snake_x(Snake* s, uint32_t position)
{
    if (position >= SNAKE_MAX_LENGTH)
    {
        return 0;
    }

    return vec2_x(s->positions[position]);
}

uint32_t snake_y(Snake* s, uint32_t position)
{
    if (position >= SNAKE_MAX_LENGTH)
    {
        return 0;
    }

    return vec2_y(s->positions[position]);
}