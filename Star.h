//
//  Star.hpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

class Star : public Actor {
public:
    Star(class Game* game, bool normalStar);
private:
    void OnUpdate(float deltaTime) override;
    
    const float TIME_RIPEN = 1.5f;
    const float ROTATE_SPEED = 3.0f;
    const float GROW_SPEED = 0.5f;
    
    float mTimerRipen = 0.0f;
    float mYSpeed = 0.0f;
};
