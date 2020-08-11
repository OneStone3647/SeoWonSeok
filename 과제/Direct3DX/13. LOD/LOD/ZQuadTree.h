#ifndef _ZQUADTREE_H_
#define _ZQUADTREE_H_

#include "define.h"
#include "ZFrustum.h"
#include "ZFLog.h"

/*===================================================================================*
 * QuadTree�� ���̽� Ŭ����
 *===================================================================================*/
class ZQuadTree
{
private:
	// QuadTree�� �����Ǵ� 4���� �ڳ� ���� ���� ��� ��
	enum CornerType
	{
		CORNER_TL,
		CORNER_TR,
		CORNER_BL,
		CORNER_BR
	};

	// QuadTree��  Frustum���� ����
	enum QuadLocation
	{
		FRUSTUM_OUT = 0,					// Frustum���� ���� ���
		FRUSTUM_PARTIALLY_IN = 1,		// Frustum�� �κ� ����
		FRUSTUM_COMPLETELY_IN = 2,	// Frustum�� ���� ����
		FRUSTUM_UNKNOWN = -1		// �� �� ����
	};

private:
	ZQuadTree*		m_pChild[4];		// QuadTree�� 4���� �ڽ� ���

	int					m_nCenter;		// QuadTree�� ������ ù��° ��
	int					m_nCorner[4];	// QuadTree�� ������ �ι�° ��
											//    TopLeft(TL)      TopRight(TR)
											//              0------1
											//              |      |
											//              |      |
											//              2------3
											// BottomLeft(BL)      BottomRight(BR)

	BOOL				m_bCulled;		// Frustum���� �ø��� ����ΰ�?
	float				m_fRadius;		// ��带 ���δ� ��豸(bounding sphere)�� ������

public:
	// ���� ��Ʈ ��� ������
	ZQuadTree(int cx, int cy);

	// ���� �ڽ� ��� ������
	ZQuadTree(ZQuadTree* pParent);

	// �Ҹ���
	~ZQuadTree();

private:
	// �޸𸮿��� ����Ʈ���� �����մϴ�.
	void			Destroy();

	// �ڽ� ��带 �߰��մϴ�.
	ZQuadTree*		AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	// 4���� �ڳʰ��� �����մϴ�.
	BOOL			SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	// Quadtree�� 4���� ���� Ʈ���� �κ� ����(subdivide)�մϴ�.
	BOOL			SubDivide();

	// ����� �������� �ε����� �����մϴ�.
	int				GenTriIndex(int nTriangles, LPVOID pIndex, TERRAINVERTEX* pHeightMap, ZFrustum* pFrustum, float fLODRatio);

	// �� �� ������ �Ÿ��� ���մϴ�.
	float			GetDistance(D3DXVECTOR3* pv1, D3DXVECTOR3* pv2)
	{
		return D3DXVec3Length(&(*pv2 - *pv1));
	}

	// ī�޶�� ���� ������ �Ÿ� ���� �������� LOD���� ���մϴ�.
	int				GetLODLevel(TERRAINVERTEX* pHeightMap, D3DXVECTOR3* pCamera, float fLODRatio)
	{
		float d = GetDistance((D3DXVECTOR3*)(pHeightMap + m_nCenter), pCamera);
		return max((int)(d*fLODRatio), 1);
	}

	// ���� ��尡 LOD������� �� �� ����� ������ ����ΰ�?
	BOOL IsVisible(TERRAINVERTEX* pHeightMap, D3DXVECTOR3* pCamera, float fLODRatio)
	{
		return ((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= GetLODLevel(pHeightMap, pCamera, fLODRatio));
	}

	// ���� ��尡 Frustum�� ���ԵǴ°�?
	int				IsInFrustum(TERRAINVERTEX* pHeightMap, ZFrustum* pFrustum);

	// IsInFrustum() �Լ��� ����� ���� Frustum �ø� ����
	void			FrustumCull(TERRAINVERTEX* pHeightMap, ZFrustum* pFrustum);

public:
	// QuadTree�� �����մϴ�.
	BOOL			Build(TERRAINVERTEX* pHeightMap);

	// �ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�մϴ�.
	int				GenerateIndex(LPVOID pIndex, TERRAINVERTEX* pHeightMap, ZFrustum* pFrustum, float fLODRatio);
};

#endif // !_ZQUADTREE_H_
