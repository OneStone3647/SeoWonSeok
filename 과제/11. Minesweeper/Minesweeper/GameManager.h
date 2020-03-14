#pragma once
#include "Block.h"

class GameManager
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	Bitmap		m_Back;

	Block*			m_Block;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();
};

