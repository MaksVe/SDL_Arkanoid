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
            // Initialize SDL_font
            if (TTF_Init() == -1)
            {
                std::cout << "SDL_ttf init error: " << TTF_GetError() << std::endl;
                return false;
            }
            else
            {
                // Load font
                font = TTF_OpenFont("Roboto-Black.ttf", 26);
                if (font == nullptr)
                {
                    std::cout << "Unable to load font: " << TTF_GetError() << std::endl;
                    return false;
                }
            }

            return true;
        }
    }
}

void Game::Run()
{
    missCounter = 0;
    
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
    
    for (it = bricks.begin(); it != bricks.end(); ++it)
    {
        delete *it;
    }
    bricks.clear();
    
    ShowStartScreen();
}

void Game::ShowStartScreen()
{
    textColor = {0, 0, 0};
    startTextSurface = TTF_RenderText_Solid(font, "Press SPACE to start", textColor);
    quitTextSurface = TTF_RenderText_Solid(font, "Press Q to quit", textColor);
    
    if (startTextSurface == nullptr || quitTextSurface == nullptr)
    {
        std::cout << "Unable to render text: " << TTF_GetError() << std::endl;
        return;
    }
    else
    {
        startTexture = nullptr;
        quitTexture = nullptr;
        
        startTexture = SDL_CreateTextureFromSurface(renderer, startTextSurface);
        quitTexture = SDL_CreateTextureFromSurface(renderer, quitTextSurface);
        
        if (startTexture == nullptr || quitTexture == nullptr)
        {
            std::cout << "Unable to create texture from rendered text: " << SDL_GetError() << std::endl;
            return;
        }
        else
        {
            startTextureRect.x = (SCREEN_WIDTH / 2) - (startTextSurface->w / 2);
            startTextureRect.y = SCREEN_HEIGHT /2 - startTextSurface->h;
            startTextureRect.h = startTextSurface->h;
            startTextureRect.w = startTextSurface->w;
            
            quitTextureRect.x = (SCREEN_WIDTH / 2) - (quitTextSurface->w / 2);
            quitTextureRect.y = 30 + (SCREEN_HEIGHT / 2 - quitTextSurface->h);
            quitTextureRect.h = quitTextSurface->h;
            quitTextureRect.w = quitTextSurface->w;
            
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);
            SDL_RenderClear(renderer);
            
            SDL_RenderCopy(renderer, startTexture, nullptr, &startTextureRect);
            SDL_RenderCopy(renderer, quitTexture, nullptr, &quitTextureRect);
            
            SDL_RenderPresent(renderer);
            
            SDL_Event e;
            
            while(true)
            {
                if (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)
                    {
                        Close();
                        break;
                    }
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
                    {
                        SDL_DestroyTexture(startTexture);
                        startTexture = nullptr;
                        SDL_FreeSurface(startTextSurface);
                        startTextSurface = nullptr;
                        Run();
                        break;
                    }
                }
            }
        }
    }
}
