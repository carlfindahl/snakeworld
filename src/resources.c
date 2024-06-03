#include "resources.h"

#include <raylib.h>

// Resource storage
static Sound sounds[4];
static Texture2D sprite_sheet;
static Rectangle sprite_rects[4];

bool initialized = false;

void resources_load()
{
    if (!initialized)
    {
        sounds[SFE_CLICK] = LoadSound("res/click.wav");
        sounds[SFE_EAT] = LoadSound("res/eat.wav");
        sounds[SFE_NOTIFICATION] = LoadSound("res/notification.wav");
        sounds[SFE_PAIN] = LoadSound("res/pain.wav");

        sprite_sheet = LoadTexture("res/sprites.png");

        sprite_rects[SR_SNAKE_HEAD] = (Rectangle){0, 0, 16, 16};
        sprite_rects[SR_SNAKE_BODY] = (Rectangle){16, 0, 16, 16};
        sprite_rects[SR_APPLE] = (Rectangle){0, 16, 16, 16};
        sprite_rects[SR_HEART] = (Rectangle){16, 16, 16, 16};

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

Rectangle resources_get_sprite_rect(enum SpriteRect sr) {
    return sprite_rects[sr];
}

Texture2D* resources_get_sprite_sheet() {
    return &sprite_sheet;
}

void resources_unload()
{
    if (initialized)
    {
        for (int i = 0; i < 4; i++)
        {
            UnloadSound(sounds[i]);
        }
    }
}
