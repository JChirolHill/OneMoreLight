//
//  Progress.hpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

class Progress : public Actor {
public:
    Progress(class Game*);
    void SetProgress(float percent);
private:
    class SpriteComponent* mSC;
};
