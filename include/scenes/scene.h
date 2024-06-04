#ifndef H_SCENE_H
#define H_SCENE_H

/**
 * Scene structure for the game
 */
typedef struct {
    void (*init)();
    void (*update)();
    void (*draw)();
    void (*uninit)();
} Scene;

#endif
