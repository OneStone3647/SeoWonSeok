#include "BlockManager.h"



BlockManager::BlockManager()
{
}


BlockManager::~BlockManager()
{
}

void BlockManager::Init(HDC MemDC, int MapSizeX, int MapSizeY, int BlockStartX, int BlockStartY, int MineCount)
{
	m_MemDC = MemDC;

	m_MapX = MapSizeX;
	m_MapY = MapSizeY;
	m_BlockStartX = BlockStartX;
	m_BlockStartY = BlockStartY;

	m_MineCount = MineCount;

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
			SafeBlock* tmpSafeBlock = new SafeBlock;
			tmpSafeBlock->Init(m_MemDC, x, y, m_BlockStartX, m_BlockStartY);
			tmpBlock.push_back(tmpSafeBlock);
		}
		m_Block.push_back(tmpBlock);
	}

	SetMine();
	SetNumberBlock();

	m_FlagCount = 0;

	m_DrawAll = false;
}

void BlockManager::Release()
{
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

// 블록 주변의 지뢰 개수 확인
void BlockManager::CheckMine(int x, int y)
{
	// 왼쪽 위 대각선 블록
	if (x - 1 >= 0 && y - 1 >= 0)
	{
		if (m_Block[y - 1][x - 1]->GetBlockType() == BLOCK_MINE)
		{
			m_Block[y][x]->IncreaseMineCount();
		}
	}
	// 왼쪽 블록
	if (x - 1 >= 0)
	{
		if (m_Block[y][x - 1]->GetBlockType() == BLOCK_MINE)
		{
			m_Block[y][x]->IncreaseMineCount();
		}
	}
	// 왼쪽 아래 대각선 블록
	if (y + 1 < m_MapY && x - 1 >= 0)
	{
		if (m_Block[y + 1][x - 1]->GetBlockType() == BLOCK_MINE)
		{
			m_Block[y][x]->IncreaseMineCount();
		}
	}
	// 위쪽 블록
	if (y - 1 >= 0)
	{
		if (m_Block[y - 1][x]->GetBlockType() == BLOCK_MINE)
		{
			m_Block[y][x]->IncreaseMineCount();
		}
	}
	// 아래쪽 블록
	if (y + 1 < m_MapY)
	{
		if (m_Block[y + 1][x]->GetBlockType() == BLOCK_MINE)
		{
			m_Block[y][x]->IncreaseMineCount();
		}
	}
	// 오른쪽 위 대각선 블록
	if (y - 1 >= 0 && x + 1 < m_MapX)
	{
		if (m_Block[y - 1][x + 1]->GetBlockType() == BLOCK_MINE)
		{
			m_Block[y][x]->IncreaseMineCount();
		}
	}
	// 오른쪽 블록
	if (x + 1 < m_MapX)
	{
		if (m_Block[y][x + 1]->GetBlockType() == BLOCK_MINE)
		{
			m_Block[y][x]->IncreaseMineCount();
		}
	}
	// 오른쪽 아래 대각선 블록
	if (x + 1 < m_MapX && y + 1 < m_MapY)
	{
		if (m_Block[y + 1][x + 1]->GetBlockType() == BLOCK_MINE)
		{
			m_Block[y][x]->IncreaseMineCount();
		}
	}
}

// 지뢰 생성
void BlockManager::SetMine()
{
	int tmpMineCount = 0;
	while (true)
	{
		int tmpX = rand() % m_MapX;
		int tmpY = rand() % m_MapY;
		if (m_Block[tmpY][tmpX]->GetBlockType() != BLOCK_MINE)
		{
			delete m_Block[tmpY][tmpX];
			MineBlock* tmpMine = new MineBlock;
			tmpMine->Init(m_MemDC, tmpX, tmpY, m_BlockStartX, m_BlockStartY);
			m_Block[tmpY][tmpX] = tmpMine;
			tmpMineCount++;
		}

		if (m_MineCount == tmpMineCount)
		{
			return;
		}
	}
}

// 숫자 블록 생성
void BlockManager::SetNumberBlock()
{
	for (int y = 0; y < m_MapY; y++)
	{
		for (int x = 0; x < m_MapX; x++)
		{
			if (m_Block[y][x]->GetBlockType() != BLOCK_MINE)
			{
				CheckMine(x, y);
				m_Block[y][x]->SetNumberBlock();
			}
		}
	}
}

// 모든 블록을 그린다.
void BlockManager::DrawAllBlock()
{
	vector<vector<Block*>>::iterator iterY;
	vector<Block*>::iterator iterX;
	for (iterY = m_Block.begin(); iterY != m_Block.end(); iterY++)
	{
		for (iterX = iterY->begin(); iterX != iterY->end(); iterX++)
		{
			(*iterX)->Draw();
		}
	}

	m_DrawAll = true;
}

void BlockManager::Update(MOUSECLICK PlayerClick, POINT MousePoint, bool * bGameStart, bool * bGameOver)
{
	int tmpFlagCount = 0;
	int tmpOpenCount = 0;

	for (int y = 0; y < m_MapY; y++)
	{
		for (int x = 0; x < m_MapX; x++)
		{
			if ((PlayerClick == MOUSECLICK_LEFT && PtInRect(&m_Block[y][x]->GetCollision(), MousePoint)) && m_Block[y][x]->GetFlag() != true)
			{
				*bGameStart = true;

				m_Block[y][x]->IsOpen();
				if (m_Block[y][x]->GetBlockType() == BLOCK_SAFE)
				{
					OpenBlock(x, y);
				}
				else if (m_Block[y][x]->GetBlockType() == BLOCK_MINE)
				{
					*bGameOver = true;
				}
			}
			else if (PlayerClick == MOUSECLICK_RIGHT && PtInRect(&m_Block[y][x]->GetCollision(), MousePoint) && m_Block[y][x]->GetOpen() != true)
			{
				*bGameStart = true;

				if (m_Block[y][x]->GetFlag())
				{
					m_Block[y][x]->SetFlag(false);
				}
				else
				{
					m_Block[y][x]->SetFlag(true);
				}
			}

			if (*bGameOver)
			{
				if (m_Block[y][x]->GetBlockType() == BLOCK_MINE && m_Block[y][x]->GetFlag() != true)
				{
					m_Block[y][x]->IsOpen();
				}
			}

			if (m_Block[y][x]->GetFlag())
			{
				tmpFlagCount++;
			}

			if (m_Block[y][x]->GetBlockType() == BLOCK_SAFE && m_Block[y][x]->GetOpen())
			{
				tmpOpenCount++;
			}
		}
	}

	m_FlagCount = tmpFlagCount;
	m_OpenCount = tmpOpenCount;
}

// 주변에 열 수 있는 블록들을 연다.
void BlockManager::OpenBlock(int x, int y)
{
	if (m_Block[y][x]->GetBlockType() == BLOCK_SAFE)
	{
		m_Block[y][x]->IsOpen();
	}

	// 왼쪽 위 대각선 블록
	if (y - 1 >= 0 && x - 1 >= 0)
	{
		if (m_Block[y - 1][x - 1]->GetOpen() != true && m_Block[y - 1][x - 1]->GetBlockType() == BLOCK_SAFE)
		{
			m_Block[y - 1][x - 1]->IsOpen();

			if (m_Block[y - 1][x - 1]->GetMineCount() == 0)
			{
				OpenBlock(x - 1, y - 1);
			}
		}
	}
	// 왼쪽 블록
	if (x - 1 >= 0)
	{
		if (m_Block[y][x - 1]->GetOpen() != true && m_Block[y][x - 1]->GetBlockType() == BLOCK_SAFE)
		{
			m_Block[y][x - 1]->IsOpen();

			if (m_Block[y][x - 1]->GetMineCount() == 0)
			{
				OpenBlock(x - 1, y);
			}
		}
	}
	// 왼쪽 아래 대각선 블록
	if (y + 1 < m_MapY && x - 1 >= 0)
	{
		if (m_Block[y + 1][x - 1]->GetOpen() != true && m_Block[y + 1][x - 1]->GetBlockType() == BLOCK_SAFE)
		{
			m_Block[y + 1][x - 1]->IsOpen();

			if (m_Block[y + 1][x - 1]->GetMineCount() == 0)
			{
				OpenBlock(x - 1, y + 1);
			}
		}
	}
	// 위 블록
	if (y - 1 >= 0)
	{
		if (m_Block[y - 1][x]->GetOpen() != true && m_Block[y - 1][x]->GetBlockType() == BLOCK_SAFE)
		{
			m_Block[y - 1][x]->IsOpen();

			if (m_Block[y - 1][x]->GetMineCount() == 0)
			{
				OpenBlock(x, y - 1);
			}
		}
	}
	// 아래 블록
	if (y + 1 < m_MapY)
	{
		if (m_Block[y + 1][x]->GetOpen() != true && m_Block[y + 1][x]->GetBlockType() == BLOCK_SAFE)
		{
			m_Block[y + 1][x]->IsOpen();

			if (m_Block[y + 1][x]->GetMineCount() == 0)
			{
				OpenBlock(x, y + 1);
			}
		}
	}
	// 오른쪽 위 대각선 블록
	if (y - 1 >= 0 && x + 1 < m_MapX)
	{
		if (m_Block[y - 1][x + 1]->GetOpen() != true && m_Block[y - 1][x + 1]->GetBlockType() == BLOCK_SAFE)
		{
			m_Block[y - 1][x + 1]->IsOpen();

			if (m_Block[y - 1][x + 1]->GetMineCount() == 0)
			{
				OpenBlock(x + 1, y - 1);
			}
		}
	}
	// 오른쪽 블록
	if (x + 1 < m_MapX)
	{
		if (m_Block[y][x + 1]->GetOpen() != true && m_Block[y][x + 1]->GetBlockType() == BLOCK_SAFE)
		{
			m_Block[y][x + 1]->IsOpen();

			if (m_Block[y][x + 1]->GetMineCount() == 0)
			{
				OpenBlock(x + 1, y);
			}
		}
	}
	// 오른쪽 아래 대각선 블록
	if (x + 1 < m_MapX && y + 1 < m_MapY)
	{
		if (m_Block[y + 1][x + 1]->GetOpen() != true && m_Block[y + 1][x + 1]->GetBlockType() == BLOCK_SAFE)
		{
			m_Block[y + 1][x + 1]->IsOpen();

			if (m_Block[y + 1][x + 1]->GetMineCount() == 0)
			{
				OpenBlock(x + 1, y + 1);
			}
		}
	}
}
