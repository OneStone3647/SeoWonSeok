#include "Maptool.h"



Maptool::Maptool()
{
}


Maptool::~Maptool()
{
}

void Maptool::Init(HWND hWnd)
{
	m_ScreenSize.cx = MaptoolWidth;
	m_ScreenSize.cy = MaptoolHeight;

	m_hWnd = hWnd;
	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(hWnd);
	// hdc와 호환되는 DC를 만든다.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc와 호환되는 비트맵을 폭 ScreenWidth, 높이 ScreenHeight의 크기로 만든다.
	m_NewBitmap = CreateCompatibleBitmap(hdc, m_ScreenSize.cx, m_ScreenSize.cy);
	// m_MemDC에 m_NewBitmap을 연결하고 이전 비트맵을 m_OldBitmap에 저장한다.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// 사용한 DC를 해제 한다.
	ReleaseDC(hWnd, hdc);

	MoveWindow(m_hWnd, 200, 100, m_ScreenSize.cx, m_ScreenSize.cy, TRUE);

	// Block 클래스 이차원 벡터가 이미 존재할 경우 할당 해제한다.
	if (!m_Block.empty())
	{
		vector<vector<Block*>>::iterator iterY;
		vector<Block*>::iterator iterX;
		for (iterY = m_Block.begin(); iterY != m_Block.end(); iterY++)
		{
			for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
			{
				delete (*iterX);
			}
			iterY->clear();
			vector<Block*>().swap(*iterY);
		}
		m_Block.clear();
		vector<vector<Block*>>().swap(m_Block);
	}
	// Block 클래스 이차원 백터 동적 할당
	// 이차원 백터 열의 메모리 크기 설정
	m_Block.reserve(MapSizeY);
	for (int y = 0; y < MapSizeY; y++)
	{
		vector<Block*> tmpBlock;
		// 이차원 백터 행의 메모리 크기 설정
		tmpBlock.reserve(MapSizeX);
		for (int x = 0; x < MapSizeX; x++)
		{
			Block* newBlock = new Block;
			newBlock->Init(m_MemDC, x, y);
			//newBlock->SetBlockType(BLOKCTYPE_BLOCK09);
			tmpBlock.push_back(newBlock);
		}
		m_Block.push_back(tmpBlock);
	}
}

void Maptool::Release()
{
	// m_MemDC에 이전 비트맵을 연결한다.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC로 만들어 진 DC는 DeleteDC로 지워야한다.
	DeleteDC(m_MemDC);

	// Block 클래스 이차원 백터 동적 할당 해제
	if (!m_Block.empty())
	{
		vector<vector<Block*>>::iterator iterY;
		vector<Block*>::iterator iterX;
		for (iterY = m_Block.begin(); iterY != m_Block.end(); iterY++)
		{
			for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
			{
				delete (*iterX);
			}
			iterY->clear();
			vector<Block*>().swap(*iterY);
		}
		m_Block.clear();
		vector<vector<Block*>>().swap(m_Block);
	}
}

void Maptool::Update(LPARAM lParam)
{
	//vector<vector<Block*>>::iterator iterY;
	//vector<Block*>::iterator iterX;
	//for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
	//{
	//	if ((*iterX)->GetBlockType() != BLOCKTYPE_EMPTY)
	//	{
	//		(*iterX)->Draw();
	//	}
	//	else
	//	{
	//		HBRUSH newBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//		HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, newBrush);
	//		HPEN newPen = (HPEN)GetStockObject(WHITE_BRUSH);
	//		HPEN oldPen = (HPEN)SelectObject(m_MemDC, newPen);

	//		Rectangle(m_MemDC, (*iterX)->GetBlockPoint().x, (*iterX)->GetBlockPoint().y, (*iterX)->GetBlockPoint().x + BlockSizeX, (*iterX)->GetBlockPoint().y + BlockSizeY);

	//		SelectObject(m_MemDC, oldBrush);
	//		SelectObject(m_MemDC, oldPen);
	//	}
	//}

	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (m_Block[y][x]->GetBlockType() != BLOCKTYPE_EMPTY)
			{
				m_Block[y][x]->Draw();
			}
			else
			{
				HBRUSH newBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
				HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, newBrush);
				HPEN newPen = (HPEN)GetStockObject(WHITE_BRUSH);
				HPEN oldPen = (HPEN)SelectObject(m_MemDC, newPen);

				Rectangle(m_MemDC, m_Block[y][x]->GetBlockPoint().x * BlockSizeX, m_Block[y][x]->GetBlockPoint().y * BlockSizeY, (m_Block[y][x]->GetBlockPoint().x + 1) * BlockSizeX, (m_Block[y][x]->GetBlockPoint().y + 1) * BlockSizeY);

				SelectObject(m_MemDC, oldBrush);
				SelectObject(m_MemDC, oldPen);
			}
		}
	}

	// GetDC를 통해 DC를 받는다.
	HDC hdc = GetDC(m_hWnd);
	// 숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	BitBlt(hdc, 0, 0, MaptoolWidth, MaptoolHeight, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}
