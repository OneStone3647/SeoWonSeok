#pragma once
#include <d3d9.h>
#include <d3dx9.h>

struct MYINDEX
{
	WORD _0, _1, _2;	// �Ϲ������� �ε����� 16��Ʈ�� ũ�⸦ �����ϴ�.
};

class Cube
{
private:
	LPDIRECT3DINDEXBUFFER9 m_IB = NULL;	// �ε����� ������ �ε��� ����

public:
	Cube();
	~Cube();

public:
	HRESULT InitIB(LPDIRECT3DDEVICE9 &device);

public:
	inline LPDIRECT3DINDEXBUFFER9 GetIB()
	{
		return m_IB;
	}
};

