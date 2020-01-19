//
//  Bag.cpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#include "Bag.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "Star.h"
#include "PlayerMove.h"
#include "Player.h"

Bag::Bag(Game* game, Player* player)
: Actor(game) {
    mCC = new CollisionComponent(this);
    mCC->SetSize(87.0f, 10.0f);
    mSC = new SpriteComponent(this);
    
    // set texture and position based on direction player facing
    CalcBagDirection(player);
}

void Bag::OnUpdate(float deltaTime) {
    // update direction and offset based on character
    CalcBagDirection(mGame->GetPlayer());
    
    // check if collide with any stars
    for(Star* s : GetGame()->mStars) {
        CollisionComponent* starCC = s->GetComponent<CollisionComponent>();
        if(starCC->Intersect(mCC)) { // caught star
            mNumStars++;
            s->SetState(ActorState::Destroy);
            SDL_Log("Num stars: %d", mNumStars);
        }
    }
}

void Bag::CalcBagDirection(Player* p) {
    PlayerMove* pm = p->GetComponent<PlayerMove>();
    if(pm->GetMovingRight()) {
        SetPosition(p->GetPosition() + Vector2(BAG_OFFSET_HORIZ, BAG_OFFSET_VERT));
        if(mNumStars > mGame->STARS_TO_WIN - 2) {
            mSC->SetTexture(mGame->GetTexture("Assets/BagFilledRight2.png"));
        }
        else if(mNumStars > mGame->STARS_TO_WIN / 2) {
            mSC->SetTexture(mGame->GetTexture("Assets/BagFilledRight1.png"));
        }
        else if(mNumStars > 0) {
            mSC->SetTexture(mGame->GetTexture("Assets/BagFilledRight0.png"));
        }
        else {
            mSC->SetTexture(mGame->GetTexture("Assets/BagEmptyRight.png"));
        }
    }
    else {
        SetPosition(p->GetPosition() + Vector2(-1.f * BAG_OFFSET_HORIZ, BAG_OFFSET_VERT));
        if(mNumStars > mGame->STARS_TO_WIN - 2) {
            mSC->SetTexture(mGame->GetTexture("Assets/BagFilledLeft2.png"));
        }
        else if(mNumStars > mGame->STARS_TO_WIN / 2) {
            mSC->SetTexture(mGame->GetTexture("Assets/BagFilledLeft1.png"));
        }
        else if(mNumStars > 0) {
            mSC->SetTexture(mGame->GetTexture("Assets/BagFilledLeft0.png"));
        }
        else {
            mSC->SetTexture(mGame->GetTexture("Assets/BagEmptyLeft.png"));
        }
    }
}
