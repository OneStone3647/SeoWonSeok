#include "BitmapManager.h"

BitmapManager* BitmapManager::m_This = NULL;

BitmapManager::BitmapManager()
{
}

void BitmapManager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);									// DC를 받음
	m_Bitmap = new Bitmap[MAXCARDNUM];						// Bitmap 클래스 배열 동적할당
	for (int i = 0; i < MAXCARDNUM; i++)
	{
		m_Bitmap[i].Init(hdc, hInst, IDB_BITMAP1 + i);		// 각 카드들 초기화
	}
}

void BitmapManager::DrawAll(HDC hdc, int card_X, int card_Y)
{
	int BitmapCount = 0;
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			m_Bitmap[BitmapCount].Draw(hdc, card_X + (m_Bitmap[BitmapCount].GetBitmapSize().cx * x), card_Y + (m_Bitmap[BitmapCount].GetBitmapSize().cy * y));
			BitmapCount++;
		}
	}
}

void BitmapManager::Release()
{
	delete m_This;
}


BitmapManager::~BitmapManager()
{
	delete m_Bitmap;
}
