#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "scenes/scene.h"

SceneManager scene_manager_create()
{
    SceneManager sm;
    sm.top = -1;
    return sm;
}

void scene_manager_push(SceneManager *sm, Scene s)
{
    if (sm->top == MAX_SCENES - 1)
    {
        printf("\nWARN: Scene stack full\n");
        return;
    }

    if (!s.initialized)
    {
        s.init();
        s.initialized = 1;
    }

    sm->top++;
    sm->scene[sm->top] = s;
}

void scene_manager_pop(SceneManager *sm)
{
    if (sm->top == -1)
    {
        return;
    }

    sm->scene[sm->top].uninit();
    memset(&sm->scene[sm->top], 0, sizeof(Scene));
    sm->top--;
}

enum SceneCommand scene_manager_update(SceneManager *sm)
{
    if (sm->top == -1)
    {
        return SCENE_COMMAND_NONE;
    }

    return sm->scene[sm->top].update();
}

void scene_manager_draw(SceneManager *sm)
{
    if (sm->top == -1)
    {
        return;
    }

    sm->scene[sm->top].draw();
}

void scene_manager_uninit(SceneManager *sm)
{
    for (int i = sm->top; i > -1; i--)
    {
        if (sm->scene[i].initialized)
        {
            sm->scene[i].uninit();
            sm->scene[i].initialized = 0;
        }
    }

    memset(sm->scene, 0, sizeof(sm->scene));
    sm->top = -1;
}