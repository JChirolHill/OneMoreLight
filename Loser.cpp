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
#include "Player.h"
#include "Bag.h"

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
        GetGame()->GetTexture("Assets/Aren/Wake3.png")
    };
    std::vector<SDL_Texture*> waitForLightAnim {
        GetGame()->GetTexture("Assets/Aren/Wake4.png")
    };
    std::vector<SDL_Texture*> litUpAnim {
        GetGame()->GetTexture("Assets/Aren/Wake5.png")
    };
    mAS->AddAnimation("idle", idle);
    mAS->AddAnimation("wake", wakeAnim);
    mAS->AddAnimation("waitForLight", waitForLightAnim);
    mAS->AddAnimation("litUp", litUpAnim);
    mAS->SetAnimation("idle");
}

Loser::~Loser() {
    mGame->SetLoser(nullptr);
}

void Loser::SwitchAnim(std::string animName) {
    mAS->SetAnimation(animName);
    if(animName == "wake") {
        mAS->SetOnRunOnce([this] {
            // change animation to waiting to receive the light
            std::string nextAnim = "waitForLight";
            AnimatedSprite* as = this->GetComponent<AnimatedSprite>();
            as->SetAnimation(nextAnim);
            
            // trigger moving the light to light him up
            this->mGame->GetPlayer()->GetBag()->SetInterpolateMove(true);
        });
    }
}

void Loser::OnUpdate(float deltaTime) {
    // trigger hug once lit up long enough
    if(mAS->GetAnimName() == "litUp") {
        mLitUpTimer += deltaTime;
        if(mLitUpTimer >= LIT_UP_TIME) {
            mAS->SetIsVisible(false);
            
            // set hug animation
            Player* p = mGame->GetPlayer();
            p->SetPosition(GetPosition());
            p->SetState(ActorState::Active);
            p->mHug = true;
            GetGame()->mGameOver = true;
        }
    }
}
