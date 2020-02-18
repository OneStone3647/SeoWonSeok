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
	m_HDC = GetDC(hWnd);

	if (m_Menu != NULL)
	{
		delete m_Menu;
	}
	m_Menu = new Menu;
	m_Menu->Init(hWnd);

	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;

	ReleaseDC(hWnd, m_HDC);
}

void GameManager::Update()
{
	m_Menu->Update();
}

void GameManager::Release()
{
}
