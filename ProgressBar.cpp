//
//  ProgressBar.cpp
//  Game-mac
//
//  Created by J Hill on 1/18/20.
//  Copyright © 2020 Sanjay Madhav. All rights reserved.
//

#include "ProgressBar.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "ProgressBit.h"
#include "Player.h"
#include "Bag.h"

ProgressBar::ProgressBar(Game* game)
: Actor(game) {
    SetPosition(Vector2(game->SCREEN_WIDTH - OFFSET, HEIGHT / 2));
    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("Assets/ProgressBar.png"));
    mBitsPerStar = (int)(NUM_BITS_IN_BAR / mGame->STARS_TO_WIN);
    mLeftOverBits = (int)(NUM_BITS_IN_BAR) % mGame->STARS_TO_WIN;
    mBitPos = Vector2(GetPosition().x, HEIGHT - OFFSET);
}

void ProgressBar::SetProgress(float percent) {
    // calc if need extra bits for this star (only first and last star)
    int numExtraBits = 0;
    if(mNumBits == 0 || mNumBits >= NUM_BITS_IN_BAR - mBitsPerStar - mLeftOverBits / 2) {
        if(mLeftOverBits % 2 == 1) { // only account for odd leftover bit once
            numExtraBits += (mLeftOverBits + 1) / 2;
            --mLeftOverBits;
        }
        else {
            numExtraBits += mLeftOverBits / 2;
        }
    }

    // only add new bits if would not spill over the progress bar limit
    if(mNumBits + mBitsPerStar + numExtraBits <= NUM_BITS_IN_BAR) {
        // populate the bits
        for(int i=0; i<mBitsPerStar + numExtraBits; ++i) {
            if(mNumBits == 0) { // first bit
                new ProgressBit(mGame, mBitPos, ProgressBitState::Bottom);
            }
            else if(mNumBits == NUM_BITS_IN_BAR - 1) { // last bit
                new ProgressBit(mGame, mBitPos, ProgressBitState::Top);
            }
            else { // center bit
                new ProgressBit(mGame, mBitPos, ProgressBitState::Center);
            }
            mNumBits++;
            mBitPos -= Vector2(0.0f, PROGRESS_BIT_HEIGHT);
        }
//        SDL_Log("%d more bits, total: %d", mBitsPerStar + numExtraBits, mNumBits);
    }
}
