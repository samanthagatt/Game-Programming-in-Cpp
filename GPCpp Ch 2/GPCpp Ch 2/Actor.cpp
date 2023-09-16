//
//  Actor.cpp
//  GPCpp Ch 2
//
//  Created by Samantha Gatt on 9/9/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#include "Actor.hpp"
#include "Game.hpp"

Actor::Actor(Game* game)
    :mState(EActive)
    , mPosition(Vector2())
    , mScale(1.0f)
    , mRotation(0.0f)
    , mGame(game)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
}

void Actor::Update(float deltaTime)
{
    
}

void Actor::UpdateComponents(float deltaTime)
{
    
}
void Actor::UpdateActor(float deltaTime)
{
    
}
void Actor::AddComponent(Component* component)
{
    
}
void Actor::RemoveComponent(Component* component)
{
    
}
Actor::State Actor::GetState()
{
    return mState;
}
