#include "config.h"
#include "init.h"
#include "structs.h"

int main(int argc, char *argv[]) {
    Env cfg;
    newConfig(cfg);

    App app;
    memset(&app, 0, sizeof(App));

    std::vector<Object3D> objs3D;
    std::vector<Object2D> objs2D;

    loadObjs(objs2D, objs3D, argc, argv);

    initSDL(cfg, app);
    main_loop(cfg, app, objs3D, objs2D);
    killSDL(app);

    return 0;
}