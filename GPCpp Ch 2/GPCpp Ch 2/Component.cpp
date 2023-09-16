//
//  Component.cpp
//  GPCpp Ch 2
//
//  Created by Samantha Gatt on 9/9/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int updateOrder)
    :mOwner(owner)
    ,mUpdateOrder(updateOrder)
{
    // Add to actor's vector of components
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
    
}
