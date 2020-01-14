#pragma once
#include "DrawManager.h"
#include "ObjectManager.h"
#include "Snake.h"

enum MAINMENU
{
	MAINMENU_PLAY = 1,
	MAINMENU_END
};

class GameManager
{
private:
	DrawManager m_DrawManager;
	ObjectManager m_ObjectManager;
	Snake* m_Snake;
	int m_Width;
	int m_Height;
	bool bPlayState;
	bool bFirstInput;
	int Score;
	int FoodCount;
	int* FoodCountptr;
public:
	GameManager();
	void MainMenu();
	void Init();
	void Play();
	void GameOver();
	void Input();
	void AddScore();
	~GameManager();
};

