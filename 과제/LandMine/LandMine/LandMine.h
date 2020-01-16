#pragma once
#include <iostream>
#include <list>
#include <time.h>

using namespace std;

class LandMine
{
private:
	int Horizon;
	int Vertical;
	list<char> Map;
	int LandMineCount;
public:
	LandMine();
	~LandMine();

public:
	void SetMap();
	void SetLandMine();
};

