#pragma once
#include "Block.h"

enum FILEMODE
{
	FILEMODE_IDLE,
	FILEMODE_SAVE,
	FILEMODE_LOAD
};

class Maptool
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

	RECT			m_SaveButton;
	RECT			m_LoadButton;

	FILEMODE	m_CurMode;

	HBRUSH		m_NullBrush;
	HBRUSH		m_WhiteBrush;
	HPEN			m_SelectPen;
	HPEN			m_LinePen;

public:
	Maptool();
	~Maptool();

public:
	void Init(HWND hWnd);
	void Init();
	void Release();
	void Update(LPARAM lParam);
	void DrawBackGround();
	void DrawSelectBlock(LPARAM lParam);
	bool Input(LPARAM lParam);
	void DrawButton(LPARAM lParam);
	void SaveLoad();
};

