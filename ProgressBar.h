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
private:
    float mPercentDone = 0.0f;
    const float HEIGHT = 324.0f;
    const float OFFSET = 30.0f;
};
