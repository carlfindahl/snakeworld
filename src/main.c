#include <raylib.h>
#include <stdio.h>
#include <stdint.h>

#include "snake.h"
#include "resources.h"
#include "game_math.h"
#include "scenes/scene.h"
#include "scenes/game.h"
#include "scenes/menu.h"

enum PlayState
{
    PS_MENU,
    PS_PLAYING,
    PS_GAME_OVER,
};

// Size of each tile
const int TILE_SIZE = 20;

// Size of the render texture that is blitted to the full screen
const int RENDER_SIZE = 600;

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 600, "Snake World");
    InitAudioDevice();
    SetTargetFPS(60);

    Music theme = LoadMusicStream("res/snakeworld_theme.ogg");
    theme.looping = true;
    PlayMusicStream(theme);

    SceneManager scene_manager = scene_manager_create();
    scene_manager_push(&scene_manager, *get_scene_menu());

    RenderTexture2D target = LoadRenderTexture(RENDER_SIZE, RENDER_SIZE);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    Shader shader = LoadShader(0, "post.fs");

    resources_load();

    while (!WindowShouldClose())
    {
        UpdateMusicStream(theme);

        scene_manager_update(&scene_manager);

        if (IsKeyPressed(KEY_R))
        {
            UnloadShader(shader);
            shader = LoadShader(0, "post.fs");
        }

        if (IsWindowResized())
        {
            int width = GetScreenWidth();
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
        scene_manager_draw(&scene_manager);
        DrawRectangleLinesEx((Rectangle){0, 0, 600, 600}, 5, DARKBLUE);
        EndTextureMode();

        // Render post process on texture
        BeginDrawing();
        float time = GetTime();
        BeginShaderMode(shader);
        SetShaderValueV(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT, 1);
        DrawTexturePro(target.texture, (Rectangle){0, 0, RENDER_SIZE, -RENDER_SIZE}, (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()}, (Vector2){0, 0}, 0, WHITE);
        EndShaderMode();

        EndDrawing();
    }

    resources_unload();

    UnloadShader(shader);
    UnloadRenderTexture(target);

    scene_manager_uninit(&scene_manager);

    StopMusicStream(theme);
    UnloadMusicStream(theme);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
