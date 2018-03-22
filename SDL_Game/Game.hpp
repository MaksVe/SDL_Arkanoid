//
//  Game.hpp
//  SDL_Game
//
//  Created by Максим on 3/20/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include "SDL2/SDL.h"
#include <SDL2_ttf/SDL_ttf.h>

#include "Pad.hpp"
#include "Ball.hpp"
#include "Brick.hpp"

class Game
{
public:
    Game();
    ~Game();
    const static int SCREEN_WIDTH = 400;
    const static int SCREEN_HEIGHT = 600;
    
    const static int BRICK_ROWS = 3;
    const static int BRICK_COLS = 8;
    const static int NUM_OF_BRICKS = BRICK_ROWS * BRICK_COLS;
    
    bool Init();
    void Run();
    
    bool Lost;
    
    void ShowStartScreen();
    
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    
    Pad* pad;
    Ball* ball;
    Brick* brick;
    
    void Update(SDL_Event* e);
    void Draw();
    void Close();
    void Lose();
    
    int missCounter = 0;
    
    std::vector<Brick*> bricks;
    std::vector<Brick*>::iterator it;
    
    SDL_Color textColor;
    SDL_Surface* startTextSurface;
    SDL_Surface* quitTextSurface;
    
    SDL_Texture* startTexture;
    SDL_Texture* quitTexture;
    
    SDL_Rect startTextureRect;
    SDL_Rect quitTextureRect;
};

#endif /* Game_hpp */
