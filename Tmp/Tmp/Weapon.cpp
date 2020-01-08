#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

bool Sword::Attack()
{
	cout << "´ó°­!" << endl << endl;
	return true;
}

bool Bow::Attack()
{
	cout << "ÇÇÀ¶~" << endl << endl;
	return true;
}

bool Staff::Attack()
{
	cout << "ÃÒ¶ó¶û~" << endl << endl;
	return false;
}
