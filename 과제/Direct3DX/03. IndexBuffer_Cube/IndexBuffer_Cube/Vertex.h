#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

class Vertex
{
private:
	LPDIRECT3DVERTEXBUFFER9 m_VB = NULL;

public:
	Vertex();
	~Vertex();

public:
	HRESULT InitVB(LPDIRECT3DDEVICE9 &device, float x, float y, float z, float size);

public:
	inline LPDIRECT3DVERTEXBUFFER9 GetVB()
	{
		return m_VB;
	}
};

