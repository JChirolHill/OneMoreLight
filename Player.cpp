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

Player::Player(Game* game)
: Actor(game) {
    mCollisionComponent = new CollisionComponent(this);
    mCollisionComponent->SetSize(32.0f, 32.0f);
    mPlayerMove = new PlayerMove(this);
    
    mAnimatedSprite = new AnimatedSprite(this);
    std::vector<SDL_Texture*> idleAnim {
        GetGame()->GetTexture("Assets/Mario/Idle.png")
    };
    std::vector<SDL_Texture*> runLAnim {
        GetGame()->GetTexture("Assets/Mario/RunLeft0.png"),
        GetGame()->GetTexture("Assets/Mario/RunLeft1.png"),
        GetGame()->GetTexture("Assets/Mario/RunLeft2.png")
    };
    std::vector<SDL_Texture*> runRAnim {
        GetGame()->GetTexture("Assets/Mario/RunRight0.png"),
        GetGame()->GetTexture("Assets/Mario/RunRight1.png"),
        GetGame()->GetTexture("Assets/Mario/RunRight2.png")
    };
    mAnimatedSprite->AddAnimation("idle", idleAnim);
    mAnimatedSprite->AddAnimation("runLeft", runLAnim);
    mAnimatedSprite->AddAnimation("runRight", runRAnim);
    mAnimatedSprite->SetAnimation("idle");
}

void Player::OnProcessInput(const Uint8* keyState) {
    
}

void Player::OnUpdate(float deltaTime) {
    
}
