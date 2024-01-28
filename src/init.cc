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
}

void killSDL(App &app) {
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

void main_loop(Env &cfg, App &app, std::vector<Object3D> &objs3D,
               std::vector<Object2D> &objs2D) {
    bool keep_window_open = true;
    while (keep_window_open) {
        event_loop(keep_window_open);
        draw(app.renderer, app.window, objs3D, objs2D);
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

void draw(SDL_Renderer *renderer, SDL_Window *window,
          std::vector<Object3D> &objs3D, std::vector<Object2D> &objs2D) {

    const float scale = 100.0f;
    int window_size_x = 0, window_size_y = 0;
    SDL_GetWindowSize(window, &window_size_x, &window_size_y);
    const float centerX = window_size_x / 2.0f, centerY = window_size_y / 2.0f;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (Object3D &obj3D : objs3D) {
        rotate(obj3D, 0, 3.141592 / 1024, 0);
        Object2D obj2D;
        project3DTo2D(obj3D, obj2D, 3.0f, centerX, centerY, scale);

        for (const auto &vertex : obj2D.vertices) {
            const Point2D &start = obj2D.points[vertex.start];
            const Point2D &end = obj2D.points[vertex.end];
            SDL_RenderDrawLineF(renderer, start.x, start.y, end.x, end.y);
        }
    }

    for (const Object2D &obj2D : objs2D) {
        for (const auto &vertex : obj2D.vertices) {
            const Point2D &start = obj2D.points[vertex.start];
            const Point2D &end = obj2D.points[vertex.end];
            SDL_RenderDrawLineF(renderer, start.x, start.y, end.x, end.y);
        }
    }

    SDL_RenderPresent(renderer);
}
