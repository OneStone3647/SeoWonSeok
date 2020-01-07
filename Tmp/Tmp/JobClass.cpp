#include "JobClass.h"



JobClass::JobClass()
{
}


JobClass::~JobClass()
{
}

void JobClass::SetWeapon(Weapon * _weapon)
{
	weapon = _weapon;
}

Weapon * JobClass::GetWeapon()
{
	return weapon;
}

bool Knight::EquipCheck()
{
	Sword* sword = dynamic_cast<Sword*>(GetWeapon());
	if (sword == NULL)
	{
		return false;
	}
	cout << "�� ����!" << endl;
	return sword->Attack();
}

bool Archer::EquipCheck()
{
	Bow* bow = dynamic_cast<Bow*>(GetWeapon());
	if (bow == NULL)
	{
		return false;
	}
	cout << "Ȱ ����!" << endl;
	return bow->Attack();
}

bool Wizard::EquipCheck()
{
	Staff* staff = dynamic_cast<Staff*>(GetWeapon());
	if (staff == NULL)
	{
		return false;
	}
	cout << "������ ����!" << endl;
	return staff->Attack();
}
