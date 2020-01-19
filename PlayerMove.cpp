//
//  PlayerMove.cpp
//  Game-mac
//
//  Created by J Hill on 9/19/19.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "PlayerMove.h"
#include "Actor.h"
#include "SDL/SDL.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Bag.h"

PlayerMove::PlayerMove(Actor* owner)
: MoveComponent(owner) {
    mYSpeed = 0.0f;
}

void PlayerMove::ProcessInput(const Uint8* keyState) {
    // check move left and right
    if(keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT]) {
        SetForwardSpeed(-1.0f * mForwardSpeed);
        mMovingRight = false;
    }
    else if(!keyState[SDL_SCANCODE_LEFT] && keyState[SDL_SCANCODE_RIGHT]) {
        SetForwardSpeed(mForwardSpeed);
        mMovingRight = true;
    }
    else {
        SetForwardSpeed(0.0f);
    }
}

void PlayerMove::Update(float deltaTime) {
    // update player position
    Vector2 updatedPosition = mOwner->GetPosition() + GetForwardSpeed() * mOwner->GetForward() * deltaTime;
    updatedPosition.y = mOwner->GetPosition().y + mYSpeed * deltaTime;
    if(updatedPosition.x < EDGE_OFFSET) {
        updatedPosition.x = EDGE_OFFSET;
    }
    else if(updatedPosition.x > mOwner->GetGame()->GetScreenDimen().x - EDGE_OFFSET) {
        updatedPosition.x = mOwner->GetGame()->GetScreenDimen().x - EDGE_OFFSET;
    }
    mOwner->SetPosition(updatedPosition);
    
    // check win
//    if(mOwner->GetPosition().x > 6368.0f && !mOwner->GetGame()->GetWin()) {
//        mOwner->GetGame()->SetWin();
//        Mix_HaltChannel(mOwner->GetGame()->GetMusicChannel());
//        Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/StageClear.wav"), 0);
//        mOwner->SetState(ActorState::Paused);
//    }
    
    // update animation
    std::string animName = mOwner->GetComponent<AnimatedSprite>()->GetAnimName();
    Game* game = mOwner->GetGame();
    if(!game->mGameOver && game->mStarsDone && !game->mWin) { // lost
        SwitchAnim("sad");
        mOwner->SetState(ActorState::Paused);
    }
    else if(!game->mGameOver && game->mStarsDone && game->mWin) { // won
        if(!mPreparedStar) { // prepare star
            SwitchAnim("prepare");
            mMovingRight = false;
            mOwner->GetComponent<AnimatedSprite>()->RunOnce("idleLeft");
        }
        else {
            // show final star
            ((Player*)mOwner)->GetBag()->GetComponent<SpriteComponent>()->SetIsVisible(true);
            game->mGameOver = true;
//            mOwner->SetState(ActorState::Active);
        }
    }
    else if(GetForwardSpeed() < 0) { // moving left
        SwitchAnim("runLeft");
    }
    else if(GetForwardSpeed() > 0) { // moving right
        SwitchAnim("runRight");
    }
    else { // idle
        if(mMovingRight) {
            SwitchAnim("idleRight");
        }
        else {
            SwitchAnim("idleLeft");
        }
    }
}

void PlayerMove::SwitchAnim(std::string animName) {
    mOwner->GetComponent<AnimatedSprite>()->SetAnimation(animName);
}
