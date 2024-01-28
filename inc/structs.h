#pragma once

#include <SDL2/SDL.h>
#include "geometry.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Surface *window_surface;

    std::vector<Object3D> objs3D;
    std::vector<Object2D> objs2D;
} App;
