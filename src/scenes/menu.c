#include "scenes/menu.h"
#include "resources.h"

#include <raylib.h>

Font *game_font = 0;
Texture2D* title_texture = 0;

static const char *menu_options[] = {
    "Play",
    "Credits",
    "Exit",
};

void menu_init()
{
    game_font = resources_get_font();
    title_texture = resources_get_sprite(1);
}

void menu_update()
{
}

void menu_draw()
{
    for (int i = 0; i < 3; i++)
    {
        Vector2 size = MeasureTextEx(*game_font, menu_options[i], 32, 0);
        DrawTextEx(*game_font, menu_options[i], (Vector2){300 - size.x / 2, 250 + 40 * i}, 32, 0, WHITE);
    }
}

void menu_uninit()
{
}

static Scene menu_scene = {
    .initialized = 0,
    .init = menu_init,
    .update = menu_update,
    .draw = menu_draw,
    .uninit = menu_uninit};

Scene *get_scene_menu()
{
    return &menu_scene;
}
