#pragma once
#include "defines.hpp"
#include "shapegenerator.hpp"
#include <SDL_scancode.h>
#include <SDL_timer.h>

enum Action {
    ACTION_NONE = 0,
    ACTION_ROT_LEFT,
    ACTION_ROT_RIGHT,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_DOWN,
    ACTION_DROP
};

typedef struct _Key {
    SDL_Scancode scancode;
    Action action;
} Key;

class FallingPiece {
public:
    FallingPiece(const int (*board)[COLS]);
    ~FallingPiece();
    void newFallingPiece(int row, int col);
    void render();
    void update();
    bool isLocked() { return locked; }
    int getRow() { return boardRow; }
    int getCol() { return boardCol; }
    const int (&getBlocks())[NUM_BLOCKS][NUM_BLOCKS] { return blockStates[state]; }

private:
    const int (*blockStates)[NUM_BLOCKS][NUM_BLOCKS];
    static const Uint32 ROTATION_DELAY = 200;
    int state = 0;
    const int (*gameBoard)[COLS];
    int boardRow = 0, boardCol = 0;
    ShapeGenerator shapeGen;
    Shape shape, nextShape;
    bool locked = false;
    Uint32 fallDelay = 500;
    Uint32 lastFall = 0;
    const static Uint32 actionDelay = 40;

    const static int frameX = WIN_WIDTH - 178;
    const static int frameY = 96;

    void renderNextPiece();
    void doAction(Action action);
    bool doesFit();
    void autoFall();
    void fall();
    void drop();
    void move(int direction);
    void rotate(int direction);
};
