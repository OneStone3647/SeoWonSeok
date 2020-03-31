#pragma once
#include "Block.h"

class Maptool : public Singleton<Maptool>
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	SIZE			m_ScreenSize;

	vector<vector<Block*>>	m_Block;

	vector<Block*>				m_BlockBitmap;
	int								m_BlockBitmapCount;

	POINT			m_MousePoint;

	BLOCKTYPE	m_CurSelectBlock;

public:
	Maptool();
	~Maptool();

public:
	void Init(HWND hWnd);
	void Release();
	void Update(LPARAM lParam);
	void DrawBackGround();
	void UpdateBlockBitmap(LPARAM lParam);
	bool Input(LPARAM lParam);
};

