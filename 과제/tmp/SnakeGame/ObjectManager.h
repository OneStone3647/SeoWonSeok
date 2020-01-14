#pragma once
#include "DrawManager.h"
#include <cstdlib> // 난수생성

#define BLOCKCOUNT 30
#define FOODCOUNT 10
#define DEFAULTHEADX 25
#define DEFAULTHEADY 15
#define FOODSPWANSPEED 1500

struct ObjectPoint
{
	int m_X;
	int m_Y;
};

class ObjectManager
{
private:
	DrawManager m_DrawManager;
	ObjectPoint* m_BlockList;
	ObjectPoint* m_FoodList;
	int m_BlockListCount;
	int m_FoodListCount;
	string m_BlockShape;
	string m_FoodShape;
	int m_CurClock;
	int m_FoodClock;
	int m_FoodSpawnSpeed;
public:
	ObjectManager();
	void ObjectInit();
	void SetBlock();
	void DrawBlock();
	bool CheckBlock(int x, int y);
	void SetFood(int* foodCount);
	void DrawFood(int* foodCount);
	bool CheckFood(int x, int y);
	void EatFood(int x, int y, int* foodCount);
	inline int GetBlockListCount()
	{
		return m_BlockListCount;
	}
	inline int GetFoodListCount()
	{
		return m_FoodListCount;
	}
	~ObjectManager();
};

