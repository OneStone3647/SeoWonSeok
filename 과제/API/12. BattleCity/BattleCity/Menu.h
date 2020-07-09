#pragma once
#include "Bitmap.h"

enum SELECTMENU
{
	SELECTMENU_GAMESTART,
	SELECTMENU_EXIT
};

class Menu
{
private:
	HDC				m_MemDC;

	Bitmap			m_Icon[2];
	int					m_IconIndex;

	SELECTMENU	m_Select;
	bool*				m_bGameStartFlag;

	float				m_AnimTime;
	float				m_StartAnimTimer;
	float				m_CurAnimTimer;

public:
	Menu();
	~Menu();

public:
	void Init(HDC MemDC, bool* GameStartFlag);
	void Update();
	void Input();
	void DrawBackGround();
	void DrawMenu();
};

