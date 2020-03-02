#pragma once
#include "Menu.h"
#include "Back.h"
#include "Player.h"
#include "End.h"
#include "Object.h"

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
	End*				m_End;
	Enemy*			m_Enemy;

	float				m_CameraX;
	int					m_FieldIndex;

	bool				m_bIsEnd;
	float				m_WinTime;
	float				m_StartWinTimer;
	float				m_CurWinTimer;

public:
	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Release();
	void Update();
};

