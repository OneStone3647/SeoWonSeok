#include "Vertex.h"



Vertex::Vertex()
{
}

Vertex::~Vertex()
{
}

/*=============================================================================
 * 정점 버퍼 초기화
 * 정점 버퍼: 기본적으로 정점 정보를 갖고 있는 메모리 블록
 *
 * 정점 버퍼를 생성하고 정점값을 채워 넣습니다.
 * 정점 버퍼를생성한 다음에는 반드시 Lock()과 Unlock()으로 포인터를 얻어내서
 * 정점 정보를 정점 버퍼에 써넣어야 합니다.
 * 또한 D3D는 인덱스버퍼도 사용 가능하다는 것을 명심합니다.
 * 정점 버퍼나 인덱스 버퍼는 기본 시스템 메모리 외에 디바이스 메모리(비디오카드 메모리)에
 * 생성될수 있는데, 대부분의 비디오카드에서는 이렇게 할 경우 엄청난 속도 향상을 얻을 수 있습니다.
 *=============================================================================*/
HRESULT Vertex::InitVB(LPDIRECT3DDEVICE9 & device, DWORD color)
{
	CUSTOMVERTEX vertices[] =
	{
		{-1, 1, 1, color}, //v0
		{ 1, 1, 1, color}, //v1
		{ 1, 1,-1, color}, //v2
		{-1, 1,-1, color}, //v3

		{-1,-1, 1, color}, //v4
		{ 1,-1, 1, color}, //v5
		{ 1,-1,-1, color}, //v6
		{-1,-1,-1, color}, //v7
	};

	// 정점 버퍼를 생성합니다.
	// 정점 구조체8개를 저장할 메모리를 할당합니다.
	// FVF를 지정하여 보관할 데이터의 형식을 지정합니다.
	if (FAILED(device->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_VB, NULL)))
	{
		return E_FAIL;
	}

	// 정점의 버퍼를 값으로 채웁니다.
	// 정점 버퍼의 Lock() 함수를 호출하여 포인터를 얻어옵니다.
	void* pVertices;

	if (FAILED(m_VB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	// Vertices를 pVertices로 복사합니다.
	memcpy(pVertices, vertices, sizeof(vertices));

	m_VB->Unlock();

	return S_OK;
}
