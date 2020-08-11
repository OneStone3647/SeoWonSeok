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

	// 루트 노드의 4개 코너 값 설정
	m_nCorner[CORNER_TL] = 0;
	m_nCorner[CORNER_TR] = cx - 1;
	m_nCorner[CORNER_BL] = cx * (cy - 1);
	m_nCorner[CORNER_BR] = cx * cy - 1;
	m_nCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
		m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 4;

	m_fRadius = 0.0f;
	m_bCulled = FALSE;
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

	m_bCulled = FALSE;
	m_fRadius = 0.0f;
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
	nLeftEdgeCenter			= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	// 우측변 가운데
	nRightEdgeCenter		= (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	// 한가운데
	nCentralPoint			= (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
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
int ZQuadTree::GenTriIndex(int nTriangles, LPVOID pIndex, TERRAINVERTEX * pHeightMap, ZFrustum * pFrustum, float fLODRatio)
{
	// 컬링된 노드라면 그냥 리턴
	if (m_bCulled)
	{
		m_bCulled = FALSE;
		return nTriangles;
	}

	// 현재 노드가 출력되어야 하는가?
	if (IsVisible(pHeightMap,pFrustum->GetPos(),fLODRatio))
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

// 현재 노드가 Frustum에 포함되는가?
int ZQuadTree::IsInFrustum(TERRAINVERTEX * pHeightMap, ZFrustum * pFrustum)
{
	BOOL b[4];
	BOOL bInSphere;

	// 경계구안에 있는가?
	//if (m_fRadius == 0.0f)
	//{
	//	g_pLog->Log("Index:[%d], Radius:[%f]", m_nCenter, m_fRadius);
	//}
	bInSphere = pFrustum->IsInSphere((D3DXVECTOR3*)(pHeightMap + m_nCenter), m_fRadius);

	// 경계구 안에 없으면 점 단위의 Frustum 테스트 생략
	if (!bInSphere)
	{
		return FRUSTUM_OUT;
	}

	// QuadTree의 4군데 경계 Frustum 테스트
	b[0] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + m_nCorner[0]));
	b[1] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + m_nCorner[1]));
	b[2] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + m_nCorner[2]));
	b[3] = pFrustum->IsIn((D3DXVECTOR3*)(pHeightMap + m_nCorner[3]));

	// 4개 모두 Frustum 안에 있음
	if (b[0] + b[1] + b[2] + b[3] == 4)
	{
		return FRUSTUM_COMPLETELY_IN;
	}

	// 일부분인 Frustum에 있는 경우
	return FRUSTUM_PARTIALLY_IN;
}

// IsInFrustum() 함수의 결과에 따라 Frustum 컬링 수행
void ZQuadTree::FrustumCull(TERRAINVERTEX * pHeightMap, ZFrustum * pFrustum)
{
	int ret;

	ret = IsInFrustum(pHeightMap, pFrustum);
	switch (ret)
	{
	case FRUSTUM_COMPLETELY_IN:		// Frustum에 완전 벗어남, 하위 노드 검색 필요없음
		m_bCulled = FALSE;
		break;
	case FRUSTUM_PARTIALLY_IN:		// Frustum에 일부 포함, 하위 노드 검색 필요함
		m_bCulled = FALSE;
		break;
	case FRUSTUM_OUT:					// Frustum에 완전 포함, 하위 노드 검색 필요없음
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

// QuadTree를 구축합니다.(Build() 함수에서 불립니다.)
BOOL ZQuadTree::Build(TERRAINVERTEX * pHeightMap)
{
	if (SubDivide())
	{
		// 좌측 상단과, 우측 하단의 거리를 구한다.
		D3DXVECTOR3 v = *((D3DXVECTOR3*)(pHeightMap + m_nCorner[CORNER_TL])) -
								*((D3DXVECTOR3*)(pHeightMap + m_nCorner[CORNER_BR]));
		/*-----------------------------------------------------------------------------------------------------------------------------------------------------*
		 * v의 거리 값이 이 노드를 감싸는 경계구의 지름이므로,
		 * 2로 나누어 반지름을 구합니다.
		 *-----------------------------------------------------------------------------------------------------------------------------------------------------*/
		m_fRadius = D3DXVec3Length(&v) / 2.0f;
		m_pChild[CORNER_TL]->Build(pHeightMap);
		m_pChild[CORNER_TR]->Build(pHeightMap);
		m_pChild[CORNER_BL]->Build(pHeightMap);
		m_pChild[CORNER_BR]->Build(pHeightMap);
	}

	return TRUE;
}

// 삼각형의 인덱스를 만들고, 출력할 삼각형의 개수를 반환합니다.
int ZQuadTree::GenerateIndex(LPVOID pIndex, TERRAINVERTEX * pHeightMap, ZFrustum * pFrustum, float fLODRatio)
{
	// 먼저 Frustum 컬링을 해서 컬링될 노드들을 배제한다.
	FrustumCull(pHeightMap, pFrustum);

	// 출력할 폴리곤의 인덱스를 생성한 뒤, 폴리곤의 개수를 리턴한다.
	return GenTriIndex(0, pIndex, pHeightMap, pFrustum, fLODRatio);
}
