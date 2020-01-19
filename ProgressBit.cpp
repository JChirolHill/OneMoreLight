//
//  Progress.cpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#include "ProgressBit.h"
#include "Game.h"
#include "SpriteComponent.h"

ProgressBit::ProgressBit(Game* game, Vector2 position, ProgressBitState state)
: Actor(game) {
    SetPosition(position);
    SpriteComponent* sc = new SpriteComponent(this);
    switch (state) {
        case ProgressBitState::Bottom:
            sc->SetTexture(game->GetTexture("Assets/ProgressBottom.png"));
            break;
        case ProgressBitState::Center:
            sc->SetTexture(game->GetTexture("Assets/ProgressCenter.png"));
            break;
        case ProgressBitState::Top:
            sc->SetTexture(game->GetTexture("Assets/ProgressTop.png"));
            break;
    }
}
