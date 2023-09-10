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

struct Vector2
{
    float x;
    float y;
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
    
    Actor(class Game* game);
    virtual ~Actor();
    
    // Called from Game
    void Update(float deltaTime); // no overriding
    void UpdateComponents(float deltaTime); // no overriding
    virtual void UpdateActor(float deltaTime); // to be overriden
    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
    
private:
    State mState;
    /// Center of actor
    Vector2 mPosition;
    float mScale;
    float mRotation;
    vector<class Component*> mComponents;
    class Game* game;
};

#endif /* Actor_hpp */
