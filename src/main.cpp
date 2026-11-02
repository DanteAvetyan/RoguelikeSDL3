
#include "engine/Game.h"

int main() {

    if (!initialize_game()) {
        return 1;
    }

    game_loop();

    shutdown_game();

    return 0;
}
