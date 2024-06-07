#pragma once

#include "scenes/end_game.h"
#include "snake.h"

#include <stdint.h>
#include <string.h>

enum GameEventIdentifier
{
    GME_NOTHING,
    GME_PUSH_SCENE,
    GME_POP_SCENE,
    GME_QUIT_GAME,
    GME_ACTION_SNAKE_DIRECTION_CHANGE,
    GME_SNAKE_DAMAGED,
    GME_FOOD_EATEN,
    GME_EVENT_COUNT,
};

struct GameEvent
{
    enum GameEventIdentifier identifier;
    union
    {
        struct
        {
            struct Scene* (*scene_fn)();
        } push_scene;

        struct
        {
            enum Direction old_dir;
            enum Direction new_dir;
        } snake_direction_change;

        struct
        {
            int damage;
            int new_health;
        } snake_damaged;

        struct
        {
            int score_delta;
            int new_score;
        } food_eaten;
    } data;
};

typedef void (*ObserverFn)(void*, struct GameEvent*);

typedef struct Observer
{
    void* context;
    ObserverFn fn;
} Observer;

typedef struct MessageQueue
{
    uint64_t size;
    uint64_t capacity;
    struct GameEvent* messages;

    uint64_t observer_size;
    uint64_t observer_capacity;
    Observer* observers;
} MessageQueue;

void mq_init();
void mq_push(struct GameEvent msg);
void mq_listen(Observer obs);
void mq_unlisten(ObserverFn obs);
void mq_process();
void mq_free();