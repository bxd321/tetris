#include "input.hpp"

static const Uint8* keyboardState;
static Uint8* prevKeyboardState;
static int numKeys;

void Input::init() {
    keyboardState = SDL_GetKeyboardState(&numKeys);
    prevKeyboardState = new Uint8[numKeys];
}

void Input::cleanup() {
    delete[] prevKeyboardState;
}

void Input::update() {
    memcpy(prevKeyboardState, keyboardState, numKeys);
}

bool Input::keyDown(SDL_Scancode scancode) {
    return keyboardState[scancode];
}

bool Input::keyPressed(SDL_Scancode scancode) {
    return !prevKeyboardState[scancode] && keyboardState[scancode];
}

bool Input::keyReleased(SDL_Scancode scancode) {
    return prevKeyboardState[scancode] && !keyboardState[scancode];
}