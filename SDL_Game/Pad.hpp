//
//  Pad.hpp
//  SDL_Game
//
//  Created by Максим on 3/20/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#ifndef Pad_hpp
#define Pad_hpp

#include <stdio.h>
#include "SDL2/SDL.h"

class Pad
{
public:
    Pad(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    ~Pad();
    
    SDL_Rect rect;
    
    void Update(SDL_Event* e);
    void Draw();
    
    void Hide();
    
private:
    SDL_Renderer* renderer;
    SDL_Event* event;
    
    bool visible;
    
    const static int PAD_WIDTH = 100;
    const static int PAD_HEIGHT = 10;
    const static int PAD_VELOCITY = 10;
};

#endif /* Pad_hpp */
