#pragma once
#define LOG(msg)        std::cout << msg << std::endl
#define TEXMAP          "assets/texturemap.png"
#define FONT            "assets/OpenSans-Regular.ttf"
#define ROWS            24
#define COLS            10
#define INVISIBLE_ROWS  3

#define BLOCK_L         32
#define NUM_BLOCKS      4
#define NUM_PIECES      7

#define WIN_X           SDL_WINDOWPOS_CENTERED
#define WIN_Y           SDL_WINDOWPOS_CENTERED
#define WIN_WIDTH       640
#define WIN_HEIGHT      704
#define ROW_TO_Y(r)     ((r - INVISIBLE_ROWS) * BLOCK_L)
#define COL_TO_X(c)     ((1 + c) * BLOCK_L)
#define SCORE_X         WIN_WIDTH - 82 - 96
#define SCORE_Y         64 + 96

#define FPS             60
#define FRAME_TICKS     1000 / FPS
#define KEY_HOLD_DELAY  200


enum Shape {
    I=1, O, T, S, Z, J, L
};
