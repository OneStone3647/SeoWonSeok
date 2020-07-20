#pragma once
#include <d3d9.h>
#include <d3dx9.h>

// 사용자 정점 구조체에 관한 정보를 타나내는 FVF값
// D3DFVF_NORMAL: 정점 포맷이 정점 벡터를 포함합니다.
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

// 광원을 사용하기 위해서는 법선 벡터의 정보가 추가 되어야 합니다.
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;	// 정점의 3차원 좌표
	D3DXVECTOR3 normal;		// 정점의 법선 벡터
};

class Vertex
{
private:
	// 정점을 보관할 정점 버퍼
	LPDIRECT3DVERTEXBUFFER9 m_VB = NULL;

public:
	Vertex();
	~Vertex();

public:
	HRESULT InitVB(LPDIRECT3DDEVICE9 & device);

public:
	inline LPDIRECT3DVERTEXBUFFER9 GetVB()
	{
		return m_VB;
	}
};

