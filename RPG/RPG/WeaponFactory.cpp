#include "WeaponFactory.h"



WeaponFactory::WeaponFactory()
{
}


WeaponFactory::~WeaponFactory()
{
}

MainWeapon * KnightWeaponFactory::CreateMainWeapon()
{
	return new Sword();
}

SubWeapon * KnightWeaponFactory::CreateSubWeapon()
{
	return new Shield();
}

MainWeapon * ArcherWeaponFactory::CreateMainWeapon()
{
	return new Bow();
}

SubWeapon * ArcherWeaponFactory::CreateSubWeapon()
{
	return new Dagger();
}

MainWeapon * WizardWeaponFactory::CreateMainWeapon()
{
	return new Staff();
}

SubWeapon * WizardWeaponFactory::CreateSubWeapon()
{
	return new Glove();
}
