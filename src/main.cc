#include "config.h"
#include "init.h"
#include "structs.h"

int main(int argc, char *argv[]) {
    Env cfg;
    newConfig(cfg);

    App app;
    memset(&app, 0, sizeof(App));

    initSDL(cfg, app);

    bool run = true;
    while (run) {
    }

    return 0;
}