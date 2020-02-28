#pragma once
#include "Menu.h"
#include "Back.h"
#include "Player.h"

class GameManager
{
private:
	HWND			m_hWnd;
	HDC				m_MemDC;
	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;

	Menu*			m_Menu;
	Back*				m_Back;
	Player*			m_Player;

	float				m_CameraX;
	int					m_FieldIndex;

public:
	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Release();
	void Update();
};

