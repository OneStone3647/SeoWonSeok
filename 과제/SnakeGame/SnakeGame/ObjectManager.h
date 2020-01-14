#pragma once
#include "DrawManager.h"
#include <cstdlib>		// 난수 생성

#define MAXBLOCKCOUNT 30
#define MAXFOODCOUNT 10
#define DEFAULTHEADX 25
#define DEFUALTDEADY 15
#define FOODSPAWNSPEED 1500

struct ObjectPoint
{
	int X;
	int Y;
};

class ObjectManager
{
private:
	DrawManager DrawManager;
	vector<ObjectPoint> BlockList;
	ObjectPoint* FoodList;
	int BlockListCount;
	int FoodListCount;
	string BlockShape;
	string FoodShape;
	int CurClock;
	int FoodClock;
	int FoodSpawnSpeed;

public:
	ObjectManager();
	~ObjectManager();

public:
	void ObjectInit();

public:
	void SetBlock();					// 벽 설정
	void DrawBlock();
	bool CheckBlock(int x, int y);		// 벽이 존재하는지 체크

public:
	void SetFood(int* foodCount);		// 음식 설정
	void DrawFood(int* foodCount);
	bool CheckFood(int x, int y);		// 음식이 존재하는지 체크
	void EatFood(int x, int y, int *foodCount);
	
public:
	inline int GetBlockListCount()
	{
		return BlockListCount;
	}
	inline int GetFoodListCount()
	{
		return FoodListCount;
	}
};

