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

int main()
{
    InitWindow(600, 600, "Snake World");
    InitAudioDevice();
    SetTargetFPS(60);

    Music theme = LoadMusicStream("res/snakeworld_theme.ogg");
    theme.looping = true;
    PlayMusicStream(theme);

    SceneManager scene_manager = scene_manager_create();
    scene_manager_push(&scene_manager, *get_scene_menu());

    Snake s = init_snake(13, 15, 3);
    double time = 1.0;
    int score = 0;
    float delay_time = 0.16f;
    float boost = 1.0f;

    int apple = vec2(10, 10);

    RenderTexture2D target = LoadRenderTexture(600, 600);
    Shader shader = LoadShader(0, "post.fs");

    resources_load();
    Texture2D *sprite_sheet = resources_get_sprite(TEXID_SPRITES);

    while (!WindowShouldClose())
    {
        UpdateMusicStream(theme);

        scene_manager_update(&scene_manager);

        if (IsKeyPressed(KEY_R))
        {
            UnloadShader(shader);
            shader = LoadShader(0, "post.fs");
        }
        else if (IsKeyPressed(KEY_P))
        {
            scene_manager_push(&scene_manager, *get_scene_game());
        } else if (IsKeyPressed(KEY_M))
        {
            scene_manager_pop(&scene_manager);
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
        DrawTextureRec(target.texture, (Rectangle){0, 0, 600, -600}, (Vector2){0, 0}, WHITE);
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
