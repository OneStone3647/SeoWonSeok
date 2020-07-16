#pragma once
#include <d3d9.h>
#include <d3dx9.h>

struct MYINDEX
{
	WORD _0, _1, _2;	// 일반적으로 인덱스는 16비트의 크기를 갖습니다.
};

class Planet
{
private:
	LPDIRECT3DINDEXBUFFER9 m_IB = NULL;	// 인덱스를 저장할 인덱스 버퍼

public:
	Planet();
	~Planet();

public:
	HRESULT InitIB(LPDIRECT3DDEVICE9 &device);

public:
	inline LPDIRECT3DINDEXBUFFER9 GetIB()
	{
		return m_IB;
	}
};

