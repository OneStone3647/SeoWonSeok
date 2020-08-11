#include "ZQuadTree.h"


// ���� ��Ʈ ��� ������
ZQuadTree::ZQuadTree(int cx, int cy)
{
	int	i;
	m_nCenter = 0;
	for (i = 0; i < 4; i++)
	{
		m_pChild[i] = NULL;
	}

	// ��Ʈ ����� 4�� �ڳ� �� ����
	m_nCorner[CORNER_TL] = 0;
	m_nCorner[CORNER_TR] = cx - 1;
	m_nCorner[CORNER_BL] = cx * (cy - 1);
	m_nCorner[CORNER_BR] = cx * cy - 1;
	m_nCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
		m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;

	m_fRadius = 0.0f;
	m_bCulled = FALSE;
}

// ���� �ڽ� ��� ������
ZQuadTree::ZQuadTree(ZQuadTree * pParent)
{
	int i;
	m_nCenter = 0;
	for (i = 0; i < 4; i++)
	{
		m_pChild[i] = NULL;
		m_nCorner[i] = 0;
	}

	m_bCulled = FALSE;
	m_fRadius = 0.0f;
}


// �Ҹ���
ZQuadTree::~ZQuadTree()
{
	Destroy();
}

// �޸𸮿��� ����Ʈ���� �����մϴ�.
void ZQuadTree::Destroy()
{
	for (int i = 0; i < 4; i++)
	{
		DEL(m_pChild[i]);
	}
}

// �ڽ� ��带 �߰��մϴ�.
ZQuadTree * ZQuadTree::AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR)
{
	ZQuadTree* pChild;

	pChild = new ZQuadTree(this);
	pChild->SetCorners(nCornerTL, nCornerTR, nCornerBL, nCornerBR);

	return pChild;
}

// 4���� �ڳ� ���� �����մϴ�.
BOOL ZQuadTree::SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR)
{
	m_nCorner[CORNER_TL] = nCornerTL;
	m_nCorner[CORNER_TR] = nCornerTR;
	m_nCorner[CORNER_BL] = nCornerBL;
	m_nCorner[CORNER_BR] = nCornerBR;
	m_nCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
		m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;

	return TRUE;
}

// Quadtree�� 4���� �ڽ� Ʈ���� �κ� ����(subdivide)�մϴ�.
BOOL ZQuadTree::SubDivide()
{
	int		nTopEdgeCenter;
	int		nBottomEdgeCenter;
	int		nLeftEdgeCenter;
	int		nRightEdgeCenter;
	int		nCentralPoint;

	// ��ܺ� ���
	nTopEdgeCenter		= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	// �ϴܺ� ���
	nBottomEdgeCenter	= (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	// ������ ���
	nLeftEdgeCenter			= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	// ������ ���
	nRightEdgeCenter		= (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	// �Ѱ��
	nCentralPoint			= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
									m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;

	// ���̻� ������ �Ұ����Ѱ�? �׷��ٸ� SubDivide() ����
	if ((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= 1)
	{
		return FALSE;
	}

	// 4���� �ڽĳ�� �߰�
	m_pChild[CORNER_TL] = AddChild(m_nCorner[CORNER_TL], nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint);
	m_pChild[CORNER_TR] = AddChild(nTopEdgeCenter, m_nCorner[CORNER_TR], nCentralPoint, nRightEdgeCenter);
	m_pChild[CORNER_BL] = AddChild(nLeftEdgeCenter, nCentralPoint, m_nCorner[CORNER_BL], nBottomEdgeCenter);
	m_pChild[CORNER_BR] = AddChild(nCentralPoint, nRightEdgeCenter, nBottomEdgeCenter, m_nCorner[CORNER_BR]);

	return TRUE;
}

// ����� �������� �ε����� �����մϴ�.
int ZQuadTree::GenTriIndex(int nTriangles, LPVOID pIndex, TERRAINVERTEX * pHeightMap, ZFrustum * pFrustum, float fLODRatio)
{
	// �ø��� ����� �׳� ����
	if (m_bCulled)
	{
		m_bCulled = FALSE;
		return nTriangles;
	}

	// ���� ��尡 ��µǾ�� �ϴ°�?
	if (IsVisible(pHeightMap,pFrustum->GetPos(),fLODRatio))
	{
#ifdef _USE_INDEX16
		LPWORD p = ((LPWORD)pIndex) + nTriangles * 3;
#else
		LPDWORD p = ((LPDWORD)pIndex) + nTriangles * 3;
#endif // _USE_INDEX16

		// ���� ��� �ﰢ��
		*p++ = m_nCorner[0];
		*p++ = m_nCorner[1];
		*p++ = m_nCorner[2];
		nTriangles++;

		// ���� �ϴ� �ﰢ��
		*p++ = m_nCorner[2];
		*p++ = m_nCorner[1];
		*p++ = m_nCorner[3];
		nTriangles++;

		return nTriangles;
	}

	if (m_pChild[CORNER_TL])
	{
		nTriangles = m_pChild[CORNER_TL]->GenTriIndex(nTriangles, pIndex, pHeightMap, pFrustum, fLODRatio);
	}
	if (m_pChild[CORNER_TR])
	{
		nTriangles = m_pChild[CORNER_TR]->GenTriIndex(nTriangles, pIndex, pHeightMap, pFrustum, fLODRatio);
	}
	if (m_pChild[CORNER_BL])
	{
		nTriangles = m_pChild[CORNER_BL]->GenTriIndex(nTriangles, pIndex, pHeightMap, pFrustum, fLODRatio);
	}
	if (m_pChild[CORNER_BR])
	{
		nTriangles = m_pChild[CORNER_BR]->GenTriIndex(nTriangles, pIndex, pHeightMap, pFrustum, fLODRatio);
	}

	return nTriangles;
}

// ���� ��尡 Frustum�� ���ԵǴ°�?
int ZQuadTree::IsInFrustum(TERRAINVERTEX * pHeightMap, ZFrustum * pFrustum)
{
	BOOL b[4];
	BOOL bInSphere;

	// ��豸�ȿ� �ִ°�?
	//if (m_fRadius == 0.0f)
	//{
	//	g_pLog->Log("Index:[%d], Radius:[%f]", m_nCenter, m_fRadius);
	//}
	bInSphere = pFrustum->IsInSphere((D3DXVECTOR3*)(pHeightMap + m_nCenter), m_fRadius);

	// ��豸 �ȿ� ������ �� ������ Frustum �׽�Ʈ ����
	if (!bInSphere)
	{
		return FRUSTUM_OUT;
	}

	// QuadTree�� 4���� ��� Frustum �׽�Ʈ
	b[0] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + m_nCorner[0]));
	b[1] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + m_nCorner[1]));
	b[2] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + m_nCorner[2]));
	b[3] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + m_nCorner[3]));

	// 4�� ��� Frustum �ȿ� ����
	if (b[0] + b[1] + b[2] + b[3] == 4)
	{
		return FRUSTUM_COMPLETELY_IN;
	}

	// �Ϻκ��� Frustum�� �ִ� ���
	return FRUSTUM_PARTIALLY_IN;
}

// IsInFrustum() �Լ��� ����� ���� Frustum �ø� ����
void ZQuadTree::FrustumCull(TERRAINVERTEX * pHeightMap, ZFrustum * pFrustum)
{
	int ret;

	ret = IsInFrustum(pHeightMap, pFrustum);
	switch (ret)
	{
	case FRUSTUM_COMPLETELY_IN:		// Frustum�� ���� ���, ���� ��� �˻� �ʿ����
		m_bCulled = FALSE;
		break;
	case FRUSTUM_PARTIALLY_IN:		// Frustum�� �Ϻ� ����, ���� ��� �˻� �ʿ���
		m_bCulled = FALSE;
		break;
	case FRUSTUM_OUT:					// Frustum�� ���� ����, ���� ��� �˻� �ʿ����
		m_bCulled = TRUE;
		break;
	}

	if (m_pChild[0])
	{
		m_pChild[0]->FrustumCull(pHeightMap, pFrustum);
	}
	if (m_pChild[1])
	{
		m_pChild[1]->FrustumCull(pHeightMap, pFrustum);
	}
	if (m_pChild[2])
	{
		m_pChild[2]->FrustumCull(pHeightMap, pFrustum);
	}
	if (m_pChild[3])
	{
		m_pChild[3]->FrustumCull(pHeightMap, pFrustum);
	}
}

// QuadTree�� �����մϴ�.(Build() �Լ����� �Ҹ��ϴ�.)
BOOL ZQuadTree::Build(TERRAINVERTEX * pHeightMap)
{
	if (SubDivide())
	{
		// ���� ��ܰ�, ���� �ϴ��� �Ÿ��� ���Ѵ�.
		D3DXVECTOR3 v = *((D3DXVECTOR3*)(pHeightMap + m_nCorner[CORNER_TL])) -
								*((D3DXVECTOR3*)(pHeightMap + m_nCorner[CORNER_BR]));
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------*
		 * v�� �Ÿ� ���� �� ��带 ���δ� ��豸�� �����̹Ƿ�,
		 * 2�� ������ �������� ���մϴ�.
		 *-----------------------------------------------------------------------------------------------------------------------------------------------------*/
		m_fRadius = D3DXVec3Length(&v) / 2.0f;
		m_pChild[CORNER_TL]->Build(pHeightMap);
		m_pChild[CORNER_TR]->Build(pHeightMap);
		m_pChild[CORNER_BL]->Build(pHeightMap);
		m_pChild[CORNER_BR]->Build(pHeightMap);
	}

	return TRUE;
}

// �ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�մϴ�.
int ZQuadTree::GenerateIndex(LPVOID pIndex, TERRAINVERTEX * pHeightMap, ZFrustum * pFrustum, float fLODRatio)
{
	// ���� Frustum �ø��� �ؼ� �ø��� ������ �����Ѵ�.
	FrustumCull(pHeightMap, pFrustum);

	// ����� �������� �ε����� ������ ��, �������� ������ �����Ѵ�.
	return GenTriIndex(0, pIndex, pHeightMap, pFrustum, fLODRatio);
}
