#include "enemy.h"

#include <raylib.h>

void enemy_spawn(Enemy** e, uint32_t pos)
{
    Enemy* enemy     = *e;
    enemy->pos       = pos;
    enemy->direction = GetRandomValue(0, DIR_COUNT);
    enemy->active    = true;
}

void enemy_despawn(Enemy** e)
{
    Enemy* enemy  = *e;
    enemy->active = false;
}

void enemy_update(Enemy* e)
{
    if (e->active)
    {
        switch (e->direction)
        {
            case UP: e->pos -= vec2(0, 1); break;
            case DOWN: e->pos += vec2(0, 1); break;
            case LEFT: e->pos -= vec2(1, 0); break;
            case RIGHT: e->pos += vec2(1, 0); break;
            default: break;
        }
    }
}
