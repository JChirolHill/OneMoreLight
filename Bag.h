//
//  Bag.hpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

class Bag : public Actor {
public:
    Bag(class Game* game, class Player* player);
    int GetStars() { return mNumStars; }
private:
    void OnUpdate(float deltaTime) override;
    void CalcBagDirection(class Player* player);
    
    class CollisionComponent* mCC;
    class SpriteComponent* mSC;
    int mNumStars = 0;
    
    const int BAG_OFFSET_HORIZ = 100.0f;
    const int BAG_OFFSET_VERT = 25.0f;
};
