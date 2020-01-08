#pragma once
#include "Mecro.h"
#include "Character.h"

class Weapon
{
public:
	Weapon();
	virtual void ActiveSkill(Character* caster, Character* target) = 0;
	~Weapon();
};

class Sword : public Weapon
{
public:
	virtual bool ActiveSkill(Character* caster, Character target) = 0;
};

class Bow : public Weapon
{

};

class Staff : public Weapon
{

};

