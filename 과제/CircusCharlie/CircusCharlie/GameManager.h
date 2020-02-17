#pragma once
#include "Player.h"

#define FPS			60

#define PI			3.141592f



class GameManager
{
private:
	HWND m_hWnd;


public:
	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Update();
	void Release();
	void Title();
};

