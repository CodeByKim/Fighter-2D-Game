#include "Resources.h"
#include "BmpImageData.h"

bool Resources::LoadBmpImage(BmpImageData* bmpImage, const wchar_t* fileName, int iCenterPointX, int iCenterPointY)
{
	HANDLE hFile;
	DWORD dwRead;	
	BITMAPFILEHEADER stFileHeader;
	BITMAPINFOHEADER stInfoHeader;
	
	std::filesystem::path filePath(L"./Textures");
	filePath /= fileName;
	
	if (bmpImage == nullptr)
	{
		return false;
	}

	//���� ����
	hFile = CreateFile(filePath.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	
	ReadFile(hFile, &stFileHeader, sizeof(BITMAPFILEHEADER), &dwRead, NULL);

	if (0x4d42 == stFileHeader.bfType)
	{
		//-----------------------------------------------------------------
		// ��������� �о ���� & 32��Ʈ Ȯ��.
		//-----------------------------------------------------------------
		ReadFile(hFile, &stInfoHeader, sizeof(BITMAPINFOHEADER), &dwRead, NULL);
		if (32 == stInfoHeader.biBitCount)
		{			
			int pitch = (stInfoHeader.biWidth * 4) + 3 & ~3;
			int width = stInfoHeader.biWidth;
			int height = stInfoHeader.biHeight;
						
			bmpImage->pitch = pitch;
			bmpImage->width = width;
			bmpImage->height = height;

			//-----------------------------------------------------------------
			// �̹����� ���� ��ü ũ�⸦ ���ϰ�, �޸� �Ҵ�.
			//-----------------------------------------------------------------
			int imageSize = pitch * height;
			bmpImage->image = new BYTE[imageSize];

			//-----------------------------------------------------------------
			// �̹��� �κ��� ��������Ʈ ���۷� �о�´�.
			// DIB �� �������� �����Ƿ� �̸� �ٽ� ������.
			// �ӽ� ���ۿ� ���� �ڿ� �������鼭 �����Ѵ�.
			//-----------------------------------------------------------------
			BYTE* bypTempBuffer = new BYTE[imageSize];		
			BYTE* bypSpriteTemp = bmpImage->image;
			BYTE* bypTurnTemp;
			ReadFile(hFile, bypTempBuffer, imageSize, &dwRead, NULL);

			//-----------------------------------------------------------------
			// �������� ������.
			//-----------------------------------------------------------------
			bypTurnTemp = bypTempBuffer + pitch * (stInfoHeader.biHeight - 1);
			for (int iCount = 0; iCount < stInfoHeader.biHeight; iCount++)
			{
				memcpy(bypSpriteTemp, bypTurnTemp, pitch);
				bypSpriteTemp += pitch;
				bypTurnTemp -= pitch;
			}

			delete[] bypTempBuffer;			
			CloseHandle(hFile);
			return true;
		}
	}

	CloseHandle(hFile);
	return false;
}

Resources& Resources::GetInstance()
{
	static Resources instance;
	return instance;
}