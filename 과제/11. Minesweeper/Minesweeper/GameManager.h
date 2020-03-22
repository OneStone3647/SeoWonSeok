#pragma once
#include "BlockManager.h"
#include "Player.h"

enum DIFFICULTY
{
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD
};

class GameManager
{
private:
	HWND				m_hWnd;
	HDC					m_MemDC;
	HBITMAP				m_NewBitmap;
	HBITMAP				m_OldBitmap;

	DIFFICULTY			m_Difficulty;
	SIZE					m_MapSize;
	SIZE					m_ScreenSize;
	SIZE					m_WindowSize;
	int						m_StartBlockXPos;
	int						m_StartBlockYPos;
	int						m_TimerPosX;
	int						m_TimerPosY;
	int						m_MineCountPosX;
	int						m_MineCountPosY;

	Bitmap				m_Back;
	BlockManager*		m_BlockManager;
	Player*				m_Player;

	int						m_MineCount;

	int						m_Timer;
	float					m_StartTimer;
	float					m_CurTimer;

	bool					m_bIsGameStart;
	bool					m_bIsGameOver;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update(LPARAM lParam);
	void InitBlock();
	DIFFICULTY GetDifficulty()
	{
		return m_Difficulty;
	}
	void SetDifficulty(DIFFICULTY Difficulty);
	void ResetGame();
	void DrawTimer();
	void DrawMineCount();
};

