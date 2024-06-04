#include "scenes/menu.h"
#include "scenes/scene.h"
#include "resources.h"

#include <stdlib.h>

#include <raylib.h>

typedef struct MenuData
{
    Font *game_font;
    Texture2D *title_texture;
} MenuData;

static const char *menu_options[] = {
    "Play",
    "Credits",
    "Exit",
};

static MenuData *menu_data = NULL;

static void menu_init()
{
    menu_data = malloc(sizeof(MenuData));
    menu_data->game_font = resources_get_font();
    menu_data->title_texture = resources_get_sprite(1);
}

static void menu_update()
{
    if (IsKeyPressed(KEY_P)) {
        // TRANSITION STATE
    }
}

static void menu_draw()
{
    DrawTextureEx(*menu_data->title_texture, (Vector2){300 - menu_data->title_texture->width, 75}, 0, 2.0, WHITE);

    for (int i = 0; i < 3; i++)
    {
        Vector2 size = MeasureTextEx(*menu_data->game_font, menu_options[i], 32, 0);
        DrawTextEx(*menu_data->game_font, menu_options[i], (Vector2){300 - size.x / 2, 325 + 40 * i}, 32, 0, WHITE);
    }
}

static void menu_uninit()
{
    free(menu_data);
    menu_data = NULL;
}

static Scene menu_scene = {
    .initialized = 0,
    .init = menu_init,
    .update = menu_update,
    .draw = menu_draw,
    .uninit = menu_uninit,
};

Scene *get_scene_menu()
{
    return &menu_scene;
}
