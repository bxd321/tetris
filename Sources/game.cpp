#include "defines.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

Game::Game()
    : fallingPiece(board) {}

Game::~Game() {
    Input::cleanup();
    Graphics::cleanup();
    SDL_Quit();
}
void Game::showStartScreen() {
    SDL_Surface* startScreenImageSurface = IMG_Load("tetris.png");
    if (!startScreenImageSurface) {
        // Handle the error if the image loading fails
        // Example: SDL_Log("Unable to load image: %s\n", IMG_GetError());
        // You may want to return or exit the function or the game here.
    }

    SDL_Texture* startScreenImageTexture = SDL_CreateTextureFromSurface(Graphics::getRenderer(), startScreenImageSurface);
    SDL_FreeSurface(startScreenImageSurface);

    bool started = false;
    while (!started) {
        Graphics::preRender();
        Graphics::drawBlock(1, 100, 100); // Render a block on the screen for demonstration

        // Render the image on the screen
        SDL_RenderCopy(Graphics::getRenderer(), startScreenImageTexture, nullptr, nullptr);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                started = true;
            } else if (event.type == SDL_KEYDOWN) {
                started = true;
            }
        }

        Graphics::renderScore();
        Graphics::present();
        SDL_Delay(10);
    }

    SDL_DestroyTexture(startScreenImageTexture);
}


bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;

    if (!Graphics::init())
        return false;

    Input::init();

    return true;
}

void Game::start() {
    showStartScreen();
    spawnPiece();
    Graphics::updateScore(0);
}

void Game::spawnPiece() {
    fallingPiece.newFallingPiece(INVISIBLE_ROWS - 2, 3);
}

bool Game::placePiece() {
    bool validRow = true;

    int pieceRow = fallingPiece.getRow();
    int pieceCol = fallingPiece.getCol();
    const int (&blocks)[NUM_BLOCKS][NUM_BLOCKS] = fallingPiece.getBlocks();

    for (int row=0; row<NUM_BLOCKS; row++) {

        for (int col=0; col<NUM_BLOCKS; col++) {

            if (blocks[row][col]) {
                board[pieceRow + row][pieceCol + col] = blocks[row][col];
                occupiedBlocks[pieceRow + row]++;
                if (pieceRow + row < INVISIBLE_ROWS)
                    validRow = false;
            }
        }
    }

    return validRow;
}

int Game::clearLines() {
    int clearedLines = 0;
    int lowestCleared = -1;

    for (int row = ROWS-1; row >= 0; row--) {
        if (occupiedBlocks[row] == COLS) {
            clearedLines++;
            if (lowestCleared < 0)
                lowestCleared = row;

        }
    }

    for (int i = lowestCleared; i >= clearedLines; i--) {

        occupiedBlocks[i] = occupiedBlocks[i - clearedLines];
        memcpy(board[i], board[i - clearedLines], COLS * sizeof(int));

        if (i > lowestCleared - clearedLines) {

            for (int col = 0; col < COLS; col++)
                board[i][col] += 10; // Mark line as cleared
        }
    }

    return clearedLines * COLS;
}

void Game::handleEvents() {
    SDL_Event event;

    Input::update();

    while (SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            running = false;
            break;
        }
    }
}

void Game::update() {
    fallingPiece.update();

    if (fallingPiece.isLocked()) {
        if (!placePiece())
            running = false;
        spawnPiece();
        score += clearLines();
    }

}

void Game::render() {
    Graphics::preRender();
    fallingPiece.render();
    renderBoard();

    if (gameDoClearDelay)
        Graphics::updateScore(score);

    Graphics::renderScore();
    Graphics::present();

    SDL_Delay(gameDoClearDelay * 250);
}

//void Game::sleep() {
//    Uint32 ticks = SDL_GetTicks();
//
//    Uint32 deltaTime = SDL_GetTicks() - ticks;
//    if (deltaTime < FRAME_TICKS)
//        SDL_Delay(FRAME_TICKS - deltaTime);
//
//    ticks = SDL_GetTicks();
//}

void Game::renderBoard() {
    bool doClearDelay = false;
    bool flag;

    for (int row=0; row<ROWS; row++) {

        for (int col=0; col<COLS; col++) {

            if (board[row][col]) {
                int shape = board[row][col] < 10 ? board[row][col] : 8;
                Graphics::drawBlock(shape, COL_TO_X(col), ROW_TO_Y(row));

                flag = (board[row][col] >= 10);
                doClearDelay |= flag;
                board[row][col] -= 10 * flag; // Unmark cleared block
            }

        }
    }

    gameDoClearDelay = doClearDelay;
}
void Game::showGameOverScreen() {
    Graphics::preRender();

    // Render the game over text
    SDL_Color textColor = {255, 255, 255};
    std::string gameOverText = "Game Over";
    SDL_Surface* gameOverSurface = TTF_RenderText_Solid(Graphics::getFont(), gameOverText.c_str(), textColor);
    SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(Graphics::getRenderer(), gameOverSurface);

    SDL_Rect textDst = {WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2 - 50, 200, 100};
    SDL_RenderCopy(Graphics::getRenderer(), gameOverTexture, nullptr, &textDst);

    SDL_FreeSurface(gameOverSurface);
    SDL_DestroyTexture(gameOverTexture);

    // Render the final score
    std::string finalScoreText = "Final Score: " + std::to_string(score);
    SDL_Surface* finalScoreSurface = TTF_RenderText_Solid(Graphics::getFont(), finalScoreText.c_str(), textColor);
    SDL_Texture* finalScoreTexture = SDL_CreateTextureFromSurface(Graphics::getRenderer(), finalScoreSurface);

    textDst = {WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2 + 50, 200, 50};
    SDL_RenderCopy(Graphics::getRenderer(), finalScoreTexture, nullptr, &textDst);

    SDL_FreeSurface(finalScoreSurface);
    SDL_DestroyTexture(finalScoreTexture);

    Graphics::renderScore();
    Graphics::present();
    SDL_Delay(5000); // Delay to display the game over screen for 5 seconds before quitting
}
