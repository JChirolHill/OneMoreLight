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
    cc->SetSize(120.0f, 212.0f);
    
    mAS = new AnimatedSprite(this);
    std::vector<SDL_Texture*> idle {
        GetGame()->GetTexture("Assets/Aren/Idle.png")
    };
    std::vector<SDL_Texture*> wakeAnim {
        GetGame()->GetTexture("Assets/Aren/Wake0.png"),
        GetGame()->GetTexture("Assets/Aren/Wake1.png"),
        GetGame()->GetTexture("Assets/Aren/Wake2.png"),
        GetGame()->GetTexture("Assets/Aren/Wake3.png"),
        GetGame()->GetTexture("Assets/Aren/Wake4.png")
    };
    std::vector<SDL_Texture*> litUpAnim {
        GetGame()->GetTexture("Assets/Aren/Wake5.png")
    };
    mAS->AddAnimation("idle", idle);
    mAS->AddAnimation("wake", wakeAnim);
    mAS->AddAnimation("litUp", litUpAnim);
    mAS->SetAnimation("idle");
}

void Loser::SwitchAnim(std::string animName) {
    mAS->SetAnimation(animName);
    if(animName == "wake") {
        mAS->RunOnce("litUp");
    }
}
