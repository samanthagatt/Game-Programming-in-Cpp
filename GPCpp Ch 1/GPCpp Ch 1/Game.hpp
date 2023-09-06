//
//  Game.hpp
//  SDL Tutorial Game
//
//  Created by Samantha Gatt on 9/5/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL2/SDL.h>

class Game
{
public:
    Game();
    // Initialize the Game
    bool Initialize();
    // Runs the game loop until the game is over
    void RunLoop();
    // Shutdown the game
    void Shutdown();
private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    // Window created by SDL
    SDL_Window* mWindow;
    // Game should continue to run
    bool mIsRunning;
    // Game renerer
    SDL_Renderer* mRenderer;
};

#endif /* Game_hpp */
