//
//  Loser.hpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

class Loser : public Actor {
public:
    Loser(class Game* game);
    ~Loser();
    void SwitchAnim(std::string animName);
private:
    class AnimatedSprite* mAS;
    float mLitUpTimer = 0.0f;
    
    const float LIT_UP_TIME = 0.5f;
    
    void OnUpdate(float deltaTime) override;
};
