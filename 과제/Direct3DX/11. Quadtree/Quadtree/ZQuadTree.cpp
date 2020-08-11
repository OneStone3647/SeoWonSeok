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
	
	m_nCorner[CORNER_TL] = 0;
	m_nCorner[CORNER_TR] = cx - 1;
	m_nCorner[CORNER_BL] = cx * (cy - 1);
	m_nCorner[CORNER_BR] = cx * cy - 1;
	m_nCenter			 = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
							m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;
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
	nLeftEdgeCenter		= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	// ������ ���
	nRightEdgeCenter	= (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	// �Ѱ��
	nCentralPoint		= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
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
int ZQuadTree::GenTriIndex(int nTriangles, LPVOID pIndex)
{
	if (IsVisible())
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
		nTriangles = m_pChild[CORNER_TL]->GenTriIndex(nTriangles, pIndex);
	}
	if (m_pChild[CORNER_TR])
	{
		nTriangles = m_pChild[CORNER_TR]->GenTriIndex(nTriangles, pIndex);
	}
	if (m_pChild[CORNER_BL])
	{
		nTriangles = m_pChild[CORNER_BL]->GenTriIndex(nTriangles, pIndex);
	}
	if (m_pChild[CORNER_BR])
	{
		nTriangles = m_pChild[CORNER_BR]->GenTriIndex(nTriangles, pIndex);
	}

	return nTriangles;
}


// QuadTree�� �����մϴ�.
BOOL ZQuadTree::Build()
{
	if (SubDivide())
	{
		m_pChild[CORNER_TL]->Build();
		m_pChild[CORNER_TR]->Build();
		m_pChild[CORNER_BL]->Build();
		m_pChild[CORNER_BR]->Build();
	}

	return TRUE;
}

// �ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�մϴ�.
int ZQuadTree::GenerateIndex(LPVOID pIndex)
{
	return GenTriIndex(0, pIndex);
}
