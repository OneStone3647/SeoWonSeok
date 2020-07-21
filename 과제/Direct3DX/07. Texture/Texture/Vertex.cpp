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
HRESULT Vertex::InitVB(LPDIRECT3DDEVICE9 & device)
{
	// 실린더를 그리기 위해 아래 위의 원을 그리는 정점 버퍼를 준비합니다.
	// 50 * 2 만큼의 크기로
	// FVF를 지정하여 보관할 데이터의 형식을 지정합니다.
	if (FAILED(device->CreateVertexBuffer(50 * 2 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_VB, NULL)))
	{
		return E_FAIL;
	}

	CUSTOMVERTEX* pVertices;

	if (FAILED(m_VB->Lock(0, 0, (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	// 삼각함수를 이용해 아래쪽 원의 정점과 위쪽 원의 정점을 만들고
	// 그릴때 D3DPT_TRIANGLESTRIP으로 연결하면 원통을 만들 수 있습니다.

	// 정점 버퍼에 들어갈 정점 데이터를 만들어 삽입합니다.
	for (DWORD i = 0; i < 50; i++)
	{
		FLOAT theta = (2 * D3DX_PI*i) / (50 - 1);

		pVertices[2 * i + 0].position = D3DXVECTOR3(sinf(theta), -1.0f, cosf(theta));	// 실린더의 아래쪽 원통 좌표
		pVertices[2 * i + 0].color = 0xffffffff;

#ifndef SHOW_HOW_TO_USE_TCI
		// 자동으로 좌표를 생성하지 않고 설정하는 방법.
		pVertices[2 * i + 0].tu = ((FLOAT)i) / (50 - 1);
		pVertices[2 * i + 0].tv = 1.0f;

#endif
		pVertices[2 * i + 1].position = D3DXVECTOR3(sinf(theta), 1.0f, cosf(theta));	// 실린더의 위쪽 원통 좌표
		pVertices[2 * i + 1].color = 0xff808080;

#ifndef SHOW_HOW_TO_USE_TCI
		// 자동으로 좌표를 생성하지 않고 설정하는 방법.
		pVertices[2 * i + 1].tu = ((FLOAT)i) / (50 - 1);
		pVertices[2 * i + 1].tv = 0.0f;

#endif
	}

	m_VB->Unlock();

	return S_OK;
}
