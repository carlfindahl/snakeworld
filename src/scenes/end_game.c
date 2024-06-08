#include "scenes/end_game.h"
#include "kv_store.h"
#include "message_queue.h"
#include "resources.h"
#include "scenes/scene.h"

#include <stdlib.h>

#include <raylib.h>

static Font* font              = NULL;
static Texture2D* sprite_sheet = NULL;
static int game_score          = 0;

void scene_end_game_init()
{
    int* score_ptr = NULL;

    font         = resources_get_font();
    sprite_sheet = resources_get_sprite(TEXID_SPRITES);

    if (kv_get_value(KVI_SCORE, &score_ptr))
    {
        game_score = *score_ptr;
    }
    else
    {
        printf("Failed to get score from kv_store\n");
    }
}

void scene_end_game_update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        struct GameEvent event = {.identifier = GME_POP_SCENE};
        mq_push(event);
    }
}

void scene_end_game_draw()
{
    Vector2 text_size = MeasureTextEx(*font, "Game Over", 32, 0);
    DrawTextEx(*font, "Game Over", (Vector2){300 - text_size.x / 2.0, 128}, 32, 0, RED);

    const char* score_text = TextFormat("You scored %d points", game_score);
    text_size              = MeasureTextEx(*font, score_text, 20, 0);
    DrawTextEx(*font, score_text, (Vector2){300 - text_size.x / 2.0, 200}, 20, 0, LIGHTGRAY);

    score_text = TextFormat("%d", game_score);
    text_size  = MeasureTextEx(*font, score_text, 48, 0);
    DrawTextEx(*font, score_text, (Vector2){300 - text_size.x / 2.0, 245}, 48, 0, YELLOW);

    text_size = MeasureTextEx(*font, "Press Enter to return to the main menu", 20, 0);
    DrawTextEx(*font, "Press Enter to return to the main menu", (Vector2){300 - text_size.x / 2.0, 320}, 20, 0, WHITE);

    DrawTexturePro(*sprite_sheet,
                   resources_get_sprite_rect(SR_TOMBSTONE),
                   (Rectangle){250.0, 400.0, 100.0, 100.0},
                   (Vector2){0.0, 0.0},
                   0.0,
                   WHITE);
}

void scene_end_game_uninit()
{
}

static Scene end_game_scene = (Scene){
    .initialized = 0,
    .init        = scene_end_game_init,
    .update      = scene_end_game_update,
    .draw        = scene_end_game_draw,
    .uninit      = scene_end_game_uninit,
};

Scene* get_scene_end_game()
{
    return &end_game_scene;
}
