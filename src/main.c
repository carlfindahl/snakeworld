#include <raylib.h>
#include <stdio.h>
#include <stdint.h>

#include "snake.h"
#include "resources.h"

enum PlayState {
    PS_MENU,
    PS_PLAYING,
    PS_GAME_OVER,
};

uint32_t vec2(uint32_t x, uint32_t y)
{
    return x | (y << 16);
}

uint32_t vec2_x(uint32_t v)
{
    return v & 0xFFFF;
}

uint32_t vec2_y(uint32_t v)
{
    return v >> 16;
}

int main()
{
    InitWindow(600, 600, "Snake World");
    InitAudioDevice();
    SetTargetFPS(60);

    Music theme = LoadMusicStream("res/snakeworld_theme.ogg");
    theme.looping = true;
    PlayMusicStream(theme);

    struct snake s = init_snake(13, 15);
    double time = 1.0;
    int score = 0;
    float delay_time = 0.16f;
    float boost = 1.0f;

    int apple = vec2(10, 10);

    RenderTexture2D target = LoadRenderTexture(600, 600);
    Shader shader = LoadShader(0, "post.fs");
    Font font = LoadFont("res/VCR_FONT.ttf");

    resources_load();
    Texture2D *sprite_sheet = resources_get_sprite_sheet();

    while (!WindowShouldClose())
    {
        UpdateMusicStream(theme);

        time -= GetFrameTime();

        if (IsKeyPressed(KEY_R))
        {
            UnloadShader(shader);
            shader = LoadShader(0, "post.fs");
        }

        // Direction change
        if (IsKeyPressed(KEY_UP) && s.direction != DOWN)
        {
            s.direction = UP;
        }
        else if (IsKeyPressed(KEY_DOWN) && s.direction != UP)
        {
            s.direction = DOWN;
        }
        else if (IsKeyPressed(KEY_LEFT) && s.direction != RIGHT)
        {
            s.direction = LEFT;
        }
        else if (IsKeyPressed(KEY_RIGHT) && s.direction != LEFT)
        {
            s.direction = RIGHT;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
        {
            boost = 0.6;
        }
        else
        {
            boost = 1.0;
        }

        if (time < 0.0)
        {
            snake_update(&s);

            // Eat apple
            if (s.positions[0] == apple)
            {
                apple = vec2(GetRandomValue(1, 28), GetRandomValue(1, 28));
                snake_increment(&s);
                PlaySound(*resources_get_sound(SFE_EAT));
                ++score;
            }

            time = delay_time * boost;
        }

        // Render on to a texture
        BeginTextureMode(target);
        ClearBackground((Color){0, 25, 40, 255});
        for (int i = 0; i < s.length; i++)
        {
            Color color = WHITE;
            color.g = (s.invulnerable > 0) ? 0 : 255;
            color.a = (s.invulnerable > 0) ? 100 : 255;

            float t = 1.0 - (float)i / (float)s.length;
            color.r = 150 + (255 - 150) * t;
            color.g = 150 + (255 - 150) * t;
            color.b = 150 + (255 - 150) * t;

            Rectangle rect = resources_get_sprite_rect((i == 0) ? SR_SNAKE_HEAD : SR_SNAKE_BODY);
            DrawTexturePro(*sprite_sheet, rect, (Rectangle){snake_x(&s, i) * 20, snake_y(&s, i) * 20, 20, 20}, (Vector2){0, 0}, 0, color);
        }

        DrawTexturePro(*sprite_sheet, resources_get_sprite_rect(SR_APPLE), (Rectangle){vec2_x(apple) * 20, vec2_y(apple) * 20, 20, 20}, (Vector2){0, 0}, 0, WHITE);
        DrawRectangleLinesEx((Rectangle){0, 0, 600, 600}, 5, DARKBLUE);

        for (int i = 0; i < s.life; i++)
        {
            DrawTexturePro(*sprite_sheet, resources_get_sprite_rect(SR_HEART), (Rectangle){10 + i * 36, 10, 24, 24}, (Vector2){0, 0}, 0, WHITE);
        }

        DrawTextEx(font, TextFormat("Score: %d", score), (Vector2){600 - 160, 10}, 24, 0.0, LIGHTGRAY);

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

    UnloadFont(font);
    UnloadShader(shader);
    UnloadRenderTexture(target);

    StopMusicStream(theme);
    UnloadMusicStream(theme);

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
