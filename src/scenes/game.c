#include "scenes/game.h"
#include "game_math.h"
#include "kv_store.h"
#include "message_queue.h"
#include "resources.h"
#include "scenes/end_game.h"
#include "scenes/scene.h"
#include "snake.h"

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#include <raylib.h>

#define INITIAL_SNAKE_LENGTH 3
#define INITIAL_TICK_TIME 1.0f
#define BASE_GAME_SPEED 0.2f
#define MAX_LIFE 4

typedef struct GameData
{
    Snake snake;
    float tick_timer;
    float delay_time;
    float boost;
    int score;
    int tick_count;
    int boost_threshold;
    uint32_t apple;
    Texture2D* sprite_sheet;
    Font* font;
} GameData;

static GameData* game_data = NULL;

static void on_snake_damaged(void* _, struct GameEvent* event)
{
    if (event->identifier == GME_SNAKE_DAMAGED)
    {
        game_data->boost = 1.0;
    }
}

static void game_init()
{
    game_data                  = malloc(sizeof(GameData));
    game_data->apple           = vec2(10, 10);
    game_data->snake           = init_snake(13, 15, INITIAL_SNAKE_LENGTH);
    game_data->score           = 0;
    game_data->tick_count      = 0;
    game_data->boost           = 1.0f;
    game_data->boost_threshold = 5;
    game_data->tick_timer      = INITIAL_TICK_TIME;
    game_data->delay_time      = BASE_GAME_SPEED;
    game_data->sprite_sheet    = resources_get_sprite(TEXID_SPRITES);
    game_data->font            = resources_get_font();

    mq_listen((Observer){.context = NULL, .fn = on_snake_damaged});
}

void game_update()
{
    Snake* s = &game_data->snake;

    // Direction change
    if (IsKeyPressed(KEY_UP) && s->previous_direction != DOWN)
    {
        s->direction = UP;
    }
    else if (IsKeyPressed(KEY_DOWN) && s->previous_direction != UP)
    {
        s->direction = DOWN;
    }
    else if (IsKeyPressed(KEY_LEFT) && s->previous_direction != RIGHT)
    {
        s->direction = LEFT;
    }
    else if (IsKeyPressed(KEY_RIGHT) && s->previous_direction != LEFT)
    {
        s->direction = RIGHT;
    }

    game_data->tick_timer -= GetFrameTime();
    if (game_data->tick_timer < 0.0)
    {
        game_data->tick_count++;

        snake_update(s);
        s->previous_direction = s->direction;

        // Eating food
        if (s->positions[0] == game_data->apple)
        {
            game_data->apple = vec2(GetRandomValue(1, 28), GetRandomValue(1, 28));
            snake_increment(s);

            int extra_score = 1 + (game_data->boost - 1.0) * 10.0;
            extra_score += s->length / 5;
            game_data->score += extra_score;

            if (game_data->score > game_data->boost_threshold)
            {
                game_data->boost_threshold += 15 * (game_data->boost - 1.0) * 10.0;
                game_data->boost += 0.1;
            }

            struct GameEvent event            = {.identifier = GME_FOOD_EATEN};
            event.data.food_eaten.score_delta = extra_score;
            event.data.food_eaten.new_score   = game_data->score;
            mq_push(event);
        }

        game_data->tick_timer = game_data->delay_time / game_data->boost;
    }

    // Death and Game Over
    if (s->life <= 0)
    {
        struct GameEvent event = {.identifier = GME_POP_SCENE};
        mq_push(event);

        event.identifier               = GME_PUSH_SCENE;
        event.data.push_scene.scene_fn = get_scene_end_game;
        mq_push(event);

        kv_set_value(KVI_SCORE, game_data->score);
    }
}

static void game_draw()
{
    Snake* const s = &game_data->snake;

    // Draw the snake
    for (int i = 0; i < s->length; i++)
    {
        Color color = WHITE;
        color.g     = (s->invulnerable > 0) ? 0 : 255;
        color.a     = (s->invulnerable > 0) ? 100 : 255;

        float t = 1.0 - (float)i / (float)s->length;
        color.r = 150 + (255 - 150) * t;
        color.g = 150 + (255 - 150) * t;
        color.b = 150 + (255 - 150) * t;

        Rectangle rect = resources_get_sprite_rect((i == 0) ? SR_SNAKE_HEAD : SR_SNAKE_BODY);
        DrawTexturePro(*game_data->sprite_sheet,
                       rect,
                       (Rectangle){snake_x(s, i) * 20, snake_y(s, i) * 20, 20, 20},
                       (Vector2){0, 0},
                       0,
                       color);
    }

    // Draw the food
    DrawTexturePro(*game_data->sprite_sheet,
                   resources_get_sprite_rect(SR_APPLE),
                   (Rectangle){vec2_x(game_data->apple) * 20, vec2_y(game_data->apple) * 20, 20, 20},
                   (Vector2){0, 0},
                   0,
                   WHITE);

    // Draw Hearts / Life
    for (int i = 0; i < MAX_LIFE; i++)
    {
        enum SpriteRect texture = (i < s->life) ? SR_HEART : SR_EMPTY_HEART;
        DrawTexturePro(*game_data->sprite_sheet,
                       resources_get_sprite_rect(texture),
                       (Rectangle){10 + i * 36, 10, 24, 24},
                       (Vector2){0, 0},
                       0,
                       WHITE);
    }

    // Draw Score
    const char* score_text = TextFormat("Score: %d", game_data->score);
    Vector2 score_size     = MeasureTextEx(*game_data->font, score_text, 24, 0);
    DrawTextEx(*game_data->font, score_text, (Vector2){600 - score_size.x - 20, 10}, 24, 0.0, LIGHTGRAY);

    // Draw info
    if (game_data->tick_count < 15)
    {
        DrawTextEx(*game_data->font, "Use arrow keys to move", (Vector2){20, 600 - 40}, 20, 0.0, LIGHTGRAY);
    }
    else if (game_data->tick_count < 30)
    {
        DrawTextEx(*game_data->font, "Good luck.", (Vector2){20, 600 - 40}, 20, 0.0, LIGHTGRAY);
    }

    if (game_data->boost > 1.0)
    {
        Color color = game_data->boost < 1.5 ? YELLOW : RED;
        color.a     = 100;
        DrawTextEx(*game_data->font, TextFormat("%.2fx!", game_data->boost), (Vector2){20, 600 - 52}, 32, 0.0, color);
    }
}

static void game_uninit()
{
    mq_unlisten(on_snake_damaged);

    free(game_data);
    game_data = NULL;
}

static Scene game_scene = {
    .initialized = 0,
    .init        = game_init,
    .update      = game_update,
    .draw        = game_draw,
    .uninit      = game_uninit,
};

Scene* get_scene_game()
{
    return &game_scene;
}
