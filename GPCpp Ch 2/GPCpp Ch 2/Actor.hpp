//
//  Actor.hpp
//  GPCpp Ch 2
//
//  Created by Samantha Gatt on 9/9/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <stdio.h>
#include <vector>
using std::vector;

// standard forward declaration
class Game;
class Component;

struct Vector2
{
    float x;
    float y;
    
    Vector2()
        :x(0.0f)
        ,y(0.0f)
    { }
    
    explicit Vector2(float inX, float inY)
        :x(inX)
        ,y(inY)
    { }
};

class Actor
{
public:
    enum State
    {
        EActive,
        EPuased,
        EDead
    };
    
    Actor(Game* game);
    virtual ~Actor();
    
    // Called from Game
    void Update(float deltaTime); // no overriding
    void UpdateComponents(float deltaTime); // no overriding
    // Actor-specific
    virtual void UpdateActor(float deltaTime); // to be overriden
    void AddComponent(Component* component);
    void RemoveComponent(Component* component);
    State GetState();
private:
    State mState;
    /// Center of actor
    Vector2 mPosition;
    float mScale;
    float mRotation;
    vector<Component*> mComponents;
    Game* mGame;
};

#endif /* Actor_hpp */
