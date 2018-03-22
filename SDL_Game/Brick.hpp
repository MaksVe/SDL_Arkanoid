//
//  Brick.hpp
//  SDL_Game
//
//  Created by Максим on 3/21/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Brick_hpp
#define Brick_hpp

#include <stdio.h>
#include "SDL2/SDL.h"

typedef enum Color
{
    RED,
    YELLOW,
    BLUE
} Color;

class Brick
{
public:
    const static int BRICK_WIDTH = 50;
    const static int BRICK_HEIGHT = 20;
    
    SDL_Rect rect;
    
    Brick(SDL_Renderer* renderer, int x, int y, Color c);
    ~Brick();
    
    void Destroy();
    void Draw();
    
private:
    SDL_Renderer* renderer;
    
    Color color;
    bool visible;
};

#endif /* Brick_hpp */
