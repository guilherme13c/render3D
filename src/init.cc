#include "init.h"

void initSDL(Env &cfg, App &app) {
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

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

    app.window_surface = SDL_GetWindowSurface(app.window);

    if (!app.window_surface) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_UpdateWindowSurface(app.window);

    main_loop(cfg, app);

    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

void main_loop(Env &cfg, App &app) {
    bool keep_window_open = true;
    while (keep_window_open) {
        event_loop(keep_window_open);
        draw(app.renderer);
    }
}

void event_loop(bool &keep_window_open) {
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0) {
        switch (e.type) {
        case SDL_QUIT:
            keep_window_open = false;
            break;
        }
    }
}

void draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLineF(renderer, 0, 0, 100, 100);

    SDL_RenderPresent(renderer);
}
