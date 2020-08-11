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
	nTopEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR]) / 2;
	// 하단변 가운데
	nBottomEdgeCenter = (m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR]) / 2;
	// 좌측변 가운데
	nLeftEdgeCenter = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL]) / 2;
	// 우측변 가운데
	nRightEdgeCenter = (m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR]) / 2;
	// 한가운데
	nCentralPoint = (m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] +
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

#ifdef _USE_INDEX16
		LPWORD p = ((LPWORD)pIndex) + nTriangles * 3;
#else
		LPDWORD p = ((LPDWORD)pIndex) + nTriangles * 3;
#endif // _USE_INDEX16

	// 현재 노드가 출력되어야 하는가?
	if (IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio))
	{
		// 만약 최하위 노드라면 부분분할(subdivide)이 불가능하므로 그냥 출력하고 리턴합니다.
		if (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1)
		{
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

		BOOL b[4];

		// 상단 이웃 노드(neighbor node)가 출력 가능한가?
		if (m_pNeighbor[EDGE_UP])
		{
			b[EDGE_UP] = m_pNeighbor[EDGE_UP]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		}
		// 하단 이웃 노드(neighbor node)가 출력 가능한가?
		if (m_pNeighbor[EDGE_DN])
		{
			b[EDGE_DN] = m_pNeighbor[EDGE_DN]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		}
		// 좌측 이웃 노드(neighbor node)가 출력 가능한가?
		if (m_pNeighbor[EDGE_LT])
		{
			b[EDGE_LT] = m_pNeighbor[EDGE_LT]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		}
		// 우측 이웃 노드(neighbor node)가 출력 가능한가?
		if (m_pNeighbor[EDGE_RT])
		{
			b[EDGE_RT] = m_pNeighbor[EDGE_RT]->IsVisible(pHeightMap, pFrustum->GetPos(), fLODRatio);
		}

		/*--------------------------------------------------------------------------------------------------------------------*
		 * 이웃 노드들이 모두다 출력가능하다면 현재 노드와 이웃 노드들이 같은 LOD이므로
		 * 부분분할이 필요없습니다.
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

		// 상단 부분분할이 필요한가?
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
		// 상단 부분분할이 필요없을 경우
		else
		{
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_TL];
			*p++ = m_nCorner[CORNER_TR];
			nTriangles++;
		}

		// 하단 부분분할이 필요한가?
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
		// 하단 부분분할이 필요없을 경우
		else
		{
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_BR];
			*p++ = m_nCorner[CORNER_BL];
			nTriangles++;
		}

		// 좌측 부분분할이 필요한가?
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
		// 좌측 부분분할이 필요없을 경우
		else
		{
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_BL];
			*p++ = m_nCorner[CORNER_TL];
			nTriangles++;
		}

		// 우측 부분분할이 필요한가?
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
		// 우측 부분분할이 필요없을 경우
		else
		{
			*p++ = m_nCenter;
			*p++ = m_nCorner[CORNER_TR];
			*p++ = m_nCorner[CORNER_BR];
			nTriangles++;
		}

		// 이 노드 아래의 자식 노드는 탐색할 필요 없으므로 리턴합니다.
		return nTriangles;
	}

	// 자식 노드들 검색
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

// 이웃 노드를 만듭니다.(삼각형 찢어짐 방지용)
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
		// 이웃 노드의 4개 코너 값을 얻습니다.
		n = GetNodeIndex(i, cx, _0, _1, _2, _3);
		// 코너 값으로 이웃 노드의 포인터를 얻어옵니다.
		if (n >= 0)
		{
			m_pNeighbor[i] = pRoot->FindNode(pHeightMap, _0, _1, _2, _3);
		}
	}

	// 자식 노드로 재귀호출
	if (m_pChild[0])
	{
		m_pChild[0]->BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[1]->BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[2]->BuildNeighborNode(pRoot, pHeightMap, cx);
		m_pChild[3]->BuildNeighborNode(pRoot, pHeightMap, cx);
	}
}

// QuadTree를 만듭니다.(Build()함수에서 불립니다.)
BOOL ZQuadTree::BuildQuadTree(TERRAINVERTEX * pHeightMap)
{
	if (SubDivide())
	{
		// 좌측 상단과 우측 하단의 거리를 구합니다.
		D3DXVECTOR3 v = *((D3DXVECTOR3*)(pHeightMap + m_nCorner[CORNER_TL])) -
								*((D3DXVECTOR3*)(pHeightMap + m_nCorner[CORNER_BR]));
		/*--------------------------------------------------------------------------------------------------------------------*
		 * v의 거리 값이 이 노드를 감싸는 경계구의 지름이므로,
		 * 2로 나누어 반지름을 구합니다.
		 *--------------------------------------------------------------------------------------------------------------------*/
		m_fRadius = D3DXVec3Length(&v) / 2.0f;
		m_pChild[CORNER_TL]->BuildQuadTree(pHeightMap);
		m_pChild[CORNER_TR]->BuildQuadTree(pHeightMap);
		m_pChild[CORNER_BL]->BuildQuadTree(pHeightMap);
		m_pChild[CORNER_BR]->BuildQuadTree(pHeightMap);
	}

	return TRUE;
}

// QuadTree를 검색해서 4개 코너 값과 일치하는 노드를 찾습니다.
ZQuadTree * ZQuadTree::FindNode(TERRAINVERTEX * pHeightMap, int _0, int _1, int _2, int _3)
{
	ZQuadTree* p = NULL;
	// 일치하는 노드라면 노드 값을 리턴
	if ((m_nCorner[0] == _0) && (m_nCorner[1] == _1) && (m_nCorner[2] == _2) && (m_nCorner[3] == _3))
	{
		return this;
	}

	// 자식 노드가 있는가?
	if (m_pChild[0])
	{
		RECT rc;
		POINT pt;
		int n = (_0 + _1 + _2 + _3) / 4;

		// 현재 맵상에서의 위치
		pt.x = (int)pHeightMap[n].p.x;
		pt.y = (int)pHeightMap[n].p.z;

		// 4개의 코너 값을 기준으로 자식 노드의 맵 점유범위를 얻습니다.
		SetRect(&rc, (int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[0]->m_nCorner[CORNER_BR]].p.z);
		// pt값이 점유범위 안에 있다면 자식노드로 들어갑니다.
		if (IsInRect(&rc, pt))
		{
			return m_pChild[0]->FindNode(pHeightMap, _0, _1, _2, _3);
		}

		// 4개의 코너 값을 기준으로 자식 노드의 맵 점유범위를 얻습니다.
		SetRect(&rc, (int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[1]->m_nCorner[CORNER_BR]].p.z);
		// pt값이 점유범위 안에 있다면 자식노드로 들어갑니다.
		if (IsInRect(&rc, pt))
		{
			return m_pChild[1]->FindNode(pHeightMap, _0, _1, _2, _3);
		}

		// 4개의 코너 값을 기준으로 자식 노드의 맵 점유범위를 얻습니다.
		SetRect(&rc, (int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[2]->m_nCorner[CORNER_BR]].p.z);
		// pt값이 점유범위 안에 있다면 자식노드로 들어갑니다.
		if (IsInRect(&rc, pt))
		{
			return m_pChild[0]->FindNode(pHeightMap, _0, _1, _2, _3);
		}

		// 4개의 코너 값을 기준으로 자식 노드의 맵 점유범위를 얻습니다.
		SetRect(&rc, (int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_TL]].p.x,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_TL]].p.z,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_BR]].p.x,
			(int)pHeightMap[m_pChild[3]->m_nCorner[CORNER_BR]].p.z);
		// pt값이 점유범위 안에 있다면 자식노드로 들어갑니다.
		if (IsInRect(&rc, pt))
		{
			return m_pChild[0]->FindNode(pHeightMap, _0, _1, _2, _3);
		}
	}

	return NULL;
}

// 4개 방향(상단, 하단, 좌측, 우측)의 이웃노드 인덱스를 구합니다.
int ZQuadTree::GetNodeIndex(int ed, int cx, int & _0, int & _1, int & _2, int & _3)
{
	int n, _a, _b, _c, _d, gap;
	_a = _0;
	_b = _1;
	_c = _2;
	_d = _3;
	gap = _b - _a;			// 현재 노드의 좌우폭 값

	switch (ed)
	{
	case EDGE_UP:					// 위쪽 방향 이웃노드의 인덱스
		_0 = _a - cx * gap;
		_1 = _b - cx * gap;
		_2 = _a;
		_3 = _b;
		break;
	case EDGE_DN:					// 아래 방향 이웃노드의 인덱스
		_0 = _c;
		_1 = _d;
		_2 = _c + cx * gap;
		_3 = _d + cx * gap;
		break;
	case EDGE_LT:					// 좌측 방향 이웃노드의 인덱스
		_0 = _a - gap;
		_1 = _a;
		_2 = _c - gap;
		_3 = _c;
		break;
	case EDGE_RT:					// 우측 방향 이웃노드의 인덱스
		_0 = _b;
		_1 = _b + gap;
		_2 = _d;
		_3 = _d + gap;
		break;
	}

	n = (_0 + _1 + _2 + _3) / 4;		// 가운데 인덱스
	if (!IS_IN_RANGE(n, 0, cx * cx - 1))
	{
		return -1;
	}

	return n;
}

// QuadTree를 구축합니다.(Build() 함수에서 불립니다.)
BOOL ZQuadTree::Build(TERRAINVERTEX * pHeightMap)
{
	// QuadTree 구축
	BuildQuadTree(pHeightMap);
	// 이웃 노드 구축
	BuildNeighborNode(this, pHeightMap, m_nCorner[CORNER_TR] + 1);

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
