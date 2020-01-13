#include "Character.h"



Character::Character()
{
}


Character::~Character()
{
	delete m_MainWeapon;
	delete m_SubWeapon;
}

void Character::GetCharacterInfo()
{
	cout << "===ĳ���� ���� ===" << endl;
	cout << "ĳ���� �̸� : " << m_Name << "CurHP / MaxHP : " << m_CurHP << " / " << m_MaxHP << endl;
	cout << "���ݷ� : " << m_Att << " ���� : " << m_Def << endl;
	cout << "������ ���� ���� - ";
	m_MainWeapon->GetMainWeapon();
	cout << endl;
	cout << "������ ���� ���� - ";
	m_SubWeapon->GetSubWeapon();
	cout << endl;
}

void Character::GetMainWeapon()
{
	m_MainWeapon->GetMainWeapon();
}

void Character::GetSubWeapon()
{
	m_SubWeapon->GetSubWeapon();
}

void Character::SetDamage(int damage)
{
	m_CurHP -= damage;
}

int Character::GetAtt()
{
	return m_Att;
}

int Character::GetCurHP()
{
	return m_CurHP;
}

char Character::PlayerSelect()
{
	char select;
	cout << "1.���� 2.���� 3.��" << endl;
	cout << "����: ";
	cin >> select;
	return select;
}

char Character::NPCSelect()
{
	srand((unsigned int)time(NULL));
	return (rand() % 3) + 49;
}

Knight::Knight(WeaponFactory * m_WeaponFactory)
{
	this->m_WeaponFactory = m_WeaponFactory;
	m_Name = "���";
}

void Knight::Initialize()
{
	m_MainWeapon = m_WeaponFactory->CreateMainWeapon();
	m_SubWeapon = m_WeaponFactory->CreateSubWeapon();
	m_Att = 5;
	m_Def = 10;
	m_MaxHP = 50;
	m_CurHP = m_MaxHP;
	delete m_WeaponFactory;
}

Archer::Archer(WeaponFactory * m_WeaponFactory)
{
	this->m_WeaponFactory = m_WeaponFactory;
	m_Name = "�ü�";
}

void Archer::Initialize()
{
	m_MainWeapon = m_WeaponFactory->CreateMainWeapon();
	m_SubWeapon = m_WeaponFactory->CreateSubWeapon();
	m_Att = 7;
	m_Def = 7;
	m_MaxHP = 40;
	m_CurHP = m_MaxHP;
	delete m_WeaponFactory;
}

Wizard::Wizard(WeaponFactory * m_WeaponFactory)
{
	this->m_WeaponFactory = m_WeaponFactory;
	m_Name = "������";
}

void Wizard::Initialize()
{
	m_MainWeapon = m_WeaponFactory->CreateMainWeapon();
	m_SubWeapon = m_WeaponFactory->CreateSubWeapon();
	m_Att = 10;
	m_Def = 5;
	m_MaxHP = 30;
	m_CurHP = m_MaxHP;
	delete m_WeaponFactory;
}
