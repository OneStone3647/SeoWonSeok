#pragma once
#include "Mecro.h"

enum SELECT
{
	SELECT_SCISSORS = 49,
	SELECT_ROCK,
	SELECT_PAPAER
};

class Character
{
private:
	string Name;
	string Job;
	int Level;
	int Att;
	int CurHP;
	int MaxHP;
	int CurExp;
	int MaxExp;
public:
	Character();
	~Character();

public:
	void SetPlayerInfo();
};

