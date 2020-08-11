#ifndef _ZQUADTREE_H_
#define _ZQUADTREE_H_

#include "define.h"
#include "ZFrustum.h"
#include "ZFLog.h"

/*===================================================================================*
 * QuadTree의 베이스 클래스
 *===================================================================================*/
class ZQuadTree
{
private:
	// QuadTree에 보관되는 4개의 코너 값에 대한 상수 값
	enum CornerType
	{
		CORNER_TL,
		CORNER_TR,
		CORNER_BL,
		CORNER_BR
	};

	// 이웃 노드 처리용 상수값
	enum 	
	{
		EDGE_UP,
		EDGE_DN,
		EDGE_LT,
		EDGE_RT
	};

	// QuadTree와  Frustum간의 관계
	enum QuadLocation
	{
		FRUSTUM_OUT = 0,					// Frustum에서 완전 벗어남
		FRUSTUM_PARTIALLY_IN = 1,		// Frustum에 부분 포함
		FRUSTUM_COMPLETELY_IN = 2,	// Frustum에 완전 포함
		FRUSTUM_UNKNOWN = -1		// 알 수 없음
	};

private:
	ZQuadTree*		m_pChild[4];		// QuadTree의 4개의 자식 노드

	ZQuadTree*		m_pParent;			// Triangle Crack(Popping)을 막기 위해서 사용합니다.
	ZQuadTree*		m_pNeighbor[4];	// Triangle Crack(Popping)을 막기 위해서 사용합니다.

	int					m_nCenter;		// QuadTree에 보관할 첫번째 값
	int					m_nCorner[4];	// QuadTree에 보관할 두번째 값
											//    TopLeft(TL)      TopRight(TR)
											//              0------1
											//              |      |
											//              |      |
											//              2------3
											// BottomLeft(BL)      BottomRight(BR)

	BOOL				m_bCulled;		// Frustum에서 컬링된 노드인가?
	float				m_fRadius;		// 노드를 감싸는 경계구(bounding sphere)의 반지름

public:
	// 최초 루트 노드 생서앚
	ZQuadTree(int cx, int cy);

	// 하위 자식 노드 생성자
	ZQuadTree(ZQuadTree* pParent);

	// 소멸자
	~ZQuadTree();

private:
	// 메모리에서 쿼드트리를 삭제합니다.
	void			Destroy();

	// 자식 노드를 추가합니다.
	ZQuadTree*		AddChild(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	// 4개의 코너값을 셋팅합니다.
	BOOL			SetCorners(int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR);

	// Quadtree를 4개의 하위 트리로 부분 분할(subdivide)합니다.
	BOOL			SubDivide();

	// 출력할 폴리곤의 인덱스를 생성합니다.
	int				GenTriIndex(int nTriangles, LPVOID pIndex, TERRAINVERTEX* pHeightMap, ZFrustum* pFrustum, float fLODRatio);

	// 두 점 사이의 거리를 구합니다.
	float			GetDistance(D3DXVECTOR3* pv1, D3DXVECTOR3* pv2)
	{
		return D3DXVec3Length(&(*pv2 - *pv1));
	}

	// 카메라와 현재 노드와의 거리 값을 기준으로 LOD값을 구합니다.
	int				GetLODLevel(TERRAINVERTEX* pHeightMap, D3DXVECTOR3* pCamera, float fLODRatio)
	{
		float d = GetDistance((D3DXVECTOR3*)(pHeightMap + m_nCenter), pCamera);
		return max((int)(d*fLODRatio), 1);
	}

	// 현재 노드가 LOD등급으로 볼 때 출력이 가능한 노드인가?
	BOOL IsVisible(TERRAINVERTEX* pHeightMap, D3DXVECTOR3* pCamera, float fLODRatio)
	{
		return ((m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= GetLODLevel(pHeightMap, pCamera, fLODRatio));
	}

	// 현재 노드가 Frustum에 포함되는가?
	int				IsInFrustum(TERRAINVERTEX* pHeightMap, ZFrustum* pFrustum);

	// IsInFrustum() 함수의 결과에 따라 Frustum 컬링 수행
	void			FrustumCull(TERRAINVERTEX* pHeightMap, ZFrustum* pFrustum);

	// 이웃 노드를 만듭니다.(삼각형 찢어짐 방지용)
	void			BuildNeighborNode(ZQuadTree* pRoot, TERRAINVERTEX* pHeightMap, int cx);

	// QuadTree를 만듭니다.(Build()함수에서 불립니다.)
	BOOL			BuildQuadTree(TERRAINVERTEX* pHeightMap);

	// QuadTree를 검색해서 4개 코너 값과 일치하는 노드를 찾습니다.
	ZQuadTree*	FindNode(TERRAINVERTEX* pHeightMap, int _0, int _1, int _2, int _3);

	// 4개 방향(상단, 하단, 좌측, 우측)의 이웃노드 인덱스를 구합니다.
	int				GetNodeIndex(int ed, int cx, int& _0, int& _1, int& _2, int& _3);

public:
	// QuadTree를 구축합니다.
	BOOL			Build(TERRAINVERTEX* pHeightMap);

	// 코너 인덱스 값을 얻어 옵니다.
	void			GetCorner(int& _0, int& _1, int& _2, int& _3)
	{
		_0 = m_nCorner[0];
		_1 = m_nCorner[1];
		_2 = m_nCorner[2];
		_3 = m_nCorner[3];
	}

	// 삼각형의 인덱스를 만들고, 출력할 삼각형의 개수를 반환합니다.
	int				GenerateIndex(LPVOID pIndex, TERRAINVERTEX* pHeightMap, ZFrustum* pFrustum, float fLODRatio);
};

#endif // !_ZQUADTREE_H_
