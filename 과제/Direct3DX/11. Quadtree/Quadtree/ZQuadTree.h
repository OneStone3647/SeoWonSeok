#ifndef _ZQUADTREE_H_
#define _ZQUADTREE_H_

#include "define.h"

/*===================================================================================*
 * QuadTree의 베이스 클래스
 *===================================================================================*/
class ZQuadTree
{
private:
	// 쿼드 트리에 보관되는 4개의 코너 값에 대한 상수 값
	enum CornerType
	{
		CORNER_TL,
		CORNER_TR,
		CORNER_BL,
		CORNER_BR
	};

private:
	ZQuadTree*		m_pChild[4];		// QuadTree의 4개의 자식 노드

	int				m_nCenter;			// QuadTree에 보관할 첫번째 값
	int				m_nCorner[4];		// QuadTree에 보관할 두번째 값
										//    TopLeft(TL)      TopRight(TR)
										//              0------1
										//              |      |
										//              |      |
										//              2------3
										// BottomLeft(BL)      BottomRight(BR)

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

	// 현재 노드가 출력이 가능한 노드인가?
	BOOL			IsVisible()
	{
		return (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1);
	}

	// 출력할 폴리곤의 인덱스를 생성합니다.
	int				GenTriIndex(int nTriangles, LPVOID pIndex);

public:
	// QuadTree를 구축합니다.
	BOOL			Build();

	// 삼각형의 인덱스를 만들고, 출력할 삼각형의 개수를 반환합니다.
	int				GenerateIndex(LPVOID pIndex);
};

#endif // !_ZQUADTREE_H_
