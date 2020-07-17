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
}

void GameManager::Release()
{
	if (m_Cube.GetIB() != NULL)
	{
		m_Cube.GetIB()->Release();
	}

	if (m_Vertex.GetVB() != NULL)
	{
		m_Vertex.GetVB()->Release();
	}
}
