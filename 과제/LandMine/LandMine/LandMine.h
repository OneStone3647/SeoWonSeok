#pragma once
#include <iostream>
#include <list>
#include <time.h>

using namespace std;

struct Point
{
	int X;
	int Y;
};

class LandMine
{
private:
	int Horizon;
	int Vertical;
	int Grid[5][5] = { 0, };
	list<Point> SearchPoint;
	list<Point> LandMinePoint;
	int MaxLandMineCount;
public:
	LandMine();
	~LandMine();

public:
	void DrawMap();
	void SetLandMine();
	bool SamePoint(list<Point>::iterator iter, Point point);
	void SearchLandMine();
};

