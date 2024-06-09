#include "enemy.h"

#include <raylib.h>

void enemy_spawn(Enemy* e, uint32_t pos)
{
    e->pos       = pos;
    e->direction = GetRandomValue(0, DIR_COUNT);
    e->active    = true;
}

void enemy_despawn(Enemy* e)
{
    e->active = false;
}

void enemy_update(Enemy* e)
{
    if (e->active)
    {
        switch (e->direction)
        {
            case UP: e->pos = vec2(vec2_x(e->pos), vec2_y(e->pos) - 1); break;
            case DOWN: e->pos = vec2(vec2_x(e->pos), vec2_y(e->pos) + 1); break;
            case LEFT: e->pos = vec2(vec2_x(e->pos) - 1, vec2_y(e->pos)); break;
            case RIGHT: e->pos = vec2(vec2_x(e->pos) + 1, vec2_y(e->pos)); break;
            default: break;
        }

        if (vec2_x(e->pos) == 0)
        {
            e->pos = vec2(MAP_SIZE, vec2_y(e->pos));
        }
        else if (vec2_x(e->pos) > MAP_SIZE)
        {
            e->pos = vec2(0, vec2_y(e->pos));
        }
        else if (vec2_y(e->pos) == 0)
        {
            e->pos = vec2(vec2_x(e->pos), MAP_SIZE);
        }
        else if (vec2_y(e->pos) > MAP_SIZE)
        {
            e->pos = vec2(vec2_x(e->pos), 0);
        }
    }
}
