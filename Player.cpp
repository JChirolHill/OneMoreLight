//
//  Player.cpp
//  Game-mac
//
//  Created by J Hill on 9/19/19.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "Player.h"
#include "AnimatedSprite.h"
#include "MoveComponent.h"
#include "CollisionComponent.h"
#include "Game.h"
#include "PlayerMove.h"
#include "Bag.h"

Player::Player(Game* game)
: Actor(game) {
    mCollisionComponent = new CollisionComponent(this);
    mCollisionComponent->SetSize(32.0f, 32.0f);
    mPlayerMove = new PlayerMove(this);
    mBag = new Bag(game, this);
    
    mAnimatedSprite = new AnimatedSprite(this);
    std::vector<SDL_Texture*> idleLeftAnim {
        GetGame()->GetTexture("Assets/Lia/IdleLeft.png")
    };
    std::vector<SDL_Texture*> idleRightAnim {
        GetGame()->GetTexture("Assets/Lia/IdleRight.png")
    };
    std::vector<SDL_Texture*> runLAnim {
        GetGame()->GetTexture("Assets/Lia/RunLeft0.png"),
        GetGame()->GetTexture("Assets/Lia/RunLeft1.png"),
        GetGame()->GetTexture("Assets/Lia/RunLeft2.png")
    };
    std::vector<SDL_Texture*> runRAnim {
        GetGame()->GetTexture("Assets/Lia/RunRight0.png"),
        GetGame()->GetTexture("Assets/Lia/RunRight1.png"),
        GetGame()->GetTexture("Assets/Lia/RunRight2.png")
    };
    mAnimatedSprite->AddAnimation("idleLeft", idleLeftAnim);
    mAnimatedSprite->AddAnimation("idleRight", idleRightAnim);
    mAnimatedSprite->AddAnimation("runLeft", runLAnim);
    mAnimatedSprite->AddAnimation("runRight", runRAnim);
    mAnimatedSprite->SetAnimation("idleRight");
}

void Player::OnProcessInput(const Uint8* keyState) {
    
}

void Player::OnUpdate(float deltaTime) {
    
}
