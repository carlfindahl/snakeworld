#include <raylib.h>

enum SoundEffect
{
    SFE_CLICK,
    SFE_EAT,
    SFE_NOTIFICATION,
    SFE_PAIN,
    SFE_COUNT,
};

enum SpriteRect
{
    SR_SNAKE_HEAD,
    SR_SNAKE_BODY,
    SR_APPLE,
    SR_HEART,
    SR_EMPTY_HEART,
    SR_TOMBSTONE,
    SR_WALL,
    SR_COUNT,
};

enum TextureId
{
    TEXID_SPRITES,
    TEXID_TITLE,
    TEXID_COUNT,
};

/// Load all required game resources
void resources_load();

/// Unload all game resources
void resources_unload();

/// Get a sound effect - if not initialized, will initialize
Sound* resources_get_sound(enum SoundEffect se);

/// Get a sprite rectangle for the given resource
Rectangle resources_get_sprite_rect(enum SpriteRect sr);

/// Get a sprite for the given resource
Texture2D* resources_get_sprite(enum TextureId id);

/// Get the main Game Font
Font* resources_get_font();
