#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� ScreenWidth, ���� ScreenHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� ���� �Ѵ�.
	ReleaseDC(hWnd, hdc);

	m_Difficulty = DIFFICULTY_EASY;
	SetDifficulty(m_Difficulty);

	MoveWindow(m_hWnd, 400, 200, m_WindowSize.cx, m_WindowSize.cy, TRUE);

	// ��� ��Ʈ�� �ʱ�ȭ
	m_Back.Init(m_MemDC, "Bitmap\\back.bmp");

	m_bIsGameStart = false;
	m_bIsGameOver = false;

	// BlockManager Ŭ���� ���� �Ҵ�
	if (m_BlockManager != NULL)
	{
		delete m_BlockManager;
	}
	m_BlockManager = new BlockManager;
	m_BlockManager->Init(m_MemDC, m_MapSize.cx, m_MapSize.cy, m_StartBlockXPos, m_StartBlockYPos, m_MineCount);

	// Player Ŭ���� ���� �Ҵ�
	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init();

	m_Timer = 0.0f;
	m_StartTimer = GetTickCount();
	m_CurTimer = 0.0f;
}

void GameManager::Release()
{
	delete m_BlockManager;
	delete m_Player;

	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ����� �� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);
}

void GameManager::Update(LPARAM lParam)
{
	m_Back.Draw(m_MemDC, 0, 0, m_ScreenSize.cx, m_ScreenSize.cy);
	m_BlockManager->DrawAllBlock();

	if (!m_bIsGameOver)
	{
		m_Player->Input(lParam);
		if (m_bIsGameStart)
		{
			m_CurTimer = GetTickCount();
		}
	}
	m_BlockManager->Update(m_Player->GetMouseClick(), m_Player->GetMousePoint(), &m_bIsGameStart, &m_bIsGameOver);
	m_Player->Init();

	if (!m_bIsGameOver && m_CurTimer - m_StartTimer >= 1000.0f)
	{
		m_Timer++;
		m_StartTimer = m_CurTimer;
	}

	DrawTimer();
	DrawMineCount();

	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::InitBlock()
{
}

void GameManager::SetDifficulty(DIFFICULTY Difficulty)
{
	switch (Difficulty)
	{
	case DIFFICULTY_EASY:
		m_Difficulty = DIFFICULTY_EASY;
		m_MapSize.cx = 9;
		m_MapSize.cy = 9;
		m_ScreenSize.cx = ScreenWidthEasy;
		m_ScreenSize.cy = ScreenHeightEasy;
		m_WindowSize.cx = WindowWidthEasy;
		m_WindowSize.cy = WindowHeightEasy;
		m_StartBlockXPos = BlockStartXEasy;
		m_StartBlockYPos = BlockStartYEasy;
		m_MineCount = 10;
		m_TimerPosX = TimerPosXEasy;
		m_TimerPosY = TimerPosYEasy;
		m_MineCountPosX = MineCountPosXEasy;
		m_MineCountPosY = MineCountPosYEasy;
		break;
	case DIFFICULTY_NORMAL:
		m_Difficulty = DIFFICULTY_NORMAL;
		m_MapSize.cx = 16;
		m_MapSize.cy = 16;
		m_ScreenSize.cx = ScreenWidthNormal;
		m_ScreenSize.cy = ScreenHeightNormal;
		m_WindowSize.cx = WindowWidthNormal;
		m_WindowSize.cy = WindowHeightNormal;
		m_StartBlockXPos = BlockStartXNormal;
		m_StartBlockYPos = BlockStartYNormal;
		m_MineCount = 40;
		m_TimerPosX = TimerPosXNormal;
		m_TimerPosY = TimerPosYNormal;
		m_MineCountPosX = MineCountPosXNormal;
		m_MineCountPosY = MineCountPosYNormal;
		break;
	case DIFFICULTY_HARD:
		m_Difficulty = DIFFICULTY_HARD;
		m_MapSize.cx = 30;
		m_MapSize.cy = 16;
		m_ScreenSize.cx = ScreenWidthHard;
		m_ScreenSize.cy = ScreenHeightHard;
		m_WindowSize.cx = WindowWidthHard;
		m_WindowSize.cy = WindowHeightHard;
		m_StartBlockXPos = BlockStartXHard;
		m_StartBlockYPos = BlockStartYHard;
		m_MineCount = 99;
		m_TimerPosX = TimerPosXHard;
		m_TimerPosY = TimerPosYHard;
		m_MineCountPosX = MineCountPosXHard;
		m_MineCountPosY = MineCountPosYHard;
		break;
	}

	// ������ â�� ȭ�� �߾ӿ� �����Ѵ�.
	//int x, y, width, height;
	//RECT rtDesk, rtWindow;
	//GetWindowRect(GetDesktopWindow(), &rtDesk);
	//GetWindowRect(m_hWnd, &rtWindow);
	//width = rtWindow.right - rtWindow.left;
	//height = rtWindow.bottom - rtWindow.top;
	//x = (rtDesk.right - width) / 2;
	//y = (rtDesk.bottom - height) / 2;
}

void GameManager::ResetGame()
{
	// BlockManager Ŭ���� ���� �Ҵ�
	m_BlockManager->Init(m_MemDC, m_MapSize.cx, m_MapSize.cy, m_StartBlockXPos, m_StartBlockYPos, m_MineCount);
	m_Player->Init();

	m_bIsGameStart = false;
	m_bIsGameOver = false;

	m_Timer = 0.0f;
	m_StartTimer = GetTickCount();
	m_CurTimer = 0.0f;

	MoveWindow(m_hWnd, 400, 200, m_WindowSize.cx, m_WindowSize.cy, TRUE);
}

void GameManager::DrawTimer()
{
	TCHAR time[128];
	wsprintf(time, TEXT("%d"), m_Timer);
	TextOut(m_MemDC, m_TimerPosX, m_TimerPosY, time, strlen(time));
}

void GameManager::DrawMineCount()
{
	int tmpMineCount = m_MineCount;
	tmpMineCount -= m_BlockManager->GetFlagCount();

	TCHAR mine[128];
	wsprintf(mine, TEXT("%d"), tmpMineCount);
	TextOut(m_MemDC, m_MineCountPosX, m_MineCountPosY, mine, strlen(mine));
}
