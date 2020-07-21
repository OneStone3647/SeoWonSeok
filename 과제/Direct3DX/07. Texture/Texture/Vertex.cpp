#include "Vertex.h"



Vertex::Vertex()
{
}


Vertex::~Vertex()
{
}

/*=============================================================================
 * ���� ���� �ʱ�ȭ
 * ���� ����: �⺻������ ���� ������ ���� �ִ� �޸� ���
 *
 * ���� ���۸� �����ϰ� �������� ä�� �ֽ��ϴ�.
 * ���� ���۸������� �������� �ݵ�� Lock()�� Unlock()���� �����͸� ����
 * ���� ������ ���� ���ۿ� ��־�� �մϴ�.
 * ���� D3D�� �ε������۵� ��� �����ϴٴ� ���� ����մϴ�.
 * ���� ���۳� �ε��� ���۴� �⺻ �ý��� �޸� �ܿ� ����̽� �޸�(����ī�� �޸�)��
 * �����ɼ� �ִµ�, ��κ��� ����ī�忡���� �̷��� �� ��� ��û�� �ӵ� ����� ���� �� �ֽ��ϴ�.
 *=============================================================================*/
HRESULT Vertex::InitVB(LPDIRECT3DDEVICE9 & device)
{
	// �Ǹ����� �׸��� ���� �Ʒ� ���� ���� �׸��� ���� ���۸� �غ��մϴ�.
	// 50 * 2 ��ŭ�� ũ���
	// FVF�� �����Ͽ� ������ �������� ������ �����մϴ�.
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

	// �ﰢ�Լ��� �̿��� �Ʒ��� ���� ������ ���� ���� ������ �����
	// �׸��� D3DPT_TRIANGLESTRIP���� �����ϸ� ������ ���� �� �ֽ��ϴ�.

	// ���� ���ۿ� �� ���� �����͸� ����� �����մϴ�.
	for (DWORD i = 0; i < 50; i++)
	{
		FLOAT theta = (2 * D3DX_PI*i) / (50 - 1);

		pVertices[2 * i + 0].position = D3DXVECTOR3(sinf(theta), -1.0f, cosf(theta));	// �Ǹ����� �Ʒ��� ���� ��ǥ
		pVertices[2 * i + 0].color = 0xffffffff;

#ifndef SHOW_HOW_TO_USE_TCI
		// �ڵ����� ��ǥ�� �������� �ʰ� �����ϴ� ���.
		pVertices[2 * i + 0].tu = ((FLOAT)i) / (50 - 1);
		pVertices[2 * i + 0].tv = 1.0f;

#endif
		pVertices[2 * i + 1].position = D3DXVECTOR3(sinf(theta), 1.0f, cosf(theta));	// �Ǹ����� ���� ���� ��ǥ
		pVertices[2 * i + 1].color = 0xff808080;

#ifndef SHOW_HOW_TO_USE_TCI
		// �ڵ����� ��ǥ�� �������� �ʰ� �����ϴ� ���.
		pVertices[2 * i + 1].tu = ((FLOAT)i) / (50 - 1);
		pVertices[2 * i + 1].tv = 0.0f;

#endif
	}

	m_VB->Unlock();

	return S_OK;
}
