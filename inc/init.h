#pragma once

#include "config.h"
#include "geometry.h"
#include "structs.h"
#include <SDL2/SDL.h>

void initSDL(Env &cfg, App &app);

void killSDL(App &app);

void main_loop(Env &cfg, App &app, std::vector<Object3D> &objs3D,
               std::vector<Object2D> &objs2D);

void event_loop(bool &keep_window_open);

void draw(SDL_Renderer *renderer, SDL_Window *window,
          std::vector<Object3D> &objs3D, std::vector<Object2D> &objs2D);
