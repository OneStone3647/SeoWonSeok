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
	m_pParent = pParent;
	m_nCenter = 0;
	for (i = 0; i < 4; i++)
	{
		m_pChild[i] = NULL;
		m_pNeighbor[i] = NULL;
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
	nTopEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	// �ϴܺ� ���
	nBottomEdgeCenter = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	// ������ ���
	nLeftEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	// ������ ���
	nRightEdgeCenter = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	// �Ѱ��
	nCentralPoint = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
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

#ifdef _USE_INDEX16
		LPWORD p = ((LPWORD)pIndex) + nTriangles * 3;
#else
		LPDWORD p = ((LPDWORD)pIndex) + nTriangles * 3;
#endif // _USE_INDEX16

	// ���� ��尡 ��µǾ�� �ϴ°�?
	if (IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio))
	{
		// ���� ������ ����� �κк���(subdivide)�� �Ұ����ϹǷ� �׳� ����ϰ� �����մϴ�.
		if (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1)
		{
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

		BOOL b[4];

		// ��� �̿� ���(neighbor node)�� ��� �����Ѱ�?
		if (m_pNeighbor[EDGE_UP])
		{
			b[EDGE_UP] = m_pNeighbor[EDGE_UP]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		}
		// �ϴ� �̿� ���(neighbor node)�� ��� �����Ѱ�?
		if (m_pNeighbor[EDGE_DN])
		{
			b[EDGE_DN] = m_pNeighbor[EDGE_DN]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		}
		// ���� �̿� ���(neighbor node)�� ��� �����Ѱ�?
		if (m_pNeighbor[EDGE_LT])
		{
			b[EDGE_LT] = m_pNeighbor[EDGE_LT]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		}
		// ���� �̿� ���(neighbor node)�� ��� �����Ѱ�?
		if (m_pNeighbor[EDGE_RT])
		{
			b[EDGE_RT] = m_pNeighbor[EDGE_RT]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		}

		/*--------------------------------------------------------------------------------------------------------------------*
		 * �̿� ������ ��δ� ��°����ϴٸ� ���� ���� �̿� ������ ���� LOD�̹Ƿ�
		 * �κк����� �ʿ�����ϴ�.
		 *--------------------------------------------------------------------------------------------------------------------*/
		if (b[EDGE_UP] && b[EDGE_DN] && b[EDGE_LT] && b[EDGE_RT])
		{
			*p++ = m_nCorner[0];
			*p++ = m_nCorner[1];
			*p++ = m_nCorner[2];
			nTriangles++;
			*p++ = m_nCorner[2];
			*p++ = m_nCorner[1];
			*p++ = m_nCorner[3];
			nTriangles++;

			return nTriangles;
		}

		int n;

		// ��� �κк����� �ʿ��Ѱ�?
		if (!b[EDGE_UP])
		{
			n = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_TL];
			*p++ = n;
			nTriangles++;
			*p++ = m_nCenter;
			*p++ = n;
			*p++ = m_nCorner[CORNER_TR];
			nTriangles++;
		}
		// ��� �κк����� �ʿ���� ���
		else
		{
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_TL];
			*p++ = m_nCorner[CORNER_TR];
			nTriangles++;
		}

		// �ϴ� �κк����� �ʿ��Ѱ�?
		if (!b[EDGE_DN])
		{
			n = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_BR];
			*p++ = n;
			nTriangles++;
			*p++ = m_nCenter;
			*p++ = n;
			*p++ = m_nCorner[CORNER_BL];
			nTriangles++;
		}
		// �ϴ� �κк����� �ʿ���� ���
		else
		{
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_BR];
			*p++ = m_nCorner[CORNER_BL];
			nTriangles++;
		}

		// ���� �κк����� �ʿ��Ѱ�?
		if (!b[EDGE_LT])
		{
			n = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_BL];
			*p++ = n;
			nTriangles++;
			*p++ = m_nCenter;
			*p++ = n;
			*p++ = m_nCorner[CORNER_TL];
			nTriangles++;
		}
		// ���� �κк����� �ʿ���� ���
		else
		{
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_BL];
			*p++ = m_nCorner[CORNER_TL];
			nTriangles++;
		}

		// ���� �κк����� �ʿ��Ѱ�?
		if (!b[EDGE_RT])
		{
			n = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_TR];
			*p++ = n;
			nTriangles++;
			*p++ = m_nCenter;
			*p++ = n;
			*p++ = m_nCorner[CORNER_BR];
			nTriangles++;
		}
		// ���� �κк����� �ʿ���� ���
		else
		{
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_TR];
			*p++ = m_nCorner[CORNER_BR];
			nTriangles++;
		}

		// �� ��� �Ʒ��� �ڽ� ���� Ž���� �ʿ� �����Ƿ� �����մϴ�.
		return nTriangles;
	}

	// �ڽ� ���� �˻�
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

// �̿� ��带 ����ϴ�.(�ﰢ�� ������ ������)
void ZQuadTree::BuildNeighborNode(ZQuadTree * pRoot, TERRAINVERTEX * pHeightMap, int cx)
{
	int n;
	int _0, _1, _2, _3;

	for (int i = 0; i < 4; i++)
	{
		_0 = m_nCorner[0];
		_1 = m_nCorner[1];
		_2 = m_nCorner[2];
		_3 = m_nCorner[3];
		// �̿� ����� 4�� �ڳ� ���� ����ϴ�.
		n = GetNodeIndex(i, cx, _0, _1, _2, _3);
		// �ڳ� ������ �̿� ����� �����͸� ���ɴϴ�.
		if (n >= 0)
		{
			m_pNeighbor[i] = pRoot->FindNode(pHeightMap, _0, _1, _2, _3);
		}
	}

	// �ڽ� ���� ���ȣ��
	if (m_pChild[0])
	{
		m_pChild[0]->BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[1]->BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[2]->BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[3]->BuildNeighborNode(pRoot, pHeightMap, cx);
	}
}

// QuadTree�� ����ϴ�.(Build()�Լ����� �Ҹ��ϴ�.)
BOOL ZQuadTree::BuildQuadTree(TERRAINVERTEX * pHeightMap)
{
	if (SubDivide())
	{
		// ���� ��ܰ� ���� �ϴ��� �Ÿ��� ���մϴ�.
		D3DXVECTOR3 v = *((D3DXVECTOR3*)(pHeightMap + m_nCorner[CORNER_TL])) -
								*((D3DXVECTOR3*)(pHeightMap + m_nCorner[CORNER_BR]));
		/*--------------------------------------------------------------------------------------------------------------------*
		 * v�� �Ÿ� ���� �� ��带 ���δ� ��豸�� �����̹Ƿ�,
		 * 2�� ������ �������� ���մϴ�.
		 *--------------------------------------------------------------------------------------------------------------------*/
		m_fRadius = D3DXVec3Length(&v) / 2.0f;
		m_pChild[CORNER_TL]->BuildQuadTree(pHeightMap);
		m_pChild[CORNER_TR]->BuildQuadTree(pHeightMap);
		m_pChild[CORNER_BL]->BuildQuadTree(pHeightMap);
		m_pChild[CORNER_BR]->BuildQuadTree(pHeightMap);
	}

	return TRUE;
}

// QuadTree�� �˻��ؼ� 4�� �ڳ� ���� ��ġ�ϴ� ��带 ã���ϴ�.
ZQuadTree * ZQuadTree::FindNode(TERRAINVERTEX * pHeightMap, int _0, int _1, int _2, int _3)
{
	ZQuadTree* p = NULL;
	// ��ġ�ϴ� ����� ��� ���� ����
	if ((m_nCorner[0] == _0) && (m_nCorner[1] == _1) && (m_nCorner[2] == _2) && (m_nCorner[3] == _3))
	{
		return this;
	}

	// �ڽ� ��尡 �ִ°�?
	if (m_pChild[0])
	{
		RECT rc;
		POINT pt;
		int n = (_0 + _1 + _2 + _3) / 4;

		// ���� �ʻ󿡼��� ��ġ
		pt.x = (int)pHeightMap[n].p.x;
		pt.y = (int)pHeightMap[n].p.z;

		// 4���� �ڳ� ���� �������� �ڽ� ����� �� ���������� ����ϴ�.
		SetRect(&rc, (int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_BR]].p.z);
		// pt���� �������� �ȿ� �ִٸ� �ڽĳ��� ���ϴ�.
		if (IsInRect(&rc, pt))
		{
			return m_pChild[0]->FindNode(pHeightMap, _0, _1, _2, _3);
		}

		// 4���� �ڳ� ���� �������� �ڽ� ����� �� ���������� ����ϴ�.
		SetRect(&rc, (int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_BR]].p.z);
		// pt���� �������� �ȿ� �ִٸ� �ڽĳ��� ���ϴ�.
		if (IsInRect(&rc, pt))
		{
			return m_pChild[1]->FindNode(pHeightMap, _0, _1, _2, _3);
		}

		// 4���� �ڳ� ���� �������� �ڽ� ����� �� ���������� ����ϴ�.
		SetRect(&rc, (int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_BR]].p.z);
		// pt���� �������� �ȿ� �ִٸ� �ڽĳ��� ���ϴ�.
		if (IsInRect(&rc, pt))
		{
			return m_pChild[0]->FindNode(pHeightMap, _0, _1, _2, _3);
		}

		// 4���� �ڳ� ���� �������� �ڽ� ����� �� ���������� ����ϴ�.
		SetRect(&rc, (int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_BR]].p.z);
		// pt���� �������� �ȿ� �ִٸ� �ڽĳ��� ���ϴ�.
		if (IsInRect(&rc, pt))
		{
			return m_pChild[0]->FindNode(pHeightMap, _0, _1, _2, _3);
		}
	}

	return NULL;
}

// 4�� ����(���, �ϴ�, ����, ����)�� �̿���� �ε����� ���մϴ�.
int ZQuadTree::GetNodeIndex(int ed, int cx, int & _0, int & _1, int & _2, int & _3)
{
	int n, _a, _b, _c, _d, gap;
	_a = _0;
	_b = _1;
	_c = _2;
	_d = _3;
	gap = _b - _a;			// ���� ����� �¿��� ��

	switch (ed)
	{
	case EDGE_UP:					// ���� ���� �̿������ �ε���
		_0 = _a - cx * gap;
		_1 = _b - cx * gap;
		_2 = _a;
		_3 = _b;
		break;
	case EDGE_DN:					// �Ʒ� ���� �̿������ �ε���
		_0 = _c;
		_1 = _d;
		_2 = _c + cx * gap;
		_3 = _d + cx * gap;
		break;
	case EDGE_LT:					// ���� ���� �̿������ �ε���
		_0 = _a - gap;
		_1 = _a;
		_2 = _c - gap;
		_3 = _c;
		break;
	case EDGE_RT:					// ���� ���� �̿������ �ε���
		_0 = _b;
		_1 = _b + gap;
		_2 = _d;
		_3 = _d + gap;
		break;
	}

	n = (_0 + _1 + _2 + _3) / 4;		// ��� �ε���
	if (!IS_IN_RANGE(n, 0, cx * cx - 1))
	{
		return -1;
	}

	return n;
}

// QuadTree�� �����մϴ�.(Build() �Լ����� �Ҹ��ϴ�.)
BOOL ZQuadTree::Build(TERRAINVERTEX * pHeightMap)
{
	// QuadTree ����
	BuildQuadTree(pHeightMap);
	// �̿� ��� ����
	BuildNeighborNode(this, pHeightMap, m_nCorner[CORNER_TR] + 1);

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
