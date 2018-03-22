//
//  Game.cpp
//  SDL_Game
//
//  Created by Максим on 3/20/18.
//  Copyright © 2018 Максим. All rights reserved.
//

#include "Game.hpp"

Game::Game()
{
    window = nullptr;
    renderer = nullptr;
    font = nullptr;
    
    Lost = false;
}

Game::~Game()
{}

bool Game::Init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Init error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr)
        {
            std::cout << "Unable to create window: " << SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            // Create renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr)
            {
                std::cout << "Unable to create renderer: " << SDL_GetError() << std::endl;
                return false;
            }
            

            return true;
        }
    }
}

void Game::Run()
{
    pad = new Pad(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    ball = new Ball(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    for (int i = 0; i < BRICK_ROWS; i++)
    {
        for (int j = 0; j < BRICK_COLS; j++)
        {
            bricks.push_back(new Brick(renderer, j * brick->BRICK_WIDTH + j,
                                   i * brick->BRICK_HEIGHT + i, (Color)i));
        }
    }
    
    bool quit = false;
    SDL_Event e;
    
    // main loop
    while(!quit)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                Close();
                quit = true;
            }
        }
        
        Update(&e);
        Draw();
        
        if (missCounter == 3)
        {
            Lose();
            //Close();
            return;
        }
    }
}

void Game::Update(SDL_Event* e)
{
    pad->Update(e);
    ball->Update(e);
    
    if (ball->Collides(pad->rect))
    {
        ball->SetDirection();
    }

    // https://stackoverflow.com/questions/991335/how-to-erase-delete-pointers-to-objects-stored-in-a-vector
    for (it = bricks.begin(); it != bricks.end(); )
    {
        if (ball->Collides((*it)->rect))
        {
            (*it)->Destroy();
            delete *it;
            it = bricks.erase(it);
            ball->SetDirection();
        }
        else
        {
            ++it;
        }
    }
    
    if (ball->MissedByPlayer)
    {
        std::cout << "Missed!" << std::endl;
        SDL_Delay(100);
        missCounter++;
        
        ball->Reset();
    }
}

void Game::Draw()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
    SDL_RenderClear(renderer);
    pad->Draw();
    ball->Draw();
    for (int i = 0; i < NUM_OF_BRICKS; i++)
    {
        bricks[i]->Draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::Close()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

void Game::Lose()
{
    std::cout << "You lost" << std::endl;
    
    pad->Hide();
    delete pad;
    pad = nullptr;
    
    delete ball;
    ball = nullptr;
    
    Lost = true;
}
