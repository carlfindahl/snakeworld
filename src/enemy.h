#pragma once

#include "game_math.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct Enemy
{
    uint32_t pos;
    enum Direction direction;
    bool active;
} Enemy;

/// Will alter the enemy in e and initialize it at the given position with random parameters
void enemy_spawn(Enemy* e, uint32_t pos);

void enemy_despawn(Enemy* e);

void enemy_update(Enemy* e);

void enemy_draw(Enemy* e);
