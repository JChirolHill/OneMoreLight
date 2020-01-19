//
//  ProgressBar.hpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

class ProgressBar : public Actor {
public:
    ProgressBar(class Game*);
    void SetProgress(float percent);
private:
    float mPercentDone = 0.0f;
    const float HEIGHT = 324.0f;
    const float OFFSET = 30.0f;
    const float NUM_BITS_IN_BAR = 50.f;
    const float PROGRESS_BIT_HEIGHT = 6.0f;
    
    int mNumBits = 0;
    int mBitsPerStar;
    int mLeftOverBits;
    Vector2 mBitPos;
};
