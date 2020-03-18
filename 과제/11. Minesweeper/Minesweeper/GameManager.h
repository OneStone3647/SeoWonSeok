#pragma once
#include "Block.h"
#include "Singleton.h"

class GameManager : public Singleton<GameManager>
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	Bitmap		m_Back;
	SIZE			m_MapSize;

	Block			m_Block;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update(LPARAM lParam);
	void InitBlock();
};

