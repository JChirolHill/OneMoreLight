//
//  PlayerMove.hpp
//  Game-mac
//
//  Created by J Hill on 9/19/19.
//  Copyright © 2019 Sanjay Madhav. All rights reserved.
//

#include <string>
#include "MoveComponent.h"
#include "Math.h"

class PlayerMove : public MoveComponent {
public:
    PlayerMove(class Actor* owner);
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    
    void SwitchAnim(std::string animName);
    bool GetMovingRight() { return mMovingRight; }
private:
    float mYSpeed;
    float mForwardSpeed = 500.0f;
    bool mMovingRight = true;
    const float EDGE_OFFSET = 150.0f;
};
