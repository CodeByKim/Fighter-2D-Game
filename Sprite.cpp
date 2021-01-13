#include "Sprite.h"
#include "Resources.h"

Sprite* Sprite::Create(const wchar_t* fileName, DWORD colorKey)
{	
    BmpImageData data;
    if (!Resources::GetInstance().LoadBmpImage(&data, fileName, 0, 0))
    {
        return nullptr;
    }

    Sprite* sprite = new Sprite(data, colorKey);
    return sprite;
}

Position2D& Sprite::GetPivot()
{
    return mPivot;
}

void Sprite::SetPivot(Position2D pivot)
{
    mPivot = pivot;
}

void Sprite::SetPivot(int x, int y)
{
    mPivot.x = x;
    mPivot.y = y;
}

Sprite::Sprite(BmpImageData data, DWORD colorKey = 0x00ffffff) 
    : mBmpImage(data), mColorKey(colorKey)
{
    mPivot = { 0, 0 };
}

Sprite::~Sprite()
{
    if (!mBmpImage.image)
        delete mBmpImage.image;
}