#include <cstdio>

#include "Game.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (Game::GetInstance().Create(hInstance, nCmdShow))
    {
        Game::GetInstance().Run();
    }

    Game::GetInstance().Release();    
}

//VOID BitmapDraw(HDC hDC)
//{
//    HANDLE	hFile;
//    DWORD	dwRead;
//    int		iPitch;
//    int		iImageSize;
//    BYTE* bypImage;
//
//    BITMAPFILEHEADER	stFileHeader;
//    BITMAPINFOHEADER	stInfoHeader;
//
//    WCHAR	szFileName[] = L"procademy.bmp";
//
//    FILE* pFile = NULL;
//    _wfopen_s(&pFile, szFileName, L"rb");
//    if (pFile == NULL) return;
//
//    dwRead = fread(&stFileHeader, sizeof(stFileHeader), 1, pFile);
//
//    if (dwRead != 1)
//        MessageBox(NULL, L"파일 헤더읽기 에러", L"dd", MB_OK);
//    dwRead = fread(&stInfoHeader, sizeof(stInfoHeader), 1, pFile);
//    if (dwRead != 1)
//        MessageBox(NULL, L"인포 헤더읽기 에러", L"dd", MB_OK);
//
//    iPitch = ((stInfoHeader.biWidth * (stInfoHeader.biBitCount / 8)) + 3) & ~3;
//    iImageSize = iPitch * stInfoHeader.biHeight;
//
//    bypImage = (BYTE*)malloc(iImageSize);
//    fread(bypImage, iImageSize, 1, pFile);
//    fclose(pFile);
//
//    StretchDIBits(hDC, 0, 0, stInfoHeader.biWidth, stInfoHeader.biHeight, 0, 0,
//        stInfoHeader.biWidth, stInfoHeader.biHeight, bypImage, (BITMAPINFO*)&stInfoHeader, DIB_RGB_COLORS, SRCCOPY);
//
//    free(bypImage);
//}