//
//  Ball.cpp
//  SDL_Game
//
//  Created by Максим on 3/20/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Ball.hpp"

Ball::Ball(SDL_Renderer* r, int screenWidth, int screenHeight)
{
    renderer = r;
    rect.x = (screenWidth / 2) - (BALL_WIDTH / 2);
    rect.y = (screenHeight / 2) - (BALL_HEIGHT / 2);
    rect.w = BALL_WIDTH;
    rect.h = BALL_HEIGHT;
    
    velocityX = 1;
    velocityY = 1;
}

Ball::~Ball()
{}

void Ball::Update(SDL_Event *e)
{
    event = e;
    
    // collisions
    rect.y -= velocityY;
    rect.x -= velocityX;
    // top
    if (rect.y <= 0)
    {
        velocityY -= velocity;
    }
    // left
    if (rect.x <= 0)
    {
        velocityX -= velocity;
    }
    // right
    if (rect.x >= 400 - (BALL_WIDTH / 2))
    {
        velocityX += velocity;
    }
    // bottom: reset the ball
    if (rect.y >= 600 - (BALL_HEIGHT / 2))
    {
        MissedByPlayer = true;
        //Reset();
    }
}

void Ball::Draw()
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::SetDirection()
{
    //velocityX = -velocityX;
    velocityY = -velocityY;
}

bool Ball::Collides(SDL_Rect &other)
{
    if ((rect.x < other.x + other.w) &&
        (other.x < rect.x + rect.w) &&
        (rect.y < other.y + other.h) &&
        (other.y < rect.y + rect.h))
        {
            return true;
        }
        
        return false;
}

void Ball::Reset()
{
    rect.x = 200;
    rect.y = 300;
    MissedByPlayer = false;
}


