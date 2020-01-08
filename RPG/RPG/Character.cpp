#include "Character.h"



Character::Character()
{
}


Character::~Character()
{
}

void Character::ShowCharacterInfo()
{
	cout << "=====info=====" << endl;
	cout << "이름 : " << Name << "\t 직업 : " << Job << endl;
	cout << "Att : " << Att << "\t CurHP / MaxHP : " << CurHP << " / " << MaxHP << endl;
}

void Character::SetWeapon(Weapon * _weapon)
{
	weapon = _weapon;
}

Weapon * Character::GetWeapon()
{
	return weapon;
}

Knight::Knight(string name)
{
	Name = name;
	Job = "기사";
	Att = 5;
	MaxHP = 50;
	CurHP = MaxHP;
}

bool Knight::EquipCheck()
{
	Sword* sword = dynamic_cast<Sword*>(GetWeapon());

	if (sword == NULL)
		return false;

	return sword->Attack();
}

Archer::Archer(string name)
{
	Name = name;
	Job = "궁수";
	Att = 7;
	MaxHP = 40;
	CurHP = MaxHP;
}

bool Archer::EquipCheck()
{
	Bow* bow = dynamic_cast<Bow*>(GetWeapon());

	if (bow == NULL)
		return false;

	return bow->Attack();
}

Wizard::Wizard(string name)
{
	Name = name;
	Job = "마법사";
	Att = 10;
	MaxHP = 30;
	CurHP = MaxHP;
}

bool Wizard::EquipCheck()
{
	Staff* staff = dynamic_cast<Staff*>(GetWeapon());

	if (staff == NULL)
		return false;

	return staff->Attack();
}
