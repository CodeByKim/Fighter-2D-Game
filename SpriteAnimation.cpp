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

int frame = 0;
void SpriteAnimation::Play(std::wstring_view animationName)
{
    auto iter = mAnimations.find(animationName.data());
    SpriteAnimationInfo* anim = iter->second;

    //프레임 애니메이션을 돌려야하는데...
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
    
    int currentFrame = mCurrentAnimation->currentFrame;

    /*wchar_t str[32];
    wsprintf(str, L"Current Frame : %d\n", currentFrame);
    OutputDebugString(str);*/

    // 현재 애니메이션의 딜레이가 
    if (mCurrentAnimation->delay >= frame)
    {
        //mCurrentAnimation->currentSprite = mCurrentAnimation->animation[currentFrame];        
        //이게 마지막 프레임인지 체크 필요
        if (mCurrentAnimation->currentFrame >= mCurrentAnimation->animation.size() - 1)
        {
            //mCurrentAnimation->currentFrame = 0;
            ResetFrame();
        }
        else
        {
            NextFrame();
        }

        frame = 0;
    }
    else
    {
        frame += 1;
        //NextFrame();
        //mCurrentAnimation->currentFrame += 1;
    }
}

void SpriteAnimation::NextFrame()
{    
    mCurrentAnimation->currentFrame = mIndex;
    mCurrentAnimation->currentSprite = mCurrentAnimation->animation[mIndex];
    mIndex += 1;
}

void SpriteAnimation::ResetFrame()
{
    mIndex = 0;
    mCurrentAnimation->currentFrame = mIndex;
    mCurrentAnimation->currentSprite = mCurrentAnimation->animation[mIndex];
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