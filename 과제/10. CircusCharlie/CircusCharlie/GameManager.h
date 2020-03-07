#pragma once
#include "Menu.h"
#include "Field.h"
#include "Player.h"
#include "End.h"

class GameManager
{
private:
	HWND			m_hWnd;
	HDC				m_MemDC;
	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;

	bool				m_bGameStart;
	bool				m_bWin;
	float				m_ExitTime;
	float				m_StartExitTimer;
	float				m_CurExitTimer;

	Menu*			m_Menu;
	Field*				m_Field;
	int					m_FieldIndex;
	Player*			m_Player;
	End*				m_End;

	float				m_CameraX;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();
};

