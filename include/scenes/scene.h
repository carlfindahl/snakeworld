#pragma once

#define MAX_SCENES 10

/**
 * Scene structure for the game
 */
typedef struct Scene
{
    int initialized;
    void (*init)();
    void (*update)();
    void (*draw)();
    void (*uninit)();
} Scene;

typedef struct SceneManager
{
    Scene scene[MAX_SCENES];
    int top;
} SceneManager;

SceneManager scene_manager_create();

void scene_manager_push(SceneManager* sm, Scene s);

void scene_manager_pop(SceneManager* sm);

void scene_manager_update(SceneManager* sm);

void scene_manager_draw(SceneManager* sm);

void scene_manager_uninit(SceneManager* sm);
