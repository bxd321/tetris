#include "game.hpp"

int main(void) {
    Game game;

    if (game.init()) {

        game.start();

        while (game.isRunning()) {

            game.handleEvents();
            game.update();
            game.render();
        }
            game.showGameOverScreen();
    }

}
