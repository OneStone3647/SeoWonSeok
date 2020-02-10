#pragma once
#include "Block.h"
#include <vector>

using namespace std;

#define FIELDCOUNTMAX 3		// 필드의 종류
#define PIECECOUNTMAX 6		// 피스의 종류

class BlockManager
{
//	// 싱글톤
//private:
//	static BlockManager* m_This;
//
//public:
//	static BlockManager* GetInstance()
//	{
//		if (m_This == NULL)
//		{
//			m_This = new BlockManager;
//		}
//		return m_This;
//	}

private:
	HDC				hdc;
	HINSTANCE		m_hInst;

	Block*			m_Board;
	Block*			m_BlackPiece;
	Block*			m_WhitePiece;

public:
	BlockManager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void SetBoard();
	void DrawAllBoard();
	void SetPiece();

	//void Release();

	~BlockManager();
};

