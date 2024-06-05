#include "scenes/end_game.h"
#include "scenes/scene.h"
#include "resources.h"

#include <stdlib.h>

#include <raylib.h>

static Font *font = NULL;
static Texture2D* sprite_sheet = NULL;

void scene_end_game_init()
{
    font = resources_get_font();
    sprite_sheet = resources_get_sprite(TEXID_SPRITES);
}

enum SceneCommand scene_end_game_update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        return SCENE_COMMAND_POP;
    }

    return SCENE_COMMAND_NONE;
}

void scene_end_game_draw()
{
    Vector2 text_size = MeasureTextEx(*font, "Game Over", 32, 0);
    DrawTextEx(*font, "Game Over", (Vector2){300 - text_size.x / 2.0, 200}, 32, 0, RED);

    text_size = MeasureTextEx(*font, "Press Enter to return to the main menu", 20, 0);
    DrawTextEx(*font, "Press Enter to return to the main menu", (Vector2){300 - text_size.x / 2.0, 250}, 20, 0, WHITE);

    DrawTexturePro(*sprite_sheet, resources_get_sprite_rect(SR_TOMBSTONE), (Rectangle){250.0, 400.0, 100.0, 100.0}, (Vector2){0.0, 0.0}, 0.0, WHITE);
}

void scene_end_game_uninit()
{
}

static Scene end_game_scene = (Scene){
    .initialized = 0,
    .init = scene_end_game_init,
    .update = scene_end_game_update,
    .draw = scene_end_game_draw,
    .uninit = scene_end_game_uninit,
};

Scene *get_scene_end_game()
{
    return &end_game_scene;
}
