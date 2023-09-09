//
//  Game.cpp
//  SDL Tutorial Game
//
//  Created by Samantha Gatt on 9/5/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#include "Game.hpp"

const int windowWidth = 1024;
const int windowHeight = 768;
const int thickness = 15;
const float paddleH = 100.0f;

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
         windowWidth, // Width of window
         windowHeight, // Height of window
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
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768.0f/2.0f;
    mBallPos.x = 1024.0f/2.0f;
    mBallPos.y = 768.0f/2.0f;
    mPaddleDir = 0;
    mBallVel.x = -200.0f;
    mBallVel.y = 235.0f;
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

void Game::shutdownIfNeeded(const Uint8* keyState)
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
    if (keyState[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::ProcessInput()
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);
    shutdownIfNeeded(keyState);
    
    if (keyState[SDL_SCANCODE_W])
    {
        mPaddleDir -= 1;
    }
    if (keyState[SDL_SCANCODE_S])
    {
        mPaddleDir += 1;
    }
}

void Game::movePaddle(float deltaTime)
{
    if (mPaddleDir != 0)
    {
        // Move paddle 300 pixels per second based on user input
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
        mPaddleDir = 0;
        // Don't let paddle move out of bounds
        float minPaddleY = paddleH/2.0f + static_cast<float>(thickness);
        float maxPaddleY = static_cast<float>(windowHeight - thickness) - paddleH/2.0f;
        if (mPaddlePos.y < minPaddleY)
        {
            mPaddlePos.y = minPaddleY;
        }
        else if (mPaddlePos.y > maxPaddleY)
        {
            mPaddlePos.y = maxPaddleY;
        }
    }
}

void Game::moveBall(float deltaTime) {
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;
    bool didCollideWithTop = mBallPos.y <= static_cast<float>(thickness) && mBallVel.y < 0.0f;
    bool didCollideWithBottom = mBallPos.y >= static_cast<float>(windowHeight - thickness - thickness/2) && mBallVel.y > 0.0f;
    // If the ball collides with the top wall while it's traveling up
    if (didCollideWithTop || didCollideWithBottom)
    {
        // Bounce off 90 degrees
        mBallVel.y *= -1;
    }
    bool didCollideWithRight = mBallPos.x >= static_cast<float>(windowWidth - thickness - thickness/2) && mBallVel.x > 0.0f;
    if (didCollideWithRight)
    {
        mBallVel.x *= -1;
    }
    bool didCollideWithPaddleY = fabs(mPaddlePos.y - mBallPos.y) <= paddleH/2.0f;
    bool didCollideWithPaddleX = mBallPos.x <= mPaddlePos.x + thickness/2 && mBallPos.x >= mPaddlePos.x - thickness/2;
    bool ballIsTravelingToPaddle = mBallVel.x < 0.0f;
    if (didCollideWithPaddleY && didCollideWithPaddleX && ballIsTravelingToPaddle)
    {
        mBallVel.x *= -1;
    }
}

void Game::UpdateGame()
{
    // Frame limiting
    // Make sure 16 miliseconds has passed so updating is smooth
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    // Change in time (in seconds)
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 100.0f;
    mTicksCount = SDL_GetTicks();
    // Clamp max delta time
    // Make sure game time doesn't jump too far forward in a single frame
    // (useful in debugging after stopping at a breakpoint)
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    movePaddle(deltaTime);
    moveBall(deltaTime);
}

void Game::drawWalls()
{
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_Rect wall{
        0,
        0,
        windowWidth,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &wall);
    wall.y = windowHeight - thickness;
    SDL_RenderFillRect(mRenderer, &wall);
    wall.x = windowWidth - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = windowHeight;
    SDL_RenderFillRect(mRenderer, &wall);
}

void Game::drawBall()
{
    SDL_Rect ball{
        static_cast<int>(mBallPos.x - thickness / 2),
        static_cast<int>(mBallPos.y - thickness / 2),
        thickness,
        thickness
    };
    SDL_RenderFillRect(mRenderer, &ball);
}

void Game::drawPaddle()
{
    SDL_Rect paddle{
        static_cast<int>(mPaddlePos.x - thickness/2),
        static_cast<int>(mPaddlePos.y - paddleH/2),
        thickness,
        static_cast<int>(paddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);
}

void Game::GenerateOutput()
{
    // Sets the color to be rendered (on the back buffer)
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    // Fills the back buffer with the set color
    SDL_RenderClear(mRenderer);
    // Draw the game scene (on the back buffer)
    drawWalls();
    drawBall();
    drawPaddle();
    // Swaps back buffer so it's now visible
    SDL_RenderPresent(mRenderer);
}
