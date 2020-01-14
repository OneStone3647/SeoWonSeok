#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	BlockShape = "��";
	BlockListCount = MAXBLOCKCOUNT;
	BlockList.reserve(BlockListCount);			// vector ��� �޸� ����

	FoodShape = "��";
	FoodListCount = MAXFOODCOUNT;
	FoodList = NULL;
	FoodSpawnSpeed = FOODSPAWNSPEED;
	srand((unsigned int)time(NULL));
}


ObjectManager::~ObjectManager()
{
	// swap�� ����� vector �޸� ����
	vector<ObjectPoint>().swap(BlockList);
	delete FoodList;
}

void ObjectManager::ObjectInit()
{
	// BlockList ���Ͱ� ��� ���� ���� ��� �ʱ�ȭ
	if (!BlockList.empty())
	{
		BlockList.clear();
	}

	if (FoodList != NULL)
	{
		delete[] FoodList;
	}
	FoodList = new ObjectPoint[FoodListCount];
	for (int i = 0; i < FoodListCount; i++)
	{
		FoodList[i].X = NULL;
		FoodList[i].Y = NULL;
	}
}

void ObjectManager::SetBlock()
{
	bool bFlag = true;
	while (bFlag)
	{
		int RandomX = (rand() % (WIDTH - 2)) + 1;
		int RandomY = (rand() % (HEIGHT - 2)) + 1;
		// ��� �ߺ� �� �ʱ� ��Ӹ� ��ġ üũ
		if (!CheckBlock(RandomX, RandomY) && (RandomX != DEFAULTHEADX && RandomY != DEFAULTHEADY))
		{
			ObjectPoint tmp;
			tmp.X = RandomX;
			tmp.Y = RandomY;
			// ó�� ����� ��ǥ�� ���� ���
			if (BlockList.size() == 0)
			{
				BlockList.push_back(tmp);
			}
			else
			{
				// ����� �ߺ����� ������ ���Ϳ� �߰�
				for (vector<ObjectPoint>::size_type i = 0; i < BlockList.size(); ++i)
				{
					if (!(BlockList[i].X == tmp.X && BlockList[i].Y == tmp.Y))
					{
						ObjectPoint tmp;
						tmp.X = RandomX;
						tmp.Y = RandomY;
						BlockList.push_back(tmp);
						break;
					}
				}
			}
		}
		if (BlockList.size() == MAXBLOCKCOUNT)
		{
			bFlag = false;
		}
	}
}

void ObjectManager::DrawBlock()
{
	for (vector<ObjectPoint>::size_type i = 0; i < BlockList.size(); ++i)
	{
		m_DrawManager.DrawPoint(BlockShape, BlockList[i].X, BlockList[i].Y);
	}
}

bool ObjectManager::CheckBlock(int x, int y)
{
	for (vector<ObjectPoint>::size_type i = 0; i < BlockList.size(); ++i)
	{
		if (BlockList[i].X == x && BlockList[i].Y == y)
		{
			return true;
		}
	}
	return false;
}

void ObjectManager::SetFood(int * foodCount)
{
	bool bFlag = true;
	CurClock = clock();
	if (CurClock - FoodClock >= FoodSpawnSpeed)
	{
		while (bFlag)
		{
			int RandomX = (rand() % (WIDTH - 2)) + 1;
			int RandomY = (rand() % (HEIGHT - 2)) + 1;
			for (int i = 0; i < FoodListCount; i++)
			{
				// ���� �ߺ�, ��� �ߺ� �� �ʱ� ��Ӹ� ��ġ üũ
				if (!CheckFood(RandomX, RandomY) && !CheckBlock(RandomX, RandomY) && (RandomX != DEFAULTHEADX && RandomY != DEFAULTHEADY))
				{
					// ���� �迭�� �ڸ��� ������� �߰�
					if (FoodList[i].X == NULL && FoodList[i].Y == NULL)
					{
						FoodList[i].X = RandomX;
						FoodList[i].Y = RandomY;
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
	for (int i = 0; i < FoodListCount; i++)
	{
		if (FoodList[i].X != NULL && FoodList[i].Y != NULL)
		{
			m_DrawManager.DrawPoint(FoodShape, FoodList[i].X, FoodList[i].Y);
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
	for (int i = 0; i < FoodListCount; i++)
	{
		if (FoodList[i].X == x && FoodList[i].Y == y)
		{
			return true;
		}
	}
	return false;
}

void ObjectManager::EatFood(int x, int y, int * foodCount)
{
	for (int i = 0; i < FoodListCount; i++)
	{
		if (FoodList[i].X == x && FoodList[i].Y == y)
		{
			FoodList[i].X = NULL;
			FoodList[i].Y = NULL;
			*foodCount -= 1;
		}
	}
}
