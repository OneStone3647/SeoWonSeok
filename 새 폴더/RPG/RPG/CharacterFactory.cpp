#include "CharacterFactory.h"



CharacterFactory::CharacterFactory()
{
}


CharacterFactory::~CharacterFactory()
{
}

Weapon * KnightCharacter::CreateWeapon()
{
	return new Sword();
}

Character * KnightCharacter::CreateCharacter(string name)
{
	return new Knight(name);
}

Weapon * ArcherCharacter::CreateWeapon()
{
	return new Bow();
}

Character * ArcherCharacter::CreateCharacter(string name)
{
	return new Archer(name);
}

Weapon * WizardCharacter::CreateWeapon()
{
	return new Staff();
}

Character * WizardCharacter::CreateCharacter(string name)
{
	return new Wizard(name);
}
