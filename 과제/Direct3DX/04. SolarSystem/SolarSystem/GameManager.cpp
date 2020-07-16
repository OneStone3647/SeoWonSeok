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
	if (m_Planet.GetIB() != NULL)
	{
		m_Planet.GetIB()->Release();
	}

	for (int i = 0; i < sizeof(m_Vertex) / sizeof(Vertex); i++)
	{
		if (m_Vertex[i].GetVB() != NULL)
		{
			m_Vertex[i].GetVB()->Release();
		}
	}
}
