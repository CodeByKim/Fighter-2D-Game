#include "Graphics.h"

//dest�� ��� RenderComponent���� ���;� ��
//void CSpriteDib::DrawSprite(int iSpriteIndex, int iDrawX, int iDrawY, BYTE* bypDest, int iDestWidth,
void Graphics::DrawSprite(Position2D position)
{	
	
}

Graphics::Graphics(HWND hWnd)
{
	m_hWnd = hWnd;
	m_hDC = GetDC(m_hWnd);
}

Graphics::~Graphics()
{
	ReleaseDC(m_hWnd, m_hDC);
}