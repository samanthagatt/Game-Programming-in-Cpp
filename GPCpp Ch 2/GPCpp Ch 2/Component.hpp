//
//  Component.hpp
//  GPCpp Ch 2
//
//  Created by Samantha Gatt on 9/9/23.
//  Copyright © 2023 Samantha Gatt. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>

class Component
{
public:
    Component(class Actor* owner, int updateOrder = 100);
    virtual ~Component();
    virtual void Update(float deltaTime);
    int GetUpdateOrder() const { return mUpdateOrder; }
private:
    // inline forward declaration
    class Actor* mOwner;
    // Lower the update order, the earlier the component is updated
    int mUpdateOrder;
};

#endif /* Component_hpp */
