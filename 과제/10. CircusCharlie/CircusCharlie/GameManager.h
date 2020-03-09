#pragma once
#include "Menu.h"
#include "Field.h"
#include "Player.h"
#include "End.h"
#include "Object.h"

class GameManager
{
private:
	HWND				m_hWnd;
	HDC					m_MemDC;
	HBITMAP				m_NewBitmap;
	HBITMAP				m_OldBitmap;

	bool					m_bGameStart;
	bool					m_bWin;
	bool					m_bExit;
	float					m_ExitTime;
	float					m_StartExitTimer;
	float					m_CurExitTimer;
	int						m_Score;

	Menu*				m_Menu;
	Field*					m_Field;
	int						m_FieldIndex;
	Player*				m_Player;
	End*					m_End;
	vector<Front*>		m_Front;
	Front*					m_CurScoreFront;

	float					m_CameraX;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();
	bool CheckCollision(Object* obejct);
	bool CheckScoreCollision(Object* obejct);
};

