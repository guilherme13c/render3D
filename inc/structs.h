#pragma once

#include "geometry.h"
#include <SDL2/SDL.h>

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *window_surface;

    std::vector<Object3D> objs3D;
    std::vector<Object2D> objs2D;

    bool leftMouseButtonDown, rightMouseButtonDown;
    int initialMouseX, initialMouseY;
    float zoomLevel;
} App;

void newApp(App &app);
