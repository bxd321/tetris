#pragma once
#include "vector"
#include <iostream>
#include "defines.hpp"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>


namespace Graphics {
    bool init();
    void cleanup();
    void preRender();
    void drawBlock(int shape, int x, int y);
    void updateScore(int score);
    void renderScore();
    void present();
    SDL_Renderer* getRenderer();
    TTF_Font* getFont();
    void renderInstructions();

    }
