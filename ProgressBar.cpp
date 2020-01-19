//
//  ProgressBar.cpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#include "ProgressBar.h"
#include "Game.h"
#include "SpriteComponent.h"

ProgressBar::ProgressBar(Game* game)
: Actor(game) {
    SetPosition(Vector2(game->SCREEN_WIDTH - OFFSET, HEIGHT / 2));
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/ProgressBar.png"));
}
