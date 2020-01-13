#include "CharacterFactory.h"



CharacterFactory::CharacterFactory()
{
}


CharacterFactory::~CharacterFactory()
{
}

// 팩토리 메서드
Character * CharacterFactory::SpawnCharacter()
{
	m_Character = CreateCharacter();
	m_Character->Initialize();
	return m_Character;
}

Character * KnightFactory::CreateCharacter()
{
	return new Knight(new KnightWeaponFactory);
}

Character * ArcherFactory::CreateCharacter()
{
	return new Archer(new ArcherWeaponFactory);
}

Character * WizardFactory::CreateCharacter()
{
	return new Wizard(new WizardWeaponFactory);
}
