#ifndef _ZQUADTREE_H_
#define _ZQUADTREE_H_

#include "define.h"

/*===================================================================================*
 * QuadTree�� ���̽� Ŭ����
 *===================================================================================*/
class ZQuadTree
{
private:
	// ���� Ʈ���� �����Ǵ� 4���� �ڳ� ���� ���� ��� ��
	enum CornerType
	{
		CORNER_TL,
		CORNER_TR,
		CORNER_BL,
		CORNER_BR
	};

private:
	ZQuadTree*		m_pChild[4];		// QuadTree�� 4���� �ڽ� ���

	int				m_nCenter;			// QuadTree�� ������ ù��° ��
	int				m_nCorner[4];		// QuadTree�� ������ �ι�° ��
										//    TopLeft(TL)      TopRight(TR)
										//              0------1
										//              |      |
										//              |      |
										//              2------3
										// BottomLeft(BL)      BottomRight(BR)

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

	// ���� ��尡 ����� ������ ����ΰ�?
	BOOL			IsVisible()
	{
		return (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1);
	}

	// ����� �������� �ε����� �����մϴ�.
	int				GenTriIndex(int nTriangles, LPVOID pIndex);

public:
	// QuadTree�� �����մϴ�.
	BOOL			Build();

	// �ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�մϴ�.
	int				GenerateIndex(LPVOID pIndex);
};

#endif // !_ZQUADTREE_H_
