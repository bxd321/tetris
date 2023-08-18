#include "game.hpp"

int main(int argc, char* argv[]) {
    Game game;

    if (game.init()) {
        game.showStartScreen();

        while (game.isRunning()) {
            game.handleEvents();

            if (!game.isPaused()) {
                game.update();
                game.render();
            }
        }

        game.showGameOverScreen();
    }

    return 0;
}
