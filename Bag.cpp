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
#include "AnimatedSprite.h"
#include "Star.h"
#include "PlayerMove.h"
#include "Player.h"
#include "ProgressBar.h"
#include "Loser.h"

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
//            Mix_PlayChannel(-1, GetGame()->GetSound("Assets/Sounds/big_star_high.wav"), 0);
            mNumStars++;
            s->SetState(ActorState::Destroy);
            SDL_Log("Num stars: %d", mNumStars);
            mGame->GetProgressBar()->SetProgress(mNumStars / mGame->STARS_TO_WIN);
        }
    }
    
    // check near enough to Aren for closing animation
    Loser* loser = mGame->GetLoser();
    Player* player = mGame->GetPlayer();
    if(!player->mHug && mGame->mGameOver && player->GetState() != ActorState::Paused && mCC->Intersect(loser->GetComponent<CollisionComponent>())) {
        player->GetComponent<AnimatedSprite>()->SetOnRunOnce([this] {
            Player* player = this->GetGame()->GetPlayer();
            std::string nextAnim = "idleLeft";
            AnimatedSprite* as = player->GetComponent<AnimatedSprite>();
            as->SetAnimation(nextAnim);
            player->SetState(ActorState::Paused);
        });
        loser->SwitchAnim("wake");
    }
    
    // allow final star/bag to move towards loser
    if(mInterpolateMove) {
        // set start pos if first time running interpolation
        if(mStartInterpolatePos < 0.0f) {
            mStartInterpolatePos = GetPosition().x;
        }
        
        // interpolate
        mInterpolateTimer += deltaTime;
        if(mInterpolateTimer < INTERPOLATE_TIME) {
            SetPosition(Vector2(Math::Lerp(mStartInterpolatePos, loser->GetPosition().x, mInterpolateTimer / INTERPOLATE_TIME), GetPosition().y));
        }
        else {
            // stop lerping and hide final star
            mInterpolateMove = false;
            mSC->SetIsVisible(false);
            
            // light up loser
            loser->SwitchAnim("litUp");
        }
    }
}

void Bag::CalcBagDirection(Player* p) {
    if(!mGame->mGameOver && mGame->mStarsDone && !mBagChangedToStar) { // change back to visible once done preparing
        mSC->SetIsVisible(false);
        mBagChangedToStar = true;
    }
    PlayerMove* pm = p->GetComponent<PlayerMove>();
    if(pm->GetMovingRight()) {
        SetPosition(p->GetPosition() + Vector2(BAG_OFFSET_HORIZ, BAG_OFFSET_VERT));
        if(mGame->mGameOver && mBagChangedToStar) { // change bag to star if game over
            mSC->SetTexture(mGame->GetTexture("Assets/FinalStarRight.png"));
        }
        else if(mNumStars > mGame->STARS_TO_WIN - 2) {
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
        if(mGame->mGameOver && mBagChangedToStar) { // change bag to star if game over
            mSC->SetTexture(mGame->GetTexture("Assets/FinalStarLeft.png"));
        }
        else if(mNumStars > mGame->STARS_TO_WIN - 2) {
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
