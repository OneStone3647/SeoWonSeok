#pragma once
#include "DrawManager.h"
#include <cstdlib>		// ���� ����

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
	void SetBlock();					// �� ����
	void DrawBlock();
	bool CheckBlock(int x, int y);		// ���� �����ϴ��� üũ

public:
	void SetFood(int* foodCount);		// ���� ����
	void DrawFood(int* foodCount);
	bool CheckFood(int x, int y);		// ������ �����ϴ��� üũ
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

