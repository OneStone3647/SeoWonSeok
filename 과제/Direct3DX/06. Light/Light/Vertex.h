#pragma once
#include <d3d9.h>
#include <d3dx9.h>

// ����� ���� ����ü�� ���� ������ Ÿ������ FVF��
// D3DFVF_NORMAL: ���� ������ ���� ���͸� �����մϴ�.
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

// ������ ����ϱ� ���ؼ��� ���� ������ ������ �߰� �Ǿ�� �մϴ�.
struct CUSTOMVERTEX
{
	D3DXVECTOR3 position;	// ������ 3���� ��ǥ
	D3DXVECTOR3 normal;		// ������ ���� ����
};

class Vertex
{
private:
	// ������ ������ ���� ����
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

