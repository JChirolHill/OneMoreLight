//
//  Star.cpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#include "Star.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "CollisionComponent.h"

Star::Star(Game* game, bool normalStar)
: Actor(game) {
    SetScale(0.1f);
    CollisionComponent* cc = new CollisionComponent(this);
    cc->SetSize(82.0f, 85.0f);
    
    // set sprite image
    if(normalStar) {
        SpriteComponent* sc = new SpriteComponent(this);
        sc->SetTexture(game->GetTexture("Assets/SmallStar.png"));
    }
    else {
        SpriteComponent* sc = new SpriteComponent(this);
        sc->SetTexture(game->GetTexture("Assets/BigStar.png"));
    }
    
    // randomly pick spawn location
    Random* rand = new Random();
    Vector2 spawnPosition = Vector2(rand->GetFloat() * game->GetScreenDimen().x, rand->GetFloat() * game->STAR_LEVEL);
    SetPosition(spawnPosition);
}

Star::~Star() {
    mGame->RemoveStar(this);
}

void Star::OnUpdate(float deltaTime) {
    // rotation
    SetRotation(mRotation + ROTATE_SPEED * deltaTime);
    
    // drop from sky if ripe
    mTimerRipen += deltaTime;
    if(mTimerRipen > TIME_RIPEN) {
        mYSpeed += GetGame()->GRAVITY * deltaTime;
        SetPosition(Vector2(GetPosition().x, GetPosition().y + mYSpeed * deltaTime));
    }
    else { // not ripe, keep growing
        SetScale(mScale + GROW_SPEED * deltaTime);
    }
    
    // destroy when pass the edge of screen
    if(GetPosition().y > GetGame()->SCREEN_HEIGHT) {
        GetGame()->RemoveStar(this);
    }
}
