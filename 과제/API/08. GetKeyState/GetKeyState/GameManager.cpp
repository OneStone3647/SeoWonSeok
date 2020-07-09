#include "GameManager.h"



GameManager::GameManager()
{
}

void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);

	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init(hdc, hInst);

	if (m_Back != NULL)
	{
		delete m_Back;
	}
	m_Back = new Back;
	m_Back->Init(hdc, hInst);
}

void GameManager::Draw(HDC hdc)
{

}


GameManager::~GameManager()
{
}
