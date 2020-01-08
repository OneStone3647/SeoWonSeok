#pragma once
#include "Character.h"

class CharacterFactory
{
public:
	CharacterFactory();
	~CharacterFactory();

public:
	virtual Weapon* CreateWeapon() = 0;
	virtual Character* CreateCharacter(string name) = 0;
};

class KnightCharacter : public CharacterFactory
{
public:
	virtual Weapon* CreateWeapon();
	virtual Character* CreateCharacter(string name);
};

class ArcherCharacter : public CharacterFactory
{
public:
	virtual Weapon* CreateWeapon();
	virtual Character* CreateCharacter(string name);
};

class WizardCharacter : public CharacterFactory
{
public:
	virtual Weapon* CreateWeapon();
	virtual Character* CreateCharacter(string name);
};

