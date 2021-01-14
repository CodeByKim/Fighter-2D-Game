#include "RenderComponent.h"
#include "GameObject.h"
#include "Graphics.h"
#include "IRenderable.h"

RenderComponent::RenderComponent(int width, int height, int colorBit)
	: mDC(nullptr), 	
	mPitch(0), 
	mColorBit(colorBit), 
	mMemoryBuffer(nullptr), 
	mBufferSize(0)
{
	memset(&mDibInfo, 0, sizeof(BITMAPINFO));
	mScreenSize = { width, height };
	
	CreateDibBuffer(width, height, colorBit);
}

RenderComponent::~RenderComponent()
{
	ReleaseDibBuffer();
}

void RenderComponent::Execute()
{	
	mRenderObject->OnRender(mGraphics);

	if (mMemoryBuffer == nullptr)
		return;
	
	int i = SetDIBitsToDevice(mDC, 0, 0, mScreenSize.width, mScreenSize.height,
		0, 0, 0, mScreenSize.height,
		mMemoryBuffer, &mDibInfo,
		DIB_RGB_COLORS);
}

void RenderComponent::CreateDibBuffer(int width, int height, int colorBit)
{
	mScreenSize.width = width;
	mScreenSize.height = height;
	mColorBit = colorBit;
	mPitch = ((width * (colorBit / 8)) + 3) & ~3;
	mBufferSize = mPitch * height;

	//------------------------------------------------------------------
	// DibInfo 헤더 생성
	// DIB 출력시 뒤집어서 출력하기 위해 높이값을 - 로 입력하고 있다.
	//------------------------------------------------------------------
	mDibInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mDibInfo.bmiHeader.biWidth = width;
	mDibInfo.bmiHeader.biHeight = -height;
	mDibInfo.bmiHeader.biPlanes = 1;
	mDibInfo.bmiHeader.biBitCount = colorBit;
	mDibInfo.bmiHeader.biCompression = 0;
	mDibInfo.bmiHeader.biSizeImage = mBufferSize;
	mDibInfo.bmiHeader.biXPelsPerMeter = 0;
	mDibInfo.bmiHeader.biYPelsPerMeter = 0;
	mDibInfo.bmiHeader.biClrUsed = 0;
	mDibInfo.bmiHeader.biClrImportant = 0;

	//------------------------------------------------------------------
	// 버퍼 생성
	//------------------------------------------------------------------
	mMemoryBuffer = new BYTE[mBufferSize];
	memset(mMemoryBuffer, 0xff, mBufferSize);
}

void RenderComponent::ReleaseDibBuffer()
{
	memset(&mScreenSize, 0, sizeof(ScreenSize));
	mPitch = 0;
	mBufferSize = 0;
	memset(&mDibInfo, 0x00, sizeof(BITMAPINFO));

	if (mMemoryBuffer != nullptr)
		delete[] mMemoryBuffer;

	mMemoryBuffer = nullptr;
}