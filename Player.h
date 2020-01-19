//
//  Player.hpp
//  Game-mac
//
//  Created by J Hill on 9/19/19.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include "string"
#include "Actor.h"

class Player : public Actor {
public:
    Player(class Game* game);
    bool DidWin(int totalPossible);
    class Bag* GetBag() { return mBag; }
    void PrepareStar();
private:
    class AnimatedSprite* mAnimatedSprite;
    class CollisionComponent* mCollisionComponent;
    class PlayerMove* mPlayerMove;
    class Bag* mBag;
    
    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;
};
