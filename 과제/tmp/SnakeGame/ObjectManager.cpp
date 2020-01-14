#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	m_BlockShape = "▣";
	m_FoodShape = "♡";
	m_BlockList = NULL;
	m_FoodList = NULL;
	m_BlockListCount = BLOCKCOUNT;
	m_FoodListCount = FOODCOUNT;
	srand((unsigned int)time(0));
	m_FoodSpawnSpeed = FOODSPWANSPEED;
}

void ObjectManager::ObjectInit()
{
	if (m_BlockList != NULL)
	{
		delete[] m_BlockList;
	}
	m_BlockList = new ObjectPoint[m_BlockListCount];
	for (int i = 0; i < m_BlockListCount; i++)
	{
		m_BlockList[i].m_X = NULL;
		m_BlockList[i].m_Y = NULL;
	}

	if (m_FoodList != NULL)
	{
		delete[] m_FoodList;
	}
	m_FoodList = new ObjectPoint[m_FoodListCount];
	for (int i = 0; i < m_FoodListCount; i++)
	{
		m_FoodList[i].m_X = NULL;
		m_FoodList[i].m_Y = NULL;
	}
}

void ObjectManager::SetBlock()
{
	int BlockCount = 0;
	bool bFlag = true;
	while (bFlag)
	{
		int RandomX = (rand() % (WIDTH - 2)) + 1;
		int RandomY = (rand() % (HEIGHT - 2)) + 1;
		for (int i = 0; i < m_BlockListCount; i++)
		{
			// 블록 중복 및 초기 뱀머리 위치 체크
			if (!CheckBlock(RandomX, RandomY) && (RandomX != DEFAULTHEADX && RandomY != DEFAULTHEADY))
			{
				// 먹이 배열에 자리가 비었으면 추가
				if (m_BlockList[i].m_X == NULL && m_BlockList[i].m_Y == NULL)
				{
					m_BlockList[i].m_X = RandomX;
					m_BlockList[i].m_Y = RandomY;
					BlockCount++;
					break;
				}
			}
		}
		if (BlockCount == BLOCKCOUNT)
		{
			bFlag = false;
		}
	}
}

void ObjectManager::DrawBlock()
{
	for (int i = 0; i < m_BlockListCount; i++)
	{
		m_DrawManager.DrawPoint(m_BlockShape, m_BlockList[i].m_X, m_BlockList[i].m_Y);
	}
}

bool ObjectManager::CheckBlock(int x, int y)
{
	for (int i = 0; i < m_BlockListCount; i++)
	{
		if (m_BlockList[i].m_X == x && m_BlockList[i].m_Y == y)
		{
			return true;
		}
	}
	return false;
}

void ObjectManager::SetFood(int * foodCount)
{
	bool bFlag = true;
	m_CurClock = clock();
	if (m_CurClock - m_FoodClock >= m_FoodSpawnSpeed)
	{
		while (bFlag)
		{
			int RandomX = (rand() % (WIDTH - 2)) + 1;
			int RandomY = (rand() % (HEIGHT - 2)) + 1;
			for (int i = 0; i < m_FoodListCount; i++)
			{
				// 먹이 중복, 블록 중복 및 초기 뱀머리 위치 체크
				if (!CheckFood(RandomX, RandomY) && !CheckBlock(RandomX, RandomY) && (RandomX != DEFAULTHEADX && RandomY != DEFAULTHEADY))
				{
					// 먹이 배열에 자리가 비었으면 추가
					if (m_FoodList[i].m_X == NULL && m_FoodList[i].m_Y == NULL)
					{
						m_FoodList[i].m_X = RandomX;
						m_FoodList[i].m_Y = RandomY;
						*foodCount += 1;
						bFlag = false;
						break;
					}
				}
			}
		}
		DrawFood(foodCount);
	}
	
}

void ObjectManager::DrawFood(int * foodCount)
{
	int FoodCount = 0;
	for (int i = 0; i < m_FoodListCount; i++)
	{
		if (m_FoodList[i].m_X != NULL && m_FoodList[i].m_Y != NULL)
		{
			m_DrawManager.DrawPoint(m_FoodShape, m_FoodList[i].m_X, m_FoodList[i].m_Y);
			FoodCount++;
			if (*foodCount == FoodCount)
			{
				break;
			}
		}
	}
}

bool ObjectManager::CheckFood(int x, int y)
{
	for (int i = 0; i < m_FoodListCount; i++)
	{
		if (m_FoodList[i].m_X == x && m_FoodList[i].m_Y == y)
		{
			return true;
		}
	}
	return false;
}

void ObjectManager::EatFood(int x, int y, int * foodCount)
{
	for (int i = 0; i < m_FoodListCount; i++)
	{
		if (m_FoodList[i].m_X == x && m_FoodList[i].m_Y == y)
		{
			m_FoodList[i].m_X = NULL;
			m_FoodList[i].m_Y = NULL;
			*foodCount -= 1;
		}
	}
}


ObjectManager::~ObjectManager()
{
	delete[] m_BlockList;
	delete[] m_FoodList;
}
