//
//  Ball.hpp
//  SDL_Game
//
//  Created by Максим on 3/20/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Ball
{
public:
    Ball(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~Ball();
    
    void Update(SDL_Event* e);
    void Draw();
    
    void SetDirection();
    
    bool Collides(SDL_Rect& other);
    bool MissedByPlayer = false;
    
    void Reset();
    
private:
    SDL_Renderer* renderer;
    SDL_Event* event;
    SDL_Rect rect;
    
    const static int BALL_WIDTH = 5;
    const static int BALL_HEIGHT = 5;
    //int velocity = 15;
    
    int velocityX;
    int velocityY;
};

#endif /* Ball_hpp */
