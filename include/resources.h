#ifndef H_RESOURCES_H
#define H_RESOURCES_H

#include <raylib.h>

enum SoundEffect
{
    SFE_CLICK,
    SFE_EAT,
    SFE_NOTIFICATION,
    SFE_PAIN,
};

enum SpriteRect
{
    SR_SNAKE_HEAD,
    SR_SNAKE_BODY,
    SR_APPLE,
    SR_HEART,
};

/// Load all required game resources
void resources_load();

/// Unload all game resources
void resources_unload();

/// Get a sound effect - if not initialized, will initialize
Sound *resources_get_sound(enum SoundEffect se);

/// Get a sprite rectangle for the given resource
Rectangle resources_get_sprite_rect(enum SpriteRect sr);

/// Get a texture for the given resource
Texture2D *resources_get_sprite_sheet();

#endif