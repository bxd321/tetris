#pragma once
#include <SDL.h>

namespace Input {
    void init();
    void cleanup();
    void update();
    bool keyDown(SDL_Scancode scancode);
    bool keyPressed(SDL_Scancode scancode);
    bool keyReleased(SDL_Scancode scancode);
};
