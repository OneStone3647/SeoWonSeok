#include "Board.h"



Board::Board()
{
	m_BoardX = BOARD_X;
	m_BoardY = BOARD_Y;
}


Board::~Board()
{
	Release();
}

void Board::Init(HDC MemDC)
{
	InitBoard(MemDC);
}

void Board::Release()
{
	// Block Ŭ���� ������ ������ ���� �Ҵ��� �����մϴ�.
	if (!m_Board.empty())
	{
		vector<vector<Block*>>::iterator iterY;
		vector<Block*>::iterator iterX;
		for (iterY = m_Board.begin(); iterY != m_Board.end(); iterY++)
		{
			for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
			{
				delete (*iterX);
			}
			iterY->clear();
			// swap���� capacity�� 0���� ����� �ݴϴ�.
			vector<Block*>().swap(*iterY);
		}
		m_Board.clear();
		// swap�� capacity�� 0���� ����� �ݴϴ�.
		vector<vector<Block*>>().swap(m_Board);
	}
}

void Board::InitBoard(HDC MemDC)
{
	// Block Ŭ���� ������ ���Ͱ� �̹� ������ ��� �Ҵ� �����մϴ�.
	Release();

	// Block Ŭ���� ������ ���͸� ���� �Ҵ��մϴ�.
	// ������ ���� ���� �޸� ũ�⸦ �����մϴ�.
	m_Board.reserve(m_BoardY);
	for (int y = 0; y < m_BoardY; y++)
	{
		vector<Block*> tmpBlockY;
		// ������ ���� ���� �޸� ũ�⸦ �����մϴ�.
		tmpBlockY.reserve(m_BoardX);
		for (int x = 0; x < m_BoardX; x++)
		{
			Block* tmpBlock = new Block;
			if (y % 2 == 0)
			{
				if (x % 2 == 0)
				{
					tmpBlock->Init(MemDC, BLOKCTYPE_BLOCK01, BLOCKBIT_X * x, BLOCKBIT_Y * y);
				}
				else
				{
					tmpBlock->Init(MemDC, BLOCKTYPE_BLOCK02, BLOCKBIT_X * x, BLOCKBIT_Y * y);
				}
			}
			else
			{
				if (x % 2 == 0)
				{
					tmpBlock->Init(MemDC, BLOCKTYPE_BLOCK02, BLOCKBIT_X * x, BLOCKBIT_Y * y);
				}
				else
				{
					tmpBlock->Init(MemDC, BLOKCTYPE_BLOCK01, BLOCKBIT_X * x, BLOCKBIT_Y * y);
				}
			}
			tmpBlockY.push_back(tmpBlock);
		}
		m_Board.push_back(tmpBlockY);
	}
}

void Board::DrawBoard()
{
	vector<vector<Block*>>::iterator iterY;
	vector<Block*>::iterator iterX;
	for (iterY = m_Board.begin(); iterY != m_Board.end(); iterY++)
	{
		for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
		{
			(*iterX)->Draw();
		}
	}
}
