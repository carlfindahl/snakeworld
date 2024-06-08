#include "scenes/credits.h"
#include "message_queue.h"
#include "resources.h"
#include "scenes/scene.h"

#include <stdlib.h>

#include <math.h>
#include <raylib.h>

static Font* font       = NULL;
static Texture2D* title = NULL;

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
    font  = resources_get_font();
    title = resources_get_sprite(TEXID_TITLE);
}

void credits_update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        struct GameEvent event = {.identifier = GME_POP_SCENE};
        mq_push(event);
    }
}

void credits_draw()
{
    Vector2 size = MeasureTextEx(*font, "A game by Daali Spill 2024", 24, 0);
    DrawTextEx(*font, "A game by Daali Spill 2024", (Vector2){300 - size.x / 2.0, 450.0}, 24, 0, WHITE);

    size = MeasureTextEx(*font, "Art by Daali Spill - Background by Midjourney", 16, 0);
    DrawTextEx(*font, "Art by Daali Spill - Background by Midjourney", (Vector2){300 - size.x / 2.0, 570.0}, 16, 0, LIGHTGRAY);

    size = MeasureTextEx(*font, "Made with Raylib", 16, 0);
    DrawTextEx(*font, "Made with Raylib", (Vector2){300 - size.x / 2.0, 550.0}, 16, 0, LIGHTGRAY);

    size = MeasureTextEx(*font, "Press [ENTER] to return to menu", 16, 0);
    DrawTextEx(*font, "Press [ENTER] to return to menu", (Vector2){300 - size.x / 2.0, 420.0}, 16, 0, WHITE);

    DrawTextureEx(*title,
                  (Vector2){300 - title->width * 1.25, 180},
                  0.0,
                  2.5,
                  colors[(current_color++ / 2) % (sizeof(colors) / sizeof(Color))]);
}

void credits_uninit()
{
}

static Scene credits_scene = {
    .initialized = 0,
    .init        = credits_init,
    .update      = credits_update,
    .draw        = credits_draw,
    .uninit      = credits_uninit,
};

Scene* get_scene_credits()
{
    return &credits_scene;
}