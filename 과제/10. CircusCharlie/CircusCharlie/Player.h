#pragma once
#include "Bitmap.h"

class Player
{
private:
	HDC				m_BackDC;
	//HDC				m_MemDC;
	//HBITMAP			m_NewBitmap;
	//HBITMAP			m_OldBitmap;

	Bitmap			m_Player_Idle;
	Bitmap			m_Player_Move1;
	Bitmap			m_Player_Move2;
	Bitmap			m_Player_Win1;
	Bitmap			m_Player_Win2;
	Bitmap			m_Player_Die;

	float			m_Player_X;
	float			m_Player_Y;

public:
	Player();
	~Player();
	
	void Init(HDC BackDC);
	void Update();
};

