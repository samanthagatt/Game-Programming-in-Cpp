//
//  Game.hpp
//  GPCpp Ch 2
//
//  Created by Samantha Gatt on 9/9/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <stdio.h>
#include <vector>
using std::vector;

class Actor;

class Game
{
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
    void AddActor(Actor* actor);
    void RemoveActor(Actor* actor);
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;
    Uint32 mTicksCount;
    bool mUpdatingActors;
    vector<Actor*> mActors;
    vector<Actor*> mPendingActors;
};

#endif /* Game_hpp */
