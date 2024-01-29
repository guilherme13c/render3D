#include "structs.h"

void newApp(App &app) {
    app.renderer = nullptr;
    app.window = nullptr;
    app.window_surface = nullptr;

    app.objs2D = std::vector<Object2D>(0);
    app.objs3D = std::vector<Object3D>(0);

    app.leftMouseButtonDown = false;
    app.rightMouseButtonDown = false;

    app.initialMouseX = 0.0f;
    app.initialMouseY = 0.0f;

    app.zoomLevel = 100.0f;
}
