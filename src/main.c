#include "game_math.h"
#include "message_queue.h"
#include "resources.h"
#include "scenes/credits.h"
#include "scenes/end_game.h"
#include "scenes/game.h"
#include "scenes/menu.h"
#include "scenes/scene.h"
#include "snake.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Size of each tile
const int TILE_SIZE = 20;

// Size of the render texture that is blitted to the full screen
const int RENDER_SIZE = 600;

struct SceneCommandContext
{
    SceneManager* scene_manager;
    int* keep_running;
};

void observe_sfx(void* _, struct GameEvent* event)
{
    switch (event->identifier)
    {
        case GME_SNAKE_DAMAGED: PlaySound(*resources_get_sound(SFE_PAIN)); break;
        case GME_FOOD_EATEN: PlaySound(*resources_get_sound(SFE_EAT)); break;
        default: break;
    }
}

void observe_scene_commands(void* scene_context, struct GameEvent* event)
{
    struct SceneCommandContext* sc = scene_context;

    switch (event->identifier)
    {
        case GME_PUSH_SCENE: scene_manager_push(sc->scene_manager, *event->data.push_scene.scene_fn()); break;
        case GME_POP_SCENE: scene_manager_pop(sc->scene_manager); break;
        case GME_QUIT_GAME: memset(sc->keep_running, 0, sizeof(int)); break;
        default: break;
    }
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 600, "Snake World");
    InitAudioDevice();
    SetTargetFPS(60);

    Music theme   = LoadMusicStream("res/snakeworld_theme.ogg");
    theme.looping = true;
    PlayMusicStream(theme);

    SceneManager scene_manager = scene_manager_create();
    scene_manager_push(&scene_manager, *get_scene_menu());

    RenderTexture2D target = LoadRenderTexture(RENDER_SIZE, RENDER_SIZE);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    Shader shader = LoadShader(0, "post.fs");

    resources_load();
    mq_init();

    int keep_running = 1;
    bool enable_post = true;

    // Observe scene commands
    struct SceneCommandContext scene_manager_context = {&scene_manager, &keep_running};
    mq_listen((Observer){&scene_manager_context, observe_scene_commands});
    mq_listen((Observer){NULL, observe_sfx});

    while (!WindowShouldClose() && keep_running)
    {
        UpdateMusicStream(theme);

        scene_manager_update(&scene_manager);
        mq_process();

        // Debug keys
        if (IsKeyPressed(KEY_R))
        {
            enable_post = !enable_post;
        }

        if (IsWindowResized())
        {
            int width  = GetScreenWidth();
            int height = GetScreenHeight();

            if (!IsWindowFullscreen())
            {
                if (width > height)
                {
                    SetWindowSize(height, height);
                }
                else
                {
                    SetWindowSize(width, width);
                }
            }
        }

        // Render on to a texture
        BeginTextureMode(target);
        ClearBackground((Color){0, 25, 40, 255});

        DrawTexturePro(*resources_get_sprite(TEXID_BACKGROUND),
                       (Rectangle){0, 0, RENDER_SIZE, RENDER_SIZE},
                       (Rectangle){0, 0, RENDER_SIZE, RENDER_SIZE},
                       (Vector2){0, 0},
                       0,
                       WHITE);

        scene_manager_draw(&scene_manager);
        DrawRectangleLinesEx((Rectangle){0, 0, RENDER_SIZE, RENDER_SIZE}, 5, DARKBLUE);
        EndTextureMode();

        // Render post process on texture
        BeginDrawing();

        if (enable_post)
        {
            float time = GetTime();
            BeginShaderMode(shader);
            SetShaderValueV(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT, 1);
        }

        DrawTexturePro(target.texture,
                       (Rectangle){0, 0, RENDER_SIZE, -RENDER_SIZE},
                       (Rectangle){0.0, 0, GetScreenWidth(), GetScreenHeight()},
                       (Vector2){0, 0},
                       0,
                       WHITE);

        if (enable_post)
        {
            EndShaderMode();
        }

        EndDrawing();
    }

    scene_manager_uninit(&scene_manager);

    mq_unlisten(observe_sfx);
    mq_unlisten(observe_scene_commands);
    mq_free();

    resources_unload();

    UnloadShader(shader);
    UnloadRenderTexture(target);

    StopMusicStream(theme);
    UnloadMusicStream(theme);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
