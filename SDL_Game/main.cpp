#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <stdio.h>
#include <iostream>

#include "Game.hpp"

int main(int argc, char* args[])
{
    Game* game = new Game();
    
    if (game->Init())
    {
        game->Run();
    }
    
    return 0;
}
