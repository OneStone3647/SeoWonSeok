#include "Cube.h"



Cube::Cube()
{
}


Cube::~Cube()
{
}

/*=============================================================================
 * 인덱스 버퍼 설정
 *=============================================================================*/
HRESULT Cube::InitIB(LPDIRECT3DDEVICE9 & device)
{
	MYINDEX indices[] =
	{
		{0, 1, 2}, {0, 2, 3}, // 윗면
		{4, 6, 5}, {4, 7, 6}, // 아랫면
		{0, 3, 7}, {0, 7, 4}, // 왼면
		{1, 5, 6}, {1, 6, 2}, // 오른면
		{3, 2, 6}, {3, 6, 7}, // 앞면
		{0, 4, 5}, {0, 5, 1}, // 뒷면
	};

	// 인덱스 버퍼 생성
	// D3DFMT_INDEX16은 인덱스의 단위가 16비트라는 것을 나타냅니다.
	// MYINDEX 구조체에서 WORD형으로 선언했으므로 D3DFMT_INDEX16을 사용합니다.
	// DWORD형일 경우 D3DFMT_INDEX32를 사용합니다.
	if (FAILED(device->CreateIndexBuffer(12 * sizeof(MYINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_IB, NULL)))
	{
		return E_FAIL;
	}

	// 인덱스 버퍼를 값으로 채운다.
	void* pIndices;
	// 인덱스 버퍼의 Lock() 함수를 호출하여 포인터를 얻어와서 정보를 채웁니다.
	if (FAILED(m_IB->Lock(0, sizeof(indices), (void**)&pIndices, 0)))
	{
		return E_FAIL;
	}

	memcpy(pIndices, indices, sizeof(indices));

	m_IB->Unlock();

	return S_OK;
}
