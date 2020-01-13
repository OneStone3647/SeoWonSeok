#pragma once
#include "MainWeapon.h"
#include "SubWeapon.h"

class WeaponFactory
{
public:
	WeaponFactory();
	~WeaponFactory();

public:
	virtual MainWeapon* CreateMainWeapon() = 0;
	virtual SubWeapon* CreateSubWeapon() = 0;
};

class KnightWeaponFactory : public WeaponFactory
{
public:
	MainWeapon* CreateMainWeapon();
	SubWeapon* CreateSubWeapon();
};

class ArcherWeaponFactory : public WeaponFactory
{
public:
	MainWeapon* CreateMainWeapon();
	SubWeapon* CreateSubWeapon();
};

class WizardWeaponFactory : public WeaponFactory
{
public:
	MainWeapon* CreateMainWeapon();
	SubWeapon* CreateSubWeapon();
};

