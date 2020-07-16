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

	// ���� ���۸� �����մϴ�.
	// ���� ����ü8���� ������ �޸𸮸� �Ҵ��մϴ�.
	// FVF�� �����Ͽ� ������ �������� ������ �����մϴ�.
	if (FAILED(device->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_VB, NULL)))
	{
		return E_FAIL;
	}

	// ������ ���۸� ������ ä��ϴ�.
	// ���� ������ Lock() �Լ��� ȣ���Ͽ� �����͸� ���ɴϴ�.
	void* pVertices;

	if (FAILED(m_VB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	// Vertices�� pVertices�� �����մϴ�.
	memcpy(pVertices, vertices, sizeof(vertices));

	m_VB->Unlock();

	return S_OK;
}
