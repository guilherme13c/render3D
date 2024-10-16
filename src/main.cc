#include "config.h"
#include "init.h"
#include "structs.h"

int main(int argc, char *argv[]) {
    Env cfg;
    newConfig(cfg);

    App app;
    newApp(app);

    Object3D cube;

    loadObjs(app.objs2D, app.objs3D, argc, argv);

    initSDL(cfg, app);
    main_loop(cfg, app);
    killSDL(app);

    return 0;
}
