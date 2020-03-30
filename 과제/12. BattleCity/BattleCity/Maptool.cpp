#include "Maptool.h"

Maptool* Maptool::m_pThis = NULL;

Maptool::Maptool()
{
}


Maptool::~Maptool()
{
	Release();
}

void Maptool::Init()
{
	MoveWindow(m_hWnd, WindowPosX, WindowPosY, m_ScreenSize.cx, m_ScreenSize.cy, TRUE);
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

	MoveWindow(m_hWnd, WindowPosX, WindowPosY, m_ScreenSize.cx, m_ScreenSize.cy, TRUE);

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
	POINT m_MousePoint = { 2000, 2000 };
	DrawBackGround();

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		m_MousePoint.x = LOWORD(lParam);
		m_MousePoint.y = HIWORD(lParam);
	}

	for (vector<vector<Block*>>::size_type y = 0; y < m_Block.size(); ++y)
	{
		for (vector<Block*>::size_type x = 0; x < m_Block[y].size(); ++x)
		{
			if (m_Block[y][x]->GetCollision().CheckMouseHit(m_MousePoint))
			{
				m_Block[y][x]->SetBlockType(BLOKCTYPE_BLOCK01);
			}

			if (m_Block[y][x]->GetBlockType() != BLOCKTYPE_EMPTY)
			{
				m_Block[y][x]->Draw();
			}
			else
			{
				HBRUSH newBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
				// m_MemDC�� newBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
				HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, newBrush);
				HPEN newPen = (HPEN)GetStockObject(WHITE_BRUSH);
				HPEN oldPen = (HPEN)SelectObject(m_MemDC, newPen);

				Rectangle(m_MemDC, m_Block[y][x]->GetBlockPoint().x * BlockSizeX, m_Block[y][x]->GetBlockPoint().y * BlockSizeY, (m_Block[y][x]->GetBlockPoint().x + 1) * BlockSizeX, (m_Block[y][x]->GetBlockPoint().y + 1) * BlockSizeY);

				// m_MemDC�� oldBrush�� �����Ѵ�.
				SelectObject(m_MemDC, oldBrush);
				// m_MemDC�� oldPen�� �����Ѵ�.
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

void Maptool::DrawBackGround()
{
	HBRUSH newBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	// m_MemDC�� newBrush�� �����ϰ� ���� �귯�ø� oldBrush�� �����Ѵ�.
	HBRUSH oldBrush = (HBRUSH)SelectObject(m_MemDC, newBrush);

	Rectangle(m_MemDC, 0, 0, MaptoolWidth, MaptoolHeight);
	Rectangle(m_MemDC, 0, 0, GameWidth, GameHeight);

	// m_MemDC�� m_OldBrush�� �����Ѵ�.
	SelectObject(m_MemDC, oldBrush);
}
