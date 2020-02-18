#pragma once
#include "Player.h"
#include "Scene.h"

#define FPS			60

#define PI			3.141592f



class GameManager
{
private:
	HWND		m_hWnd;
	HDC			m_HDC;

	Scene*		m_Title;
	Player*		m_Player;

public:
	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Update();
	void Release();
	void Title();
};

