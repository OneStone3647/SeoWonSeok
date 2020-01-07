#pragma once
#include <iostream>

using namespace std;

class Weapon
{
public:
	Weapon();
	virtual bool Attack() = 0;
	~Weapon();
};

class Sword : public Weapon
{
public:
	virtual bool Attack();
};

class Bow : public Weapon
{
public:
	virtual bool Attack();
};

class Staff : public Weapon
{
public:
	virtual bool Attack();
};

