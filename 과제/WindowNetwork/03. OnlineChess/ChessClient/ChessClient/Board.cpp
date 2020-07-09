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
	// Block 클래스 이차원 벡터의 동적 할당을 해제합니다.
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
			// swap으로 capacity를 0으로 만들어 줍니다.
			vector<Block*>().swap(*iterY);
		}
		m_Board.clear();
		// swap을 capacity를 0으로 만들어 줍니다.
		vector<vector<Block*>>().swap(m_Board);
	}
}

void Board::InitBoard(HDC MemDC)
{
	// Block 클래스 이차원 벡터가 이미 존재할 경우 할당 해제합니다.
	Release();

	// Block 클래스 이차원 벡터를 동적 할당합니다.
	// 이차원 벡터 열의 메모리 크기를 설정합니다.
	m_Board.reserve(m_BoardY);
	for (int y = 0; y < m_BoardY; y++)
	{
		vector<Block*> tmpBlockY;
		// 이차원 벡터 행의 메모리 크기를 설정합니다.
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
