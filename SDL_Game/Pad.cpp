//
//  Pad.cpp
//  SDL_Game
//
//  Created by Максим on 3/20/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Pad.hpp"

Pad::Pad(SDL_Renderer* r, int screenWidth, int screenHeight)
{
    renderer = r;
    rect.x = (screenWidth / 2) - (PAD_WIDTH / 2);
    rect.y = screenHeight - PAD_HEIGHT;
    rect.w = PAD_WIDTH;
    rect.h = PAD_HEIGHT;
    visible = true;
}

Pad::~Pad()
{}

void Pad::Update(SDL_Event* e)
{
    event = e;
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
            case SDLK_LEFT:
                rect.x -= PAD_VELOCITY;
                if (rect.x < 0)
                {
                    rect.x = 0;
                }
                break;
            case SDLK_RIGHT:
                rect.x += PAD_VELOCITY;
                if (rect.x > 300)
                {
                    rect.x = 300;
                }
                break;
            default:
                break;
        }
    }
}

void Pad::Draw()
{
    if (!visible)
    {
        return;
    }
    
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
}

void Pad::Hide()
{
    visible = false;
}
