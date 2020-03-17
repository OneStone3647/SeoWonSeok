#include "BlockManager.h"



BlockManager::BlockManager()
{
}


BlockManager::~BlockManager()
{
}

void BlockManager::Init(HDC MemDC, int MapSizeX, int MapSizeY, int BlockStartX, int BlockStartY)
{
	m_MemDC = MemDC;

	m_MapX = MapSizeX;
	m_MapY = MapSizeY;
	m_BlockStartX = BlockStartX;
	m_BlockStartY = BlockStartY;

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
	m_Block.reserve(m_MapY);
	for (int y = 0; y < m_MapY; y++)
	{
		vector<Block*> tmpBlock;
		// 이차원 백터 행의 메모리 크기 설정
		tmpBlock.reserve(m_MapX);
		for (int x = 0; x < m_MapX; x++)
		{
			Safe* tmpSafe = new Safe;
			tmpSafe->Init(m_MemDC, x, y, m_BlockStartX, m_BlockStartY);
			tmpBlock.push_back(tmpSafe);
		}
		m_Block.push_back(tmpBlock);
	}

	//m_Block[BLOCKINDEX_BLANK].Init(m_MemDC, "Bitmap\\block.bmp");
	//m_Block[BLOCKINDEX_0].Init(m_MemDC, "Bitmap\\block_0.bmp");
	//m_Block[BLOCKINDEX_1].Init(m_MemDC, "Bitmap\\block_1.bmp");
	//m_Block[BLOCKINDEX_2].Init(m_MemDC, "Bitmap\\block_2.bmp");
	//m_Block[BLOCKINDEX_3].Init(m_MemDC, "Bitmap\\block_3.bmp");
	//m_Block[BLOCKINDEX_4].Init(m_MemDC, "Bitmap\\block_4.bmp");
	//m_Block[BLOCKINDEX_5].Init(m_MemDC, "Bitmap\\block_5.bmp");
	//m_Block[BLOCKINDEX_6].Init(m_MemDC, "Bitmap\\block_6.bmp");
	//m_Block[BLOCKINDEX_7].Init(m_MemDC, "Bitmap\\block_7.bmp");
	//m_Block[BLOCKINDEX_8].Init(m_MemDC, "Bitmap\\block_8.bmp");
	//m_Block[BLOCKINDEX_FLAG].Init(m_MemDC, "Bitmap\\flag.bmp");
	//m_Block[BLOCKINDEX_MINE].Init(m_MemDC, "Bitmap\\mine.bmp");
}

void BlockManager::DrawAllBlock()
{
	vector<vector<Block*>>::iterator iterY;
	vector<Block*>::iterator iterX;
	for (iterY = m_Block.begin(); iterY != m_Block.end(); iterY++)
	{
		for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
		{
			(*iterX)->DrawBlock();
		}
	}
}
