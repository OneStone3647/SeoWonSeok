#pragma once
#include "Mecro.h"

class MainWeapon
{
protected:
	string m_Name;
	int m_Att;

public:
	MainWeapon();
	~MainWeapon();

public:
	void GetMainWeapon();
};

class Sword : public MainWeapon
{
public:
	Sword();
};

class Bow : public MainWeapon
{
public:
	Bow();
};

class Staff : public MainWeapon
{
public:
	Staff();
};

