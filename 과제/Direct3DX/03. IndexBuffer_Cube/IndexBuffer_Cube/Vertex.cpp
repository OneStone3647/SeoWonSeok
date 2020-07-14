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
HRESULT Vertex::InitVB(LPDIRECT3DDEVICE9 & device, float x, float y, float z, float size)
{
	CUSTOMVERTEX vertices[] = 
	{
		{-size + x, size + y, size + z, 0xffff0000}, //v0
		{ size + x, size + y, size + z, 0xff00ff00}, //v1
		{ size + x, size + y,-size + z, 0xff0000ff}, //v2
		{-size + x, size + y,-size + z, 0xffffff00}, //v3

		{-size + x,-size + y, size + z, 0xffff0000}, //v4
		{ size + x,-size + y, size + z, 0xff00ff00}, //v5
		{ size + x,-size + y,-size + z, 0xff0000ff}, //v6
		{-size + x,-size + y,-size + z, 0xffffff00}, //v7
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
