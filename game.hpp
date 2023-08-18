#pragma once
#include "defines.hpp"
#include "fallingpiece.hpp"

class Game {
public:
    Game();
    ~Game();
    bool init();
    bool loadAssets();
    void showStartScreen();
    void start();
    void handleEvents();
    void update();
    void render();
    bool isRunning() const { return running; }
    void showGameOverScreen();
    void pause() {
    paused = !paused;};
    bool isPaused() {
    return paused;};
    std::vector<int> scoreHistory;
    void displayScoreHistory();

//    void sleep();

private:
    int board[ROWS][COLS] = {0};
    int occupiedBlocks[ROWS] = {0};
    bool running = true;
    bool paused = true;
    int score = 0;
    bool gameDoClearDelay = false;
    FallingPiece fallingPiece;

    void spawnPiece();
    bool placePiece();
    int clearLines();
    void renderBoard();
};

