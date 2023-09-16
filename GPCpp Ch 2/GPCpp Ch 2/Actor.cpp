//
//  Actor.cpp
//  GPCpp Ch 2
//
//  Created by Samantha Gatt on 9/9/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#include "Actor.hpp"
#include "Component.hpp"
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
    while(!mComponents.empty())
    {
        // As we're looping, `delete`ing the components (`~Component) is also calling Actor::RemoveComponent
        // So the while loop is needed instead of an iterator (since the mComponents array will be changing)
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    for (Component* comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}
void Actor::UpdateActor(float deltaTime)
{
    
}
void Actor::AddComponent(Component* component)
{
    int myOrder = component->GetUpdateOrder();
    // Define this outside for loop scope
    auto iter = mComponents.begin();
    // C++ doen't require anything actually in the setup part
    for (;
        iter != mComponents.end();
        ++iter)
    {
        // Find the insertion point in the sorted vector
        // (The first component with a order higher than the component passed into this function)
        // *iter == getting the reference from the iterator/pointer
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }

    // Inserts element before position of iterator
    mComponents.insert(iter, component);
}
void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}
