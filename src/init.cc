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

void main_loop(Env &cfg, App &app) {
    bool keep_window_open = true;
    while (keep_window_open) {
        event_loop(keep_window_open, app);
        draw(app.renderer, app.window, app);
    }
}

void event_loop(bool &keep_window_open, App &app) {
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0) {
        switch (e.type) {
        case SDL_QUIT:
            keep_window_open = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT) {
                app.leftMouseButtonDown = true;
                app.initialMouseX = e.button.x;
                app.initialMouseY = e.button.y;
            } else if (e.button.button == SDL_BUTTON_RIGHT) {
                app.rightMouseButtonDown = true;
                app.initialMouseX = e.button.x;
                app.initialMouseY = e.button.y;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT) {
                app.leftMouseButtonDown = false;
            } else if (e.button.button == SDL_BUTTON_RIGHT) {
                app.rightMouseButtonDown = false;
            }
            break;
        case SDL_MOUSEMOTION:
            if (app.leftMouseButtonDown) {
                float rx = (e.motion.y - app.initialMouseY) * 0.01f;
                float ry = (e.motion.x - app.initialMouseX) * 0.01f;
                for (Object3D &obj3D : app.objs3D) {
                    rotate(obj3D, rx, -ry, 0.0f);
                }
            } else if (app.rightMouseButtonDown) {
                float dx = (e.motion.x - app.initialMouseX) * 0.01f;
                float dy = (e.motion.y - app.initialMouseY) * 0.01f;
                for (Object3D &obj3D : app.objs3D) {
                    translate(obj3D, dx, dy, 0.0f);
                }
            }
            app.initialMouseX = e.motion.x;
            app.initialMouseY = e.motion.y;
            break;
        case SDL_MOUSEWHEEL:
            if (e.wheel.y > 0) {
                app.zoomLevel *= 1.1f;
            } else if (e.wheel.y < 0) {
                app.zoomLevel /= 1.1f;
            }
            break;
        }
    }
}

void draw(SDL_Renderer *renderer, SDL_Window *window, App &app) {
    int window_size_x = 0, window_size_y = 0;
    SDL_GetWindowSize(window, &window_size_x, &window_size_y);
    const float centerX = window_size_x / 2.0f, centerY = window_size_y / 2.0f;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (Object3D &obj3D : app.objs3D) {
        Object2D obj2D;
        project3DTo2D(obj3D, obj2D, 5.0f, centerX, centerY, app.zoomLevel);

        for (const Vertex &vertex : obj2D.vertices) {
            const Point2D &start = obj2D.points[vertex.start];
            const Point2D &end = obj2D.points[vertex.end];
            SDL_RenderDrawLineF(renderer, start.x, start.y, end.x, end.y);
        }
    }

    SDL_RenderPresent(renderer);
}
