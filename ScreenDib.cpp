#include "ScreenDIB.h"

ScreenDib::ScreenDib(int width, int height, int colorBit)
{
	memset(&m_stDibInfo, 0, sizeof(BITMAPINFO));
	m_bypBuffer = NULL;
	m_iWidth = 0;
	m_iHeight = 0;
	m_iPitch = 0;
	m_iBufferSize = 0;
	m_iColorBit = 0;
	//------------------------------------------------------------------
	// �������� ���ڷ� ���۸� �����
	//------------------------------------------------------------------
	CreateDibBuffer(width, height, colorBit);
}
ScreenDib::~ScreenDib()
{
	ReleaseDibBuffer();
}
VOID ScreenDib::CreateDibBuffer(int width, int height, int colorBit)
{
	m_iWidth = width;
	m_iHeight = height;
	m_iColorBit = colorBit;
	m_iPitch = ((m_iWidth * (m_iColorBit / 8)) + 3) & ~3;
	m_iBufferSize = m_iPitch * m_iHeight;
	//------------------------------------------------------------------
	// DibInfo ��� ����
	// DIB ��½� ����� ����ϱ� ���� ���̰��� - �� �Է��ϰ� �ִ�.
	//------------------------------------------------------------------
	m_stDibInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_stDibInfo.bmiHeader.biWidth = m_iWidth;
	m_stDibInfo.bmiHeader.biHeight = -m_iHeight;
	m_stDibInfo.bmiHeader.biPlanes = 1;
	m_stDibInfo.bmiHeader.biBitCount = m_iColorBit;
	m_stDibInfo.bmiHeader.biCompression = 0;
	m_stDibInfo.bmiHeader.biSizeImage = m_iBufferSize;
	m_stDibInfo.bmiHeader.biXPelsPerMeter = 0;
	m_stDibInfo.bmiHeader.biYPelsPerMeter = 0;
	m_stDibInfo.bmiHeader.biClrUsed = 0;
	m_stDibInfo.bmiHeader.biClrImportant = 0;
	//------------------------------------------------------------------
	// ���� ����
	//------------------------------------------------------------------
	m_bypBuffer = new BYTE[m_iBufferSize];
	memset(m_bypBuffer, 0xff, m_iBufferSize);
}

VOID ScreenDib::ReleaseDibBuffer()
{
	m_iWidth = 0;
	m_iHeight = 0;
	m_iPitch = 0;
	m_iBufferSize = 0;
	memset(&m_stDibInfo, 0x00, sizeof(BITMAPINFO));
	if (m_bypBuffer != NULL)
		delete[] m_bypBuffer;
	m_bypBuffer = NULL;
}
void ScreenDib::DrawBuffer(HWND hWnd, int x, int y)
{
	if (m_bypBuffer == NULL) return;
	RECT Rect;
	HDC hDC;
	//------------------------------------------------------------------
	// ���� ����� DC �� ��´�.
	//------------------------------------------------------------------
	GetWindowRect(hWnd, &Rect);
	hDC = GetDC(hWnd);
	//------------------------------------------------------------------
	// GDI �Լ��� ����Ͽ� DC�� ����Ѵ�.
	//------------------------------------------------------------------
	int i = SetDIBitsToDevice(hDC, 0, 0, m_iWidth, m_iHeight,
		0, 0, 0, m_iHeight,
		m_bypBuffer, &m_stDibInfo,
		DIB_RGB_COLORS);
	ReleaseDC(hWnd, hDC);
}
BYTE* ScreenDib::GetDibBuffer(void)
{
	return m_bypBuffer;
}
int ScreenDib::GetWidth(void)
{
	return m_iWidth;
}
int ScreenDib::GetHeight(void)
{
	return m_iHeight;
}
int ScreenDib::GetPitch(void)
{
	return m_iPitch;
}