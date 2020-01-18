#include "CollisionComponent.h"
#include <algorithm>
#include "Actor.h"
#include "SDL/SDL.h"

CollisionComponent::CollisionComponent(Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
    // get variables to avoid repeatedly fetching
    Vector2 myMin = GetMin();
    Vector2 myMax = GetMax();
    Vector2 otherMin = other->GetMin();
    Vector2 otherMax = other->GetMax();
    
    // check to the left of other, right of other, below other, above other
    return !(myMax.x < otherMin.x || otherMax.x < myMin.x || myMax.y < otherMin.y || otherMax.y < myMin.y);
}

Vector2 CollisionComponent::GetMin() const
{
	return Vector2(mOwner->GetPosition().x - (mWidth * mOwner->GetScale()) / 2.0f,
                   mOwner->GetPosition().y - (mHeight * mOwner->GetScale()) / 2.0f);
}

Vector2 CollisionComponent::GetMax() const
{
    return Vector2(mOwner->GetPosition().x + (mWidth * mOwner->GetScale()) / 2.0f,
                   mOwner->GetPosition().y + (mHeight * mOwner->GetScale()) / 2.0f);
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

// returns if THIS collides on the top/bottom/left/right of OTHER
CollSide CollisionComponent::GetMinOverlap(const CollisionComponent* other, Vector2& offset)
{
    // reset the offset
    offset = Vector2::Zero;
    
    // check if intersect
    if(!Intersect(other)) {
        offset = Vector2::Zero;
        return CollSide::None;
    }
    else {
        // find min difference
        float dy1 = std::abs(other->GetMin().y - GetMax().y);
        float dy2 = std::abs(other->GetMax().y - GetMin().y);
        float dx1 = std::abs(other->GetMin().x - GetMax().x);
        float dx2 = std::abs(other->GetMax().x - GetMin().x);
        float smallest = std::min(dy1, std::min(dy2, std::min(dx1, dx2)));
        
        // return appropriate side
        if(smallest == dy1) {
            offset.y = dy1;
            return CollSide::Top;
        }
        else if(smallest == dy2) {
            offset.y = -dy2;
            return CollSide::Bottom;
        }
        else if(smallest == dx1) {
            offset.x = dx1;
            return CollSide::Left;
        }
        else {
            offset.x = -dx2;
            return CollSide::Right;
        }
    }
    
}
