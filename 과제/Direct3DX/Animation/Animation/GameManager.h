#pragma once
#include "Vertex.h"
#include "Cube.h"

class GameManager
{
private:
	HWND m_hWnd;
	D3DXMATRIXA16 matWorld;	// ���� �����̽�
	Vertex m_Vertex;
	Cube m_Cube;

public:
	GameManager();
	~GameManager();

public:
	void Init(HWND hWnd);
	void Release();

public:
	inline D3DXMATRIXA16* GetmatWorld()
	{
		return &matWorld;
	}

	inline Vertex* GetVertex()
	{
		return &m_Vertex;
	}

	inline Cube* GetCube()
	{
		return &m_Cube;
	}
};

