#pragma once
#include "Board.h"
#include "Player.h"
#include "NetManager.h"
#include "Singleton.h"

class GameManager : public Singleton<GameManager>
{
private:
	HWND		m_hWnd;
	HDC			m_MemDC;
	HBITMAP		m_NewBitmap;
	HBITMAP		m_OldBitmap;

	Board*		m_Board;
	Player*		m_Player;
	Player*		m_Enemy;

	bool			m_bIsStart;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void InitPlayers();
	void Release();
	void Update(LPARAM lParam);
	void EnemyUpdate();
	void DrawAll();
	void Victory(Player* player);
	void Move(Player* player, Player* enemy);
	bool CheckObstacle(POINT currentPoint, POINT goalPoint);
};

