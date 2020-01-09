#pragma once
#include "WeaponFactory.h"

class Character
{
protected:
	string m_Name;
	int m_Att;
	int m_Def;
	int m_CurHP;
	int m_MaxHP;
	MainWeapon* m_MainWeapon;
	SubWeapon* m_SubWeapon;

public:
	Character();
	~Character();

public:
	void GetCharacterInfo();
	void GetMainWeapon();
	void GetSubWeapon();
	void SetDamage(int damage);
	int GetAtt();
	int GetCurHP();

public:
	virtual void Initialize() = 0;
};

class Knight : public Character
{
public:
	WeaponFactory* m_WeaponFactory;

public:
	Knight(WeaponFactory* m_WeaponFactory);

public:
	void Initialize();
};

class Archer : public Character
{
public:
	WeaponFactory* m_WeaponFactory;

public:
	Archer(WeaponFactory* m_WeaponFactory);

public:
	void Initialize();
};

class Wizard : public Character
{
public:
	WeaponFactory* m_WeaponFactory;

public:
	Wizard(WeaponFactory* m_WeaponFactory);

public:
	void Initialize();
};

