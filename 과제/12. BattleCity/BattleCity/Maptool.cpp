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
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� ScreenWidth, ���� ScreenHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, m_ScreenSize.cx, m_ScreenSize.cy);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� ���� �Ѵ�.
	ReleaseDC(hWnd, hdc);

	MoveWindow(m_hWnd, 200, 100, m_ScreenSize.cx, m_ScreenSize.cy, TRUE);

	// Block Ŭ���� ������ ���Ͱ� �̹� ������ ��� �Ҵ� �����Ѵ�.
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
	// Block Ŭ���� ������ ���� ���� �Ҵ�
	// ������ ���� ���� �޸� ũ�� ����
	m_Block.reserve(MapSizeY);
	for (int y = 0; y < MapSizeY; y++)
	{
		vector<Block*> tmpBlock;
		// ������ ���� ���� �޸� ũ�� ����
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
	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ����� �� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);

	// Block Ŭ���� ������ ���� ���� �Ҵ� ����
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

	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	BitBlt(hdc, 0, 0, MaptoolWidth, MaptoolHeight, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}
