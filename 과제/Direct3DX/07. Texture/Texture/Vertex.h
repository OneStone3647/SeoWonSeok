#pragma once
#include <d3d9.h>
#include <d3dx9.h>

// SHOW_HOW_TO_USE_TCI가 선언된 것과 선언되지 않은 것의 컴파일 결과를 반드시 비교.
//#define SHOW_HOW_TO_USE_TCI

// 사용자 정점 구조체에 관한 정보를 타나내는 FVF값
// D3DFVF_NORMAL: 정점 포맷이 정점 벡터를 포함합니다.
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

struct CUSTOMVERTEX
{
	D3DXVECTOR3	position;	// 정점의 3차원 좌표
	D3DCOLOR	color;
	FLOAT		tu, tv;		// 텍스처 좌표
};

// 사용자 정점 구조체에 관한 정보를 나타내는 FVF 값
#ifdef SHOW_HOW_TO_USE_TCI
// 매크로가 정의되어 있다면 컴파일
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#else
// 매크로가 정의되어 있지 않다면 컴파일
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#endif

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

