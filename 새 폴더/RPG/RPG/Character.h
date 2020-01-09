#pragma once
#include "Weapon.h"

enum SELECT
{
	SELECT_SCISSORS = 49,
	SELECT_ROCK,
	SELECT_PAPAER
};

enum SELECTJOB
{
	SELECTJOB_KNIGHT = 0,
	SELECTJOB_ARCHER,
	SELECTJOB_WIZARD
};

class Character
{
protected:
	string Name;
	string Job;
	int Att;
	int CurHP;
	int MaxHP;
	Weapon* weapon;
public:
	Character();
	~Character();

public:
	void ShowCharacterInfo();
	void SetWeapon(Weapon* _weapon);
	
public:
	Weapon* GetWeapon();

public:
	virtual bool EquipCheck() = 0;
};

class Knight : public Character
{
public:
	Knight(string name);

public:
	virtual bool EquipCheck();
};

class Archer : public Character
{
public:
	Archer(string name);

public:
	virtual bool EquipCheck();
};

class Wizard : public Character
{
public:
	Wizard(string name);

public:
	virtual bool EquipCheck();
};
