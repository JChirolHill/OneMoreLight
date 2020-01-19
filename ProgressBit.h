//
//  Progress.hpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

enum class ProgressBitState {
    Bottom,
    Center,
    Top
};

class ProgressBit : public Actor {
public:
    ProgressBit(class Game*, Vector2 position, ProgressBitState state);
private:
};
