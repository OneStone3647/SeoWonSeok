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

	// ��� ��Ʈ�� �ʱ�ȭ
	m_Back.Init(m_MemDC, "Bitmap\\back.bmp");

	// BlockManager Ŭ���� ���� �Ҵ�
	if (m_BlockManager != NULL)
	{
		delete m_BlockManager;
	}
	m_BlockManager = new BlockManager;
	m_BlockManager->Init(m_MemDC, m_MapSize.cx, m_MapSize.cy, m_StartBlockXPos, m_StartBlockYPos);

	// Player Ŭ���� ���� �Ҵ�
	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init();
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

	m_Player->Input(lParam);
	m_BlockManager->CheckBlock(m_Player->GetMouseClick(), m_Player->GetMousePoint());
	m_Player->Init();


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
	ResetGame();
	MoveWindow(m_hWnd, 400, 200, m_WindowSize.cx, m_WindowSize.cy, TRUE);
}

void GameManager::ResetGame()
{
	// BlockManager Ŭ���� ���� �Ҵ�
	if (m_BlockManager != NULL)
	{
		delete m_BlockManager;
	}
	m_BlockManager = new BlockManager;
	m_BlockManager->Init(m_MemDC, m_MapSize.cx, m_MapSize.cy, m_StartBlockXPos, m_StartBlockYPos);
}
