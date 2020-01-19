//
//  Progress.cpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#include "Progress.h"
#include "Game.h"
#include "SpriteComponent.h"

Progress::Progress(Game* game)
: Actor(game) {
    mSC = new SpriteComponent(this);
//    mSC->SetTexture(game->GetTexture("Assets/ProgessStrip.png"));
}

void Progress::SetProgress(float percent) {
//    mSC->SetTexture(<#SDL_Texture *texture#>)
}
