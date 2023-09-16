//
//  Game.cpp
//  GPCpp Ch 2
//
//  Created by Samantha Gatt on 9/9/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#include "Game.hpp"
#include "Actor.hpp"

Game::Game()
    :mIsRunning(false)
    , mUpdatingActors(false)
{ }

bool Game::Initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    
    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
    if (!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }
    
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    mTicksCount = SDL_GetTicks();
    
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
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
    
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::UpdateGame()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    // Change in time (in seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 100.0f;
    mTicksCount = SDL_GetTicks();
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    
    // Update all actors
    mUpdatingActors = true;
    for (Actor* actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;
    
    // Skips updating them this run loop (since it's their first?)
    for (Actor* actor : mPendingActors)
    {
        mActors.emplace_back(actor);
    }
    mPendingActors.clear();
    
    // Temp vector for dead actors (to be deleted next)
    // Even checks if the previously pending actors are dead
    vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }
    // Delete all dead actors
    // Can do a normal for loop because mActors will be modified on ~Actor (not deadActors)
    for (auto actor : deadActors)
    {
        // Removes it from mActors too since we have the custom ~Actor
        delete actor;
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255); // defines color
    SDL_RenderClear(mRenderer); // fills back buffer with defined color
    SDL_RenderPresent(mRenderer); // swaps buffers
}

void Game::AddActor(Actor* actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void removeActor(vector<Actor*>& actors, Actor* actor)
{
    auto iter = std::find(actors.begin(), actors.end(), actor);
    if (iter != actors.end()) {
        // Swaps actor to be removed with the last actor in vector
        // Avoids erase copies (?)
        std::iter_swap(iter, actors.end()-1);
        actors.pop_back();
    }
}

void Game::RemoveActor(Actor* actor)
{
    removeActor(mPendingActors, actor);
    removeActor(mActors, actor);
}

void Game::Shutdown()
{
    while(!mActors.empty())
    {
        delete mActors.back();
    }
}
