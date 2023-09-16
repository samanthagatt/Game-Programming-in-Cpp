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
    return true;
}

void Game::ProcessInput()
{
    
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
    
    for (Actor* actor : mPendingActors)
    {
        mActors.emplace_back(actor);
    }
    mPendingActors.clear();
    
    // Temp vector for dead actors (to be deleted next)
    vector<Actor*> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }
    // Delete all dead actors
    for (auto actor : deadActors)
    {
        // Removes it from mActors too since we have the custom ~Actor
        delete actor;
    }
}

void Game::GenerateOutput()
{
    
}

void Game::RunLoop()
{
    ProcessInput();
    UpdateGame();
    GenerateOutput();
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

void removeActor(vector<Actor*>& actors, Actor *actor)
{
    auto iter = std::find(actors.begin(), actors.end(), actor);
    if (iter != actors.end()) {
        // Swaps actor to be removed with the last actor in vector
        // Avoids erase copies (?)
        std::iter_swap(iter, actors.end()-1);
        actors.pop_back();
    }
}

void Game::RemoveActor(Actor *actor)
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
