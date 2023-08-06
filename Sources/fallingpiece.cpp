#include "defines.hpp"
#include "fallingpiece.hpp"
#include "graphics.hpp"
#include "input.hpp"

const int (*getBlockStates(Shape s))[NUM_BLOCKS][NUM_BLOCKS];

static Key keys[] = {
    {SDL_SCANCODE_A, ACTION_ROT_LEFT},
    {SDL_SCANCODE_D, ACTION_ROT_RIGHT},
    {SDL_SCANCODE_LEFT, ACTION_LEFT},
    {SDL_SCANCODE_RIGHT, ACTION_RIGHT},
    {SDL_SCANCODE_DOWN, ACTION_DOWN},
    {SDL_SCANCODE_SPACE, ACTION_DROP}
};


FallingPiece::FallingPiece(const int (*board)[COLS])
    : gameBoard(board), nextShape(shapeGen.generateNext()) {

}

FallingPiece::~FallingPiece() {}

void FallingPiece::newFallingPiece(int _row, int _col) {
    shape = nextShape;
    nextShape = shapeGen.generateNext();
    blockStates = getBlockStates(shape);
    state = 0;
    boardRow = _row;
    boardCol = _col;
    locked = false;
}

void FallingPiece::render() {
    if (locked)
        return;

    for (int row=0; row<NUM_BLOCKS; row++) {

        for (int col=0; col<NUM_BLOCKS; col++) {

            const int& block = blockStates[state][row][col];
            if (block)
                Graphics::drawBlock(block, COL_TO_X(boardCol + col), ROW_TO_Y(boardRow + row));

        }
    }

    renderNextPiece();
}

void FallingPiece::update() {
    static Uint32 lastActionTime = 0;
    static Uint32 lastPressTime = 0;

    Uint32 time = SDL_GetTicks();

    Action action = ACTION_NONE;

    for (Key& key: keys) {

        if (Input::keyPressed(key.scancode)) {
            action = key.action;
            lastPressTime = time;

        } else if (Input::keyDown(key.scancode)) {

            if (key.action == ACTION_DROP)
                continue;

            if (time - lastPressTime >= KEY_HOLD_DELAY && time - actionDelay >= lastActionTime) {
                lastActionTime = time;
                action = key.action;
            }
        }
    }

    doAction(action);

    autoFall();
}

void FallingPiece::doAction(Action action) {
    static Uint32 lastRotateTime = 0; // Store the last time the rotation key was pressed
    Uint32 currentTime = SDL_GetTicks();

    switch (action) {
    case ACTION_DOWN:
        fall();
        break;
    case ACTION_LEFT:
        move(-1);
        break;
    case ACTION_RIGHT:
        move(1);
        break;
    case ACTION_ROT_LEFT:
        if (currentTime - lastRotateTime >= ROTATION_DELAY) {
            rotate(-1);
            lastRotateTime = currentTime;
        }
        break;
    case ACTION_ROT_RIGHT:
        if (currentTime - lastRotateTime >= ROTATION_DELAY) {
            rotate(1);
            lastRotateTime = currentTime;
        }
        break;
    case ACTION_DROP:
        drop();
        break;
    }
}


void FallingPiece::autoFall() {
    Uint32 elapsed = SDL_GetTicks() - lastFall;

    if (elapsed >= fallDelay && !locked) {

        fall();
    }
}

void FallingPiece::fall() {
    boardRow += 1;
    if (!doesFit()) {
        boardRow -= 1;
        locked = true;
    }

    lastFall = SDL_GetTicks();
}

void FallingPiece::move(int direction) {
    boardCol += direction;
    if (!doesFit()) {
        boardCol -= direction;
    }
}

void FallingPiece::rotate(int direction) {
    int origState = state;

    state += direction;
    if (state == 4)
        state %= 4;
    if (state < 0)
        state = 3;

    if (!doesFit()) {
        state = origState;
    }
}

void FallingPiece::drop() {
    do {
        boardRow++;
    } while (doesFit());
    boardRow--;
    locked = true;
}

bool FallingPiece::doesFit() {
    for (int i=0; i<NUM_BLOCKS; i++) {

        for (int j=0; j<NUM_BLOCKS; j++) {

            if (!blockStates[state][i][j])
                continue;

            int row = boardRow + i;
            int col = boardCol + j;
            if (row >= ROWS || col >= COLS || col < 0 || gameBoard[row][col])
                return false;

        }
    }

    return true;
}

void FallingPiece::renderNextPiece() {

    const int (*nextBlocks)[NUM_BLOCKS][NUM_BLOCKS] = getBlockStates(nextShape);

    for (int row=0; row<NUM_BLOCKS-1; row++) {

        for (int col=0; col<NUM_BLOCKS-1; col++) {

            if (nextBlocks[0][row][col])
                Graphics::drawBlock(nextBlocks[0][row][col], frameX + col * BLOCK_L, frameY + row * BLOCK_L);

        }
    }
}
