#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

bool Sword::Attack()
{
	cout << "��!" << endl << endl;
	return true;
}

bool Bow::Attack()
{
	cout << "����~" << endl << endl;
	return true;
}

bool Staff::Attack()
{
	cout << "�Ҷ��~" << endl << endl;
	return false;
}
