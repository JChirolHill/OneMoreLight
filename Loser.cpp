//
//  Loser.cpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#include "Loser.h"
#include "Game.h"
#include "CollisionComponent.h"
#include "AnimatedSprite.h"

Loser::Loser(Game* game)
: Actor(game) {
    CollisionComponent* cc = new CollisionComponent(this);
    cc->SetSize(32.0f, 32.0f);
    
    AnimatedSprite* animSprite = new AnimatedSprite(this);
    std::vector<SDL_Texture*> idle {
        GetGame()->GetTexture("Assets/Aren/Idle.png")
    };
    std::vector<SDL_Texture*> wakeAnim {
        GetGame()->GetTexture("Assets/Aren/Wake0.png"),
        GetGame()->GetTexture("Assets/Aren/Wake1.png"),
        GetGame()->GetTexture("Assets/Aren/Wake2.png"),
        GetGame()->GetTexture("Assets/Aren/Wake3.png"),
        GetGame()->GetTexture("Assets/Aren/Wake4.png"),
        GetGame()->GetTexture("Assets/Aren/Wake5.png")
    };
    animSprite->AddAnimation("idle", idle);
    animSprite->AddAnimation("wake", wakeAnim);
    animSprite->SetAnimation("idle");
}
