#include "scenes/credits.h"
#include "scenes/scene.h"
#include "resources.h"

#include <stdlib.h>

#include <raylib.h>
#include <math.h>

static Font *font = NULL;
static Texture2D *title = NULL;

static Color colors[] = {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
};

int current_color = 0;

void credits_init()
{
    font = resources_get_font();
    title = resources_get_sprite(TEXID_TITLE);
}

enum SceneCommand credits_update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        return SCENE_COMMAND_POP;
    }

    return SCENE_COMMAND_NONE;
}

void credits_draw()
{
    Vector2 size = MeasureTextEx(*font, "A game by Daali Spill 2024", 24, 0);
    DrawTextEx(*font, "A game by Daali Spill 2024", (Vector2){300 - size.x / 2.0, 500.0}, 24, 0, WHITE);

    size = MeasureTextEx(*font, "Press [ENTER] to return to menu", 16, 0);
    DrawTextEx(*font, "Press [ENTER] to return to menu", (Vector2){300 - size.x / 2.0, 450.0}, 16, 0, WHITE);

    DrawTextureEx(*title, (Vector2){300 - title->width * 1.25, 180}, 0.0, 2.5, colors[current_color++ % (sizeof(colors) / sizeof(Color))]);
}

void credits_uninit()
{
}

static Scene credits_scene = {
    .initialized = 0,
    .init = credits_init,
    .update = credits_update,
    .draw = credits_draw,
    .uninit = credits_uninit,
};

Scene *get_scene_credits()
{
    return &credits_scene;
}