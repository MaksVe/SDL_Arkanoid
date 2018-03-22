//
//  Brick.cpp
//  SDL_Game
//
//  Created by Максим on 3/21/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Brick.hpp"

Brick::Brick(SDL_Renderer* r, int x, int y, Color c)
{
    renderer = r;
    rect.x = x;
    rect.y = y;
    rect.w = BRICK_WIDTH;
    rect.h = BRICK_HEIGHT;
    color = c;
    visible = true;
}

Brick::~Brick()
{}

void Brick::Destroy()
{
    visible = false;
}

void Brick::Draw()
{
    if (!visible)
    {
        return;
    }
    
    switch (color)
    {
        case RED:
            SDL_SetRenderDrawColor(renderer, 255, 51, 51, 255);
            break;
        case YELLOW:
            SDL_SetRenderDrawColor(renderer, 255, 255, 51, 255);
            break;
        case BLUE:
            SDL_SetRenderDrawColor(renderer, 51, 153, 255, 255);
            break;
    }
    
    SDL_RenderFillRect(renderer, &rect);
}
