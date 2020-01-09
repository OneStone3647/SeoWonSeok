#pragma once
#include "Mecro.h"

class SubWeapon
{
protected:
	string m_Name;
	int m_Def;

public:
	SubWeapon();
	~SubWeapon();

public:
	void GetSubWeapon();
};

class Shield : public SubWeapon
{
public:
	Shield();
};

class Dagger : public SubWeapon
{
public:
	Dagger();
};

class Glove : public SubWeapon
{
public:
	Glove();
};

