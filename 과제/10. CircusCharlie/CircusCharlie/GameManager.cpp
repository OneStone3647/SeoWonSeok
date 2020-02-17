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
	HDC hdc = GetDC(hWnd);



	ReleaseDC(hWnd, hdc);
}

void GameManager::Update()
{
}

void GameManager::Release()
{
}

void GameManager::Title()
{
}
