#pragma once
#include <Windows.h>

enum PLAYERPOISTION
{
	PLAYERPOSITION_DOWN = 0,
	PLAYERPOSITION_UP,
	PLAYERPOSITION_LEFT,
	PLAYERPOSITION_RIGHT
};

class Player
{
private:
	HDC				MemDC;
	HBITMAP			m_NewBitmap;
	HBITMAP			m_OldBitmap;
	SIZE			m_size;

	int				m_X;
	int				m_Y;

	PLAYERPOISTION	m_Position;
	int				m_Frame;

public:
	Player();

	void Init(HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc);
	void Input(HWND hWnd);
	void SetFrame(PLAYERPOISTION position);

	~Player();
};

