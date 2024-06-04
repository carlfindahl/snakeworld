#include "scenes/scene.h"
#include "scenes/game.h"
#include "game_math.h"
#include "snake.h"
#include "resources.h"

#include <stdlib.h>
#include <stdint.h>

#include <raylib.h>

#define INITIAL_SNAKE_LENGTH 3
#define INITIAL_TICK_TIME 1.0f
#define BASE_GAME_SPEED 0.3f

typedef struct GameData
{
    Snake snake;
    float tick_timer;
    float delay_time;
    float boost;
    int score;
    uint32_t apple;
    Texture2D *sprite_sheet;
    Font *font;
} GameData;

static GameData *game_data = NULL;

static void game_init()
{
    game_data = malloc(sizeof(GameData));
    game_data->apple = vec2(10, 10);
    game_data->snake = init_snake(13, 15, INITIAL_SNAKE_LENGTH);
    game_data->score = 0;
    game_data->boost = 1.0f;
    game_data->tick_timer = INITIAL_TICK_TIME;
    game_data->delay_time = BASE_GAME_SPEED;
    game_data->sprite_sheet = resources_get_sprite(TEXID_SPRITES);
    game_data->font = resources_get_font();
}

static void game_update()
{
    Snake *s = &game_data->snake;

    // Direction change
    if (IsKeyPressed(KEY_UP) && s->direction != DOWN)
    {
        s->direction = UP;
    }
    else if (IsKeyPressed(KEY_DOWN) && s->direction != UP)
    {
        s->direction = DOWN;
    }
    else if (IsKeyPressed(KEY_LEFT) && s->direction != RIGHT)
    {
        s->direction = LEFT;
    }
    else if (IsKeyPressed(KEY_RIGHT) && s->direction != LEFT)
    {
        s->direction = RIGHT;
    }

    game_data->tick_timer -= GetFrameTime();
    if (game_data->tick_timer < 0.0)
    {
        snake_update(s);

        // Eat apple
        if (s->positions[0] == game_data->apple)
        {
            game_data->apple = vec2(GetRandomValue(1, 28), GetRandomValue(1, 28));
            snake_increment(s);
            PlaySound(*resources_get_sound(SFE_EAT));
            ++game_data->score;
        }

        game_data->tick_timer = game_data->delay_time;
    }
}

static void game_draw()
{
    Snake *const s = &game_data->snake;

    // Draw the snake
    for (int i = 0; i < s->length; i++)
    {
        Color color = WHITE;
        color.g = (s->invulnerable > 0) ? 0 : 255;
        color.a = (s->invulnerable > 0) ? 100 : 255;

        float t = 1.0 - (float)i / (float)s->length;
        color.r = 150 + (255 - 150) * t;
        color.g = 150 + (255 - 150) * t;
        color.b = 150 + (255 - 150) * t;

        Rectangle rect = resources_get_sprite_rect((i == 0) ? SR_SNAKE_HEAD : SR_SNAKE_BODY);
        DrawTexturePro(*game_data->sprite_sheet, rect, (Rectangle){snake_x(s, i) * 20, snake_y(s, i) * 20, 20, 20}, (Vector2){0, 0}, 0, color);
    }

    // Draw the food
    DrawTexturePro(*game_data->sprite_sheet, resources_get_sprite_rect(SR_APPLE), (Rectangle){vec2_x(game_data->apple) * 20, vec2_y(game_data->apple) * 20, 20, 20}, (Vector2){0, 0}, 0, WHITE);

    // Draw Hearts / Life
    for (int i = 0; i < s->life; i++)
    {
        DrawTexturePro(*game_data->sprite_sheet, resources_get_sprite_rect(SR_HEART), (Rectangle){10 + i * 36, 10, 24, 24}, (Vector2){0, 0}, 0, WHITE);
    }

    // Draw Score
    DrawTextEx(*game_data->font, TextFormat("Score: %d", game_data->score), (Vector2){600 - 160, 10}, 24, 0.0, LIGHTGRAY);
}

static void game_uninit()
{
    free(game_data);
    game_data = NULL;
}

static Scene game_scene = {
    .initialized = 0,
    .init = game_init,
    .update = game_update,
    .draw = game_draw,
    .uninit = game_uninit,
};

Scene *get_scene_game()
{
    return &game_scene;
}
