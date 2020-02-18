#include "GameManager.h"



GameManager::GameManager()
{
	m_Title = NULL;
	m_Player = NULL;
}


GameManager::~GameManager()
{
}

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	m_HDC = GetDC(hWnd);

	if (m_Title != NULL)
	{
		delete m_Title;
	}
	m_Title = new Scene;
	m_Title->Init(hWnd);

	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;

	ReleaseDC(hWnd, m_HDC);
}

void GameManager::Update()
{
	m_Title->Update();
}

void GameManager::Release()
{
}

void GameManager::Title()
{
}
