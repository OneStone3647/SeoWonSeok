#include "CharacterFactory.h"



CharacterFactory::CharacterFactory()
{
}


CharacterFactory::~CharacterFactory()
{
	jobs.clear();
	weapons.clear();
}

void CharacterFactory::Addjob(JobClass * job)
{
	jobs.push_back(job);
}

void CharacterFactory::AddWeapon(Weapon * weapon)
{
	weapons.push_back(weapon);
}

Weapon * KnightCharacter::CreateWeapon()
{
	return new Sword();
}

JobClass * KnightCharacter::CreateJobClass()
{
	return new Knight();
}

Weapon * ArcherCharacter::CreateWeapon()
{
	return new Bow();
}

JobClass * ArcherCharacter::CreateJobClass()
{
	return new Archer();
}

Weapon * WizardCharacter::CreateWeapon()
{
	return new Staff();
}

JobClass * WizardCharacter::CreateJobClass()
{
	return new Wizard;
}
