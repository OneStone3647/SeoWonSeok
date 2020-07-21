#pragma once
#include <d3d9.h>
#include <d3dx9.h>

// SHOW_HOW_TO_USE_TCI�� ����� �Ͱ� ������� ���� ���� ������ ����� �ݵ�� ��.
//#define SHOW_HOW_TO_USE_TCI

// ����� ���� ����ü�� ���� ������ Ÿ������ FVF��
// D3DFVF_NORMAL: ���� ������ ���� ���͸� �����մϴ�.
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL)

struct CUSTOMVERTEX
{
	D3DXVECTOR3	position;	// ������ 3���� ��ǥ
	D3DCOLOR	color;
	FLOAT		tu, tv;		// �ؽ�ó ��ǥ
};

// ����� ���� ����ü�� ���� ������ ��Ÿ���� FVF ��
#ifdef SHOW_HOW_TO_USE_TCI
// ��ũ�ΰ� ���ǵǾ� �ִٸ� ������
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#else
// ��ũ�ΰ� ���ǵǾ� ���� �ʴٸ� ������
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#endif

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

