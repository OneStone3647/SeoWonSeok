#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	BlockShape = "▣";
	BlockListCount = MAXBLOCKCOUNT;
	BlockList.reserve(BlockListCount);			// vector 사용 메모리 예약

	FoodShape = "♡";
	FoodListCount = MAXFOODCOUNT;
	FoodList = NULL;
	FoodSpawnSpeed = FOODSPAWNSPEED;
	srand((unsigned int)time(NULL));
}


ObjectManager::~ObjectManager()
{
	// swap을 사용한 vector 메모리 해제
	vector<ObjectPoint>().swap(BlockList);
	delete FoodList;
}

void ObjectManager::ObjectInit()
{
	// BlockList 벡터가 비어 있지 않을 경우 초기화
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
		// 블록 중복 및 초기 뱀머리 위치 체크
		if (!CheckBlock(RandomX, RandomY) && (RandomX != DEFAULTHEADX && RandomY != DEFAULTHEADY))
		{
			ObjectPoint tmp;
			tmp.X = RandomX;
			tmp.Y = RandomY;
			// 처음 블록의 좌표를 넣을 경우
			if (BlockList.size() == 0)
			{
				BlockList.push_back(tmp);
			}
			else
			{
				// 블록이 중복되지 않으면 벡터에 추가
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
				// 먹이 중복, 블록 중복 및 초기 뱀머리 위치 체크
				if (!CheckFood(RandomX, RandomY) && !CheckBlock(RandomX, RandomY) && (RandomX != DEFAULTHEADX && RandomY != DEFAULTHEADY))
				{
					// 먹이 배열에 자리가 비었으면 추가
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
