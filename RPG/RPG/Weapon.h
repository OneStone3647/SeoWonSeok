#pragma once
#include "Mecro.h"

class Weapon
{
public:
	Weapon();
	virtual bool Attack() = 0;
	virtual ~Weapon();
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

