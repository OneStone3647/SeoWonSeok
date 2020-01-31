#pragma once
#include "Bitmap.h"

#define MAXCARDNUM 11

class BitmapManager
{
private:
	static BitmapManager* m_This;
	Bitmap* m_Bitmap;

public:
	static BitmapManager* GetInstance()
	{
		if (m_This == NULL)
		{
			m_This = new BitmapManager;
		}
		return m_This;
	}

public:
	BitmapManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void DrawAll(HDC hdc, int card_X, int card_Y);
	void Release();

	~BitmapManager();
};

