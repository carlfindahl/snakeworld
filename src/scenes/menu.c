#include "scenes/menu.h"

#include <raylib.h>

static const char* menu_options[] = {
    "Play",
    "Credits",
    "Exit"
};


void menu_init() {
    
}

void menu_update() {

}

void menu_render() {
    for (int i = 0; i < 3; i++) {
        DrawText(menu_options[i], 20, 20 + 40 * i, 20, WHITE);
    }
}

void menu_uninit() {

}
