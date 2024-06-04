#ifndef H_SCENE_H
#define H_SCENE_H

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

enum SceneCommand
{
    SCENE_QUIT,
    SCENE_PUSH_GAME,
    SCENE_PUSH_MENU,
    SCENE_POP,
};

SceneManager scene_manager_create();

void scene_manager_push(SceneManager *sm, Scene s);

void scene_manager_pop(SceneManager *sm);

void scene_manager_update(SceneManager *sm);

void scene_manager_draw(SceneManager *sm);

void scene_manager_uninit(SceneManager *sm);

#endif
