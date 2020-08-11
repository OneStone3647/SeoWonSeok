#include "ZQuadTree.h"


// 최초 루트 노드 생성자
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

// 하위 자식 노드 생성자
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


// 소멸자
ZQuadTree::~ZQuadTree()
{
	Destroy();
}

// 메모리에서 쿼드트리를 삭제합니다.
void ZQuadTree::Destroy()
{
	for (int i = 0; i < 4; i++)
	{
		DEL(m_pChild[i]);
	}
}

// 자식 노드를 추가합니다.
ZQuadTree * ZQuadTree::AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR)
{
	ZQuadTree* pChild;

	pChild = new ZQuadTree(this);
	pChild->SetCorners(nCornerTL, nCornerTR, nCornerBL, nCornerBR);

	return pChild;
}

// 4개의 코너 값을 셋팅합니다.
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

// Quadtree를 4개의 자식 트리로 부분 분할(subdivide)합니다.
BOOL ZQuadTree::SubDivide()
{
	int		nTopEdgeCenter;
	int		nBottomEdgeCenter;
	int		nLeftEdgeCenter;
	int		nRightEdgeCenter;
	int		nCentralPoint;

	// 상단변 가운데
	nTopEdgeCenter		= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	// 하단변 가운데
	nBottomEdgeCenter	= (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	// 좌측변 가운데
	nLeftEdgeCenter		= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	// 우측변 가운데
	nRightEdgeCenter	= (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	// 한가운데
	nCentralPoint		= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
						   m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;

	// 더이상 분할이 불가능한가? 그렇다면 SubDivide() 종료
	if ((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= 1)
	{
		return FALSE;
	}

	// 4개의 자식노드 추가
	m_pChild[CORNER_TL] = AddChild(m_nCorner[CORNER_TL], nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint);
	m_pChild[CORNER_TR] = AddChild(nTopEdgeCenter, m_nCorner[CORNER_TR], nCentralPoint, nRightEdgeCenter);
	m_pChild[CORNER_BL] = AddChild(nLeftEdgeCenter, nCentralPoint, m_nCorner[CORNER_BL], nBottomEdgeCenter);
	m_pChild[CORNER_BR] = AddChild(nCentralPoint, nRightEdgeCenter, nBottomEdgeCenter, m_nCorner[CORNER_BR]);

	return TRUE;
}

// 출력할 폴리곤의 인덱스를 생성합니다.
int ZQuadTree::GenTriIndex(int nTriangles, LPVOID pIndex)
{
	if (IsVisible())
	{
#ifdef _USE_INDEX16
		LPWORD p = ((LPWORD)pIndex) + nTriangles * 3;
#else
		LPDWORD p = ((LPDWORD)pIndex) + nTriangles * 3;
#endif // _USE_INDEX16

		// 좌측 상단 삼각형
		*p++ = m_nCorner[0];
		*p++ = m_nCorner[1];
		*p++ = m_nCorner[2];
		nTriangles++;

		// 우측 하단 삼각형
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


// QuadTree를 구축합니다.
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

// 삼각형의 인덱스를 만들고, 출력할 삼각형의 개수를 반환합니다.
int ZQuadTree::GenerateIndex(LPVOID pIndex)
{
	return GenTriIndex(0, pIndex);
}
