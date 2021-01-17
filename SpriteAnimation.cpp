#include "Sprite.h"
#include "SpriteAnimation.h"
#include "Resources.h"

void SpriteAnimation::AddAnimation(const wchar_t* fileName, GameObject* owner, int delay, DWORD colorKey)
{
    if (HasAnimation(fileName))
    {
        return;
    }

    std::vector<BmpImageData>* sprites = Resources::GetInstance().GetSprites(fileName);

    SpriteAnimationInfo* info = new SpriteAnimationInfo;
    info->currentFrame = 0;
    info->delay = delay;
    //info->animation.reserve(sprites->size());

    for (int i = 0; i < sprites->size(); i++)
    {
        Sprite* sprite = new Sprite((*sprites)[i], owner, colorKey);
        sprite->SetPivot(71, 90);
        info->animation.push_back(sprite);
        //info->animation[i] = sprite;                
    }

    mAnimations.insert(std::make_pair(fileName, info));
}

void SpriteAnimation::Play(std::wstring_view animationName)
{    
    auto iter = mAnimations.find(animationName.data());
    SpriteAnimationInfo* anim = iter->second;
    
    //우선.. Play함수는 프레임마다 실행되니까 상관은 없을거같은데.. 문제는 프레임스킵이다.
    if (mCurrentAnimation == nullptr)
    {
        mCurrentAnimation = anim;
        mCurrentAnimation->currentFrame = 0;
        mCurrentAnimation->currentSprite = mCurrentAnimation->animation[0];
    }

    if (mCurrentAnimation != anim)
    {
        mCurrentAnimation = anim;
        mCurrentAnimation->currentFrame = 0;
        mCurrentAnimation->currentSprite = mCurrentAnimation->animation[0];
    }
        
    if (mCurrentAnimation->delay <= frame)
    {        
        int currentFrame = mCurrentAnimation->currentFrame;        
        if (currentFrame >= mCurrentAnimation->animation.size())
        {            
            ResetFrame();            
        }
        else
        {
            NextFrame(); 
            
        }
        frame = 0;
    }
    
    frame += 1;
}

void SpriteAnimation::NextFrame()
{        
    wchar_t str[32];
    wsprintf(str, L"Current Frame : %d\n", mCurrentAnimation->currentFrame);
    OutputDebugString(str);

    mCurrentAnimation->currentSprite = mCurrentAnimation->animation[mCurrentAnimation->currentFrame];
    mCurrentAnimation->currentFrame += 1;    
}

void SpriteAnimation::ResetFrame()
{        
    mCurrentAnimation->currentSprite = mCurrentAnimation->animation[0];
    mCurrentAnimation->currentFrame = 0;
}

Sprite* SpriteAnimation::GetCurrentSprite()
{
    if(mCurrentAnimation == nullptr)
        return nullptr;

    return mCurrentAnimation->currentSprite;
}

bool SpriteAnimation::HasAnimation(std::wstring_view animationName)
{    
    auto iter = mAnimations.find(animationName.data());
    if (iter != mAnimations.end())
    {
        return true;
    }

    return false;
}