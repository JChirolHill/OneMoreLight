#include "AnimatedSprite.h"
#include "Actor.h"
#include "Game.h"
#include "PlayerMove.h"

AnimatedSprite::AnimatedSprite(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{
}

void AnimatedSprite::Update(float deltaTime)
{
    if(!mAnims.empty()) {
        if(!mIsPaused) {
            mAnimTimer += mAnimFPS * deltaTime;
            while(mAnimTimer >= mAnims[mAnimName].size()) {
                mAnimTimer -= mAnims[mAnimName].size();
                if(mRunOnce) { // done with one execution
                    mRunOnce = false;
                    SetAnimation(mNextAnim);
                    mNextAnim = "";
                    mOwner->GetComponent<PlayerMove>()->mPreparedStar = true;
                }
            }
        }
        SetTexture(mAnims[mAnimName][(int)mAnimTimer]);
    }
}

void AnimatedSprite::SetAnimation(const std::string& name, bool resetTimer)
{
    SDL_Log("new anim: %s", name.c_str());
	if (mAnimName != name)
	{
		mAnimName = name;
	}
	
	if (resetTimer)
	{
		mAnimTimer = 0.0f;
	}
}

void AnimatedSprite::AddAnimation(const std::string& name,
								  const std::vector<SDL_Texture*>& images)
{
	mAnims.emplace(name, images);
}

void AnimatedSprite::RunOnce(const std::string& nextAnim) {
    mRunOnce = true;
    mNextAnim = nextAnim;
}
