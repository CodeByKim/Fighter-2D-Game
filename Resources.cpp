#include "Resources.h"
#include "BmpImageData.h"

void Resources::LoadSprite(const wchar_t* path, Position2D pivot)
{
	auto spriteIter = mSprites.find(path);
	if (spriteIter != mSprites.end())
	{
		return;
	}

	std::vector<BmpImageData>* sprites = new std::vector<BmpImageData>();
	std::filesystem::path basePath(L"./SpriteData");
	std::filesystem::directory_iterator iter(basePath / path);

	while (iter != std::filesystem::end(iter))
	{
		BmpImageData data;		
		const wchar_t* spritePath = iter->path().c_str();

		if (Resources::GetInstance().LoadBmpImage(&data, spritePath))
		{
			sprites->push_back(data);
			++iter;
		}		
	}

	mSprites.insert(std::make_pair(path, sprites));
}

std::vector<BmpImageData>* Resources::GetSprites(std::wstring_view name)
{
	return mSprites[name.data()];
}

bool Resources::LoadBmpImage(BmpImageData* bmpImage, const wchar_t* fileName)
{
	HANDLE hFile;
	DWORD dwRead;	
	BITMAPFILEHEADER stFileHeader;
	BITMAPINFOHEADER stInfoHeader;
	
	//std::filesystem::path filePath(L"./SpriteData");
	//filePath /= fileName;
	
	if (bmpImage == nullptr)
	{
		return false;
	}

	//���� ����
	hFile = CreateFile(fileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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