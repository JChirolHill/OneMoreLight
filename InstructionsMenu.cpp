//
//  InstructionsMenu.cpp
//  Game-mac
//
//  Created by J Hill on 1/21/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#include "InstructionsMenu.h"
#include "Game.h"
#include "SpriteComponent.h"

InstructionsMenu::InstructionsMenu(Game* game)
: Actor(game) {
    SetPosition(Vector2(mGame->SCREEN_WIDTH / 2, mGame->SCREEN_HEIGHT));
    mSC = new SpriteComponent(this);
//    mSC->SetTexture(mGame->GetTexture("Assets/Instructions.png"));
}
