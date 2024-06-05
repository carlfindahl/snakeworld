#include "resources.h"

#include <raylib.h>

// Resource storage
static Sound sounds[SFE_COUNT];
static Texture2D sprites[TEXID_COUNT];
static Rectangle sprite_rects[SR_COUNT];
static Font game_font;

bool initialized = false;

void resources_load()
{
    if (!initialized)
    {
        sounds[SFE_CLICK] = LoadSound("res/click.wav");
        sounds[SFE_EAT] = LoadSound("res/eat.wav");
        sounds[SFE_NOTIFICATION] = LoadSound("res/notification.wav");
        sounds[SFE_PAIN] = LoadSound("res/pain.wav");

        sprites[TEXID_SPRITES] = LoadTexture("res/sprites.png");
        sprites[TEXID_TITLE] = LoadTexture("res/title.png");

        game_font = LoadFont("res/VCR_FONT.ttf");

        sprite_rects[SR_SNAKE_HEAD] = (Rectangle){0, 0, 16, 16};
        sprite_rects[SR_SNAKE_BODY] = (Rectangle){16, 0, 16, 16};
        sprite_rects[SR_APPLE] = (Rectangle){0, 16, 16, 16};
        sprite_rects[SR_HEART] = (Rectangle){16, 16, 16, 16};
        sprite_rects[SR_TOMBSTONE] = (Rectangle){0, 32, 16, 16};
        sprite_rects[SR_EMPTY_HEART] = (Rectangle){16, 32, 16, 16};

        initialized = true;
    }
}

Sound *resources_get_sound(enum SoundEffect se)
{
    if (!initialized)
    {
        resources_load();
    }

    return &sounds[se];
}

Rectangle resources_get_sprite_rect(enum SpriteRect sr)
{
    return sprite_rects[sr];
}

Texture2D *resources_get_sprite(enum TextureId id)
{
    return &sprites[id];
}

Font *resources_get_font()
{
    return &game_font;
}

void resources_unload()
{
    if (initialized)
    {
        for (int i = 0; i < SFE_COUNT; i++)
        {
            UnloadSound(sounds[i]);
        }

        for (int i = 0; i < TEXID_COUNT; i++)
        {
            UnloadTexture(sprites[i]);
        }

        UnloadFont(game_font);
    }
}
