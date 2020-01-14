#include "ObjectManager.h"



ObjectManager::ObjectManager()
{
	BlockShape = "▣";
	BlockListCount = MAXBLOCKCOUNT;
	BlockList.reserve(BlockListCount);

	FoodShape = "♡";
	FoodList = NULL;
	FoodSpawnSpeed = FOODSPAWNSPEED;
	srand((unsigned int)time(NULL));
}


ObjectManager::~ObjectManager()
{
}

void ObjectManager::ObjectInit()
{
	// BlockList 벡터가 비어 있지 않을 경우 초기화
	if (!BlockList.empty())
	{
		BlockList.clear();
	}
	for (vector<int>::size_type i = 0; i < BlockList.size(); ++i)
	{

	}
}

void ObjectManager::SetBlock()
{
}

void ObjectManager::DrawBlock()
{
}

bool ObjectManager::CheckBlock(int x, int y)
{
	return false;
}

void ObjectManager::SetFood(int * foodCount)
{
}

void ObjectManager::DrawFood(int * foodCount)
{
}

bool ObjectManager::CheckFood(int x, int y)
{
	return false;
}

void ObjectManager::EatFood(int x, int y, int * foodCount)
{
}
