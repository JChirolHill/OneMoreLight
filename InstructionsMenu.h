//
//  InstructionsMenu.hpp
//  Game-mac
//
//  Created by J Hill on 1/21/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#pragma once
#include "Actor.h"

class InstructionsMenu : public Actor {
public:
    InstructionsMenu(class Game*);
    void Hide();
private:
    class SpriteComponent* mSC;
};
