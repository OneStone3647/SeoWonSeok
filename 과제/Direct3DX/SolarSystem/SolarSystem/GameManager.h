#pragma once
#include "Vertex.h"
#include "Planet.h"

class GameManager
{
private:
	HWND m_hWnd;
	D3DXMATRIXA16 matWorld;	// 월드 스페이스
	Vertex m_Vertex[9];
	Planet m_Planet;
	POINT m_MousePos;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();
	void Update();

public:
	inline D3DXMATRIXA16* GetmatWorld()
	{
		return &matWorld;
	}

	inline Vertex* GetVertex(int i)
	{
		return &m_Vertex[i];
	}

	inline Planet* GetPlanet()
	{
		return &m_Planet;
	}
};

