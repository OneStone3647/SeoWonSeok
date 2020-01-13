#pragma once
#include"Character.h"

class CharacterFactory
{
public:
	Character* m_Character;

public:
	CharacterFactory();
	~CharacterFactory();

public:
	virtual Character* SpawnCharacter();

public:
	virtual Character* CreateCharacter() = 0;
};

class KnightFactory : public CharacterFactory
{
public:
	Character* CreateCharacter();
};

class ArcherFactory : public CharacterFactory
{
public:
	Character* CreateCharacter();
};

class WizardFactory : public CharacterFactory
{
public:
	Character* CreateCharacter();
};

