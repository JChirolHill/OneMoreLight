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

PlayerMove::PlayerMove(Actor* owner)
: MoveComponent(owner) {
    mYSpeed = 0.0f;
}

void PlayerMove::ProcessInput(const Uint8* keyState) {
    // check move left and right
    if(keyState[SDL_SCANCODE_LEFT] && !keyState[SDL_SCANCODE_RIGHT]) {
        SetForwardSpeed(-300.0f);
    }
    else if(!keyState[SDL_SCANCODE_LEFT] && keyState[SDL_SCANCODE_RIGHT]) {
        SetForwardSpeed(300.0f);
    }
    else {
        SetForwardSpeed(0.0f);
    }
}

void PlayerMove::Update(float deltaTime) {
    // update player position
    Vector2 updatedPosition = mOwner->GetPosition() + GetForwardSpeed() * mOwner->GetForward() * deltaTime;
    updatedPosition.y = mOwner->GetPosition().y + mYSpeed * deltaTime;
    if(updatedPosition.x < 0.f) {
        updatedPosition.x = 0.f;
    }
    else if(updatedPosition.x > mOwner->GetGame()->GetScreenDimen().x) {
        updatedPosition.x = mOwner->GetGame()->GetScreenDimen().x;
    }
    mOwner->SetPosition(updatedPosition);
    
    // check win
//    if(mOwner->GetPosition().x > 6368.0f && !mOwner->GetGame()->GetWin()) {
//        mOwner->GetGame()->SetWin();
//        Mix_HaltChannel(mOwner->GetGame()->GetMusicChannel());
//        Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/StageClear.wav"), 0);
//        mOwner->SetState(ActorState::Paused);
//    }
    
    // fix offset if hit blocks
//    CollisionComponent* cc = mOwner->GetComponent<CollisionComponent>();
//    Vector2 offset;
//    bool touchingBlocks = false;
//    for(Block* b : mOwner->GetGame()->mBlocks) {
//        CollSide side = cc->GetMinOverlap(b->mCollisionComponent, offset);
//        if(side != CollSide::None) {
//            touchingBlocks = true;
//            if(side == CollSide::Top && mYSpeed > 0.0f) {
//                mYSpeed = 0.0f;
//                mInAir = false;
//            }
//            if(side == CollSide::Bottom && mYSpeed < 0.0f) {
//                mYSpeed = 0.0f;
//                Mix_PlayChannel(-1, mOwner->GetGame()->GetSound("Assets/Sounds/Bump.wav"), 0);
//            }
//            mOwner->SetPosition(mOwner->GetPosition() - offset);
//        }
//    }
//    mInAir = !touchingBlocks;
    
    // update animation
    std::string animName = mOwner->GetComponent<AnimatedSprite>()->GetAnimName();
    if(animName == "dead") { // dead
        mOwner->SetState(ActorState::Paused);
    }
    else if(GetForwardSpeed() < 0) { // moving left
        SwitchAnim("runLeft");
    }
    else if(GetForwardSpeed() > 0) { // moving right
        SwitchAnim("runRight");
    }
    else { // idle
        SwitchAnim("idle");
    }
}

void PlayerMove::SwitchAnim(std::string animName) {
    mOwner->GetComponent<AnimatedSprite>()->SetAnimation(animName);
}
