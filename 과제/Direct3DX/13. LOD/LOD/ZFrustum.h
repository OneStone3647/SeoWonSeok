#ifndef _ZFRUSTUM_H_
#define _ZFRUSTUM_H_

#include <d3d9.h>
#include <d3dx9.h>

// �������ҿ� ��Ȯ�ϰ� ���Ե��� �ʴ���, �ణ�� ������ �־ �������ҿ� ���Խ�Ű�� ���� ��
#define PLANE_EPSILON	-5.0f

/*=============================================================================*
 * ����ü(��������) �ø��� �ϱ� ���� Ŭ����
 *=============================================================================*/
class ZFrustum
{
private:
	D3DXVECTOR3 m_vtx[8];		// ���������� ������ ���� 8��
	D3DXVECTOR3 m_vPos;		// ���� ī�޶��� ������ǥ
	D3DXPLANE	m_plane[6];		// ���������� �����ϴ� 6���� ���

public:
	ZFrustum();
	~ZFrustum();

public:
	// ī�޶�(view) * ��������(projection, ����)����� �Է� �޾� 6���� ����� ����ϴ�.
	BOOL Make(D3DXMATRIXA16* pmatViewProj);

	// ���� v�� �������� �ȿ� ������ TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�մϴ�.
	BOOL IsIn(D3DXVECTOR3* pv);

	/*=============================================================================*
	 * �߽�(v)�� ������(radius)�� ���� ��豸(bounding sphere)��
	 * �������� �ȿ� ������ TRUE�� ��ȯ, �ƴϸ� FALSE�� ��ȯ�մϴ�.
	 *=============================================================================*/
	BOOL IsInSphere(D3DXVECTOR3* pv, float radius);

	// ���������� ȭ�鿡 �׷��ݴϴ�.
	BOOL Draw(LPDIRECT3DDEVICE9 pDev);

	// ���� ī�޶��� ���� ��ǥ�� ����ݴϴ�.
	D3DXVECTOR3* GetPos()
	{
		return &m_vPos;
	}
};

void ZMakePlane(D3DXPLANE* pPlane, D3DXVECTOR3* pv0, D3DXVECTOR3* pv1, D3DXVECTOR3* pv2);

#endif // _ZFRUSTUM_H_
