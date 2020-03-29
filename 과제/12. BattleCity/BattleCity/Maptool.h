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

public:
	Maptool();
	~Maptool();

public:
	void Init();
	void Init(HWND hWnd);
	void Release();
	void Update(LPARAM lParam);
};

