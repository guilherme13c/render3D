#include "config.h"
#include "init.h"
#include "structs.h"

int main(int argc, char *argv[]) {
    Env cfg;
    newConfig(cfg);

    App app;
    memset(&app, 0, sizeof(App));

    loadObjs(app.objs2D, app.objs3D, argc, argv);

    initSDL(cfg, app);
    main_loop(cfg, app);
    killSDL(app);

    return 0;
}