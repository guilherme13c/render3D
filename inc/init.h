#pragma once

#include "config.h"
#include "geometry.h"
#include "structs.h"
#include <SDL2/SDL.h>

void initSDL(Env &cfg, App &app);

void killSDL(App &app);

void main_loop(Env &cfg, App &app);

void event_loop(bool &keep_window_open, App &app);

void draw(SDL_Renderer *renderer, SDL_Window *window, App &app);
