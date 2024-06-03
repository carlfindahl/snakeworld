#include "resources.h"

#include <raylib.h>

// Resource storage
static Sound sounds[4];
static Texture2D sprite_rects[4];

bool initialized = false;

void resources_load()
{
    if (!initialized)
    {
        sounds[SFE_CLICK] = LoadSound("res/click.wav");
        sounds[SFE_EAT] = LoadSound("res/eat.wav");
        sounds[SFE_NOTIFICATION] = LoadSound("res/notification.wav");
        sounds[SFE_PAIN] = LoadSound("res/pain.wav");

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
