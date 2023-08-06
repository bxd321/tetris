#include "graphics.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "defines.hpp"

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static SDL_Texture* textureMap = nullptr;
static SDL_Rect bgsrc = {BLOCK_L, 0, WIN_WIDTH, WIN_HEIGHT};
static SDL_Rect blocksrc = {0, 0, BLOCK_L, BLOCK_L};
static SDL_Rect blockdst = {0, 0, BLOCK_L, BLOCK_L};
static TTF_Font* font;
static SDL_Texture* scoreText = nullptr;
bool loadAssets();
void destroyScoreText();

bool Graphics::init() {
    window = SDL_CreateWindow("Tetris", WIN_X, WIN_Y, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!window || !renderer) {
        LOG(SDL_GetError());
        SDL_ClearError();
        return false;
    }

    if (TTF_Init() < 0) {
        LOG(TTF_GetError());
        return false;
    }

    if (!(font = TTF_OpenFont(FONT, 12))) {
        LOG(TTF_GetError());
        return false;
    }

    if (!loadAssets())
        return false;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    return true;
}

bool loadAssets() {
    SDL_Surface* s = nullptr;

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        s = IMG_Load(TEXMAP);

        textureMap = SDL_CreateTextureFromSurface(renderer, s);
    } else
        LOG(IMG_GetError());

    IMG_Quit();

    if (s == nullptr)
        return false;

    SDL_FreeSurface(s);

    return true;

}

void Graphics::cleanup() {
    SDL_DestroyTexture(textureMap);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    destroyScoreText();
    TTF_CloseFont(font);
    TTF_Quit();
}

void Graphics::preRender() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureMap, &bgsrc, nullptr);
}

void Graphics::drawBlock(int shape, int x, int y) {
    blocksrc.y = (shape - 1) * BLOCK_L;
    blockdst.x = x;
    blockdst.y = y;
    SDL_RenderCopy(renderer, textureMap, &blocksrc, &blockdst);
}

void Graphics::updateScore(int score) {
    std::string scoreT = "Score: " + std::to_string(score);

    destroyScoreText();

    SDL_Color textColor = {255, 255, 255};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreT.c_str(), textColor);
    scoreText = SDL_CreateTextureFromSurface(renderer, textSurface);

    SDL_FreeSurface(textSurface);
}

void destroyScoreText() {
    if (scoreText) {
        SDL_DestroyTexture(scoreText);
        scoreText = nullptr;
    }
}

void Graphics::renderScore() {
    SDL_Rect textDst = {SCORE_X, SCORE_Y, 96, 48};
    SDL_RenderCopy(renderer, scoreText, nullptr, &textDst);
}

void Graphics::present() {
    SDL_RenderPresent(renderer);
}
SDL_Renderer* Graphics::getRenderer() {
    return renderer;
}
TTF_Font* Graphics::getFont() {
    return font;
}
