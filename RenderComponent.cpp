#include "RenderComponent.h"
#include "GameObject.h"
#include "Graphics.h"
#include "IRenderable.h"

RenderComponent::RenderComponent(HWND hWnd, int width, int height, int colorBit)	
{
	mhWnd = hWnd;
	memset(&mDibInfo, 0, sizeof(BITMAPINFO));		
	CreateDibBuffer(width, height, colorBit);
	mDC = GetDC(hWnd);

	mGraphics = new Graphics(mhWnd, screenBuffer);
}

RenderComponent::~RenderComponent()
{
	ReleaseDibBuffer();
}

void RenderComponent::Execute(std::vector<GameObject*>& gameObjects)
{	
	if (screenBuffer.memoryBuffer == nullptr)
		return;

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->OnRender(mGraphics);
	}

	SetDIBitsToDevice(mDC, 0, 0, screenBuffer.screenSize.width, screenBuffer.screenSize.height,
		0, 0, 0, screenBuffer.screenSize.height,
		screenBuffer.memoryBuffer, &mDibInfo,
		DIB_RGB_COLORS);
}

void RenderComponent::CreateDibBuffer(int width, int height, int colorBit)
{	
	screenBuffer.screenSize.width = width;
	screenBuffer.screenSize.height = height;

	screenBuffer.colorBit = colorBit;
	screenBuffer.pitch = ((width * (colorBit / 8)) + 3) & ~3;
	screenBuffer.bufferSize = screenBuffer.pitch * height;

	//------------------------------------------------------------------
	// DibInfo ��� ����
	// DIB ��½� ����� ����ϱ� ���� ���̰��� - �� �Է��ϰ� �ִ�.
	//------------------------------------------------------------------
	mDibInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	mDibInfo.bmiHeader.biWidth = width;
	mDibInfo.bmiHeader.biHeight = -height;
	mDibInfo.bmiHeader.biPlanes = 1;
	mDibInfo.bmiHeader.biBitCount = colorBit;
	mDibInfo.bmiHeader.biCompression = 0;
	mDibInfo.bmiHeader.biSizeImage = screenBuffer.bufferSize;
	mDibInfo.bmiHeader.biXPelsPerMeter = 0;
	mDibInfo.bmiHeader.biYPelsPerMeter = 0;
	mDibInfo.bmiHeader.biClrUsed = 0;
	mDibInfo.bmiHeader.biClrImportant = 0;

	//------------------------------------------------------------------
	// ���� ����
	//------------------------------------------------------------------
	screenBuffer.memoryBuffer = new BYTE[screenBuffer.bufferSize];
	memset(screenBuffer.memoryBuffer, 0xff, screenBuffer.bufferSize);
}

void RenderComponent::ReleaseDibBuffer()
{	
	memset(&mDibInfo, 0x00, sizeof(BITMAPINFO));

	if (screenBuffer.memoryBuffer != nullptr)
		delete[] screenBuffer.memoryBuffer;

	screenBuffer.memoryBuffer = nullptr;
	ReleaseDC(mhWnd, mDC);
}