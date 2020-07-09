#pragma once
#include "Player.h"
#include "Back.h"

class GameManager
{
private:
	Player*		m_Player;
	Back*			m_Back;

	HDC			m_MainDC;
	HDC			m_MemDC[3];
	HBITMAP		m_NewBitmap[3];
	HBITMAP		m_OldBitmap[3];

public:
	GameManager();

	void Init(HDC hdc);
	void Draw();

	~GameManager();

	inline Player* GetPlayer()
	{
		return m_Player;
	}
};

