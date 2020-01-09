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
	cout << "ĳ���� �̸� : " << m_Name << endl;
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
}
