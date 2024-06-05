#ifndef H_SCENE_H
#define H_SCENE_H

#define MAX_SCENES 10

enum SceneCommand
{
    SCENE_COMMAND_NONE,
    SCENE_COMMAND_QUIT,
    SCENE_COMMAND_PUSH_GAME,
    SCENE_COMMAND_PUSH_MENU,
    SCENE_COMMAND_PUSH_GAME_OVER,
    SCENE_COMMAND_PUSH_CREDITS,
    SCENE_COMMAND_POP,
};

/**
 * Scene structure for the game
 */
typedef struct Scene
{
    int initialized;
    void (*init)();
    enum SceneCommand (*update)();
    void (*draw)();
    void (*uninit)();
} Scene;

typedef struct SceneManager
{
    Scene scene[MAX_SCENES];
    int top;
} SceneManager;

SceneManager scene_manager_create();

void scene_manager_push(SceneManager *sm, Scene s);

void scene_manager_pop(SceneManager *sm);

enum SceneCommand scene_manager_update(SceneManager *sm);

void scene_manager_draw(SceneManager *sm);

void scene_manager_uninit(SceneManager *sm);

#endif
