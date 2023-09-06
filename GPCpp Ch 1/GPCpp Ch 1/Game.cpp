//
//  Game.cpp
//  SDL Tutorial Game
//
//  Created by Samantha Gatt on 9/5/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#include "Game.hpp"

Game::Game()
:mWindow(nullptr)
,mIsRunning(true)
{
    
}

bool Game::Initialize()
{
    // Initialize SDL
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    // Create SDL Window
    mWindow = SDL_CreateWindow(
         "Game Programming in C++ (Chapter 1)", // Window title
         100, // Top-left x-coordinate of window
         100, // Top-left y-coordinate of window
         1024, // Width of window
         768, // Height of window
         0 // Flags (0 for no flags set)
     );
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    // Create SDL Renderer
    mRenderer = SDL_CreateRenderer(
        mWindow, // Window to create renderer for
        -1, // Which graphics driver to use. Usually -1 (let SDL decide) for a single window
        SDL_RENDERER_ACCELERATED | // Takes advantage of graphics hardware
            SDL_RENDERER_PRESENTVSYNC // Enables vsync
    );
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::RunLoop()
{
    while(mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    if (keyState[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::UpdateGame()
{
    
}

void Game::GenerateOutput()
{
    
}
