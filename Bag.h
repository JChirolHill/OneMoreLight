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
    void SetInterpolateMove(bool interpolate) { this->mInterpolateMove = interpolate; }
private:
    void OnUpdate(float deltaTime) override;
    void CalcBagDirection(class Player* player);
    
    class CollisionComponent* mCC;
    class SpriteComponent* mSC;
    int mNumStars = 0;
    bool mBagChangedToStar = false;
    bool mInterpolateMove = false;
    float mInterpolateTimer = 0.0f;
    float mStartInterpolatePos = -1.0f;
    
    const int BAG_OFFSET_HORIZ = 100.0f;
    const int BAG_OFFSET_VERT = 25.0f;
    const float INTERPOLATE_TIME = 0.25f;
};
