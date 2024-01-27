#include "init.h"

void initSDL(Env &cfg, App &app) {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow(
        cfg["WINDOW_NAME"].c_str(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, std::stoi(cfg["WINDOW_WIDTH"]),
        std::stoi(cfg["WINDOW_HEIGHT"]), windowFlags);

    if (!app.window) {
        printf("Failed to open %d x %d window: %s\n",
               std::stoi(cfg["WINDOW_WIDTH"]), std::stoi(cfg["WINDOW_HEIGHT"]),
               SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}
