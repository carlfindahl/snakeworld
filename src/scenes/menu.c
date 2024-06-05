#include "scenes/menu.h"
#include "scenes/scene.h"
#include "resources.h"

#include <stdlib.h>
#include <math.h>

#include <raylib.h>

typedef struct MenuData
{
    int selected_menu_option;
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
    menu_data->selected_menu_option = 0;
    menu_data->game_font = resources_get_font();
    menu_data->title_texture = resources_get_sprite(TEXID_TITLE);
}

static enum SceneCommand menu_update()
{
    if (IsKeyPressed(KEY_UP))
    {
        menu_data->selected_menu_option = (menu_data->selected_menu_option - 1 + 3) % 3;
        PlaySound(*resources_get_sound(SFE_CLICK));
    }
    else if (IsKeyPressed(KEY_DOWN))
    {
        menu_data->selected_menu_option = (menu_data->selected_menu_option + 1) % 3;
        PlaySound(*resources_get_sound(SFE_CLICK));
    }
    else if (IsKeyPressed(KEY_ENTER))
    {
        PlaySound(*resources_get_sound(SFE_NOTIFICATION));
        switch (menu_data->selected_menu_option)
        {
        case 0:
            return SCENE_COMMAND_PUSH_GAME;
            break;
        case 1:
            return SCENE_COMMAND_PUSH_CREDITS;
            break;
        case 2:
            return SCENE_COMMAND_QUIT;
            break;
        }
    }

    return SCENE_COMMAND_NONE;
}

static void menu_draw()
{
    double time = GetTime();
    for (int i = 5; i >= 0; i--)
    {
        Color color = i == 0 ? WHITE : YELLOW;
        color.a = i == 0 ? 255 : 25;
        DrawTextureEx(*menu_data->title_texture, (Vector2){300 - menu_data->title_texture->width, 75 + (sin(i * 10 + time) * 10)}, 0.0, 2.0, color);
    }

    for (int i = 0; i < 3; i++)
    {
        Color color = i == menu_data->selected_menu_option ? YELLOW : WHITE;

        Vector2 size = MeasureTextEx(*menu_data->game_font, menu_options[i], 32, 0);
        DrawTextEx(*menu_data->game_font, menu_options[i], (Vector2){300 - size.x / 2, 325 + 40 * i}, 32, 0, color);
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
