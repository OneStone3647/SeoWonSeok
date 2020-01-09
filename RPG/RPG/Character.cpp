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
	cout << "===캐릭터 정보 ===" << endl;
	cout << "캐릭터 이름 : " << m_Name << endl;
	cout << "공격력 : " << m_Att << " 방어력 : " << m_Def << endl;
	cout << "장착한 메인 무기 - ";
	m_MainWeapon->GetMainWeapon();
	cout << endl;
	cout << "장착한 보조 무기 - ";
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
	m_Name = "기사";
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
	m_Name = "궁수";
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
	m_Name = "마법사";
}

void Wizard::Initialize()
{
	m_MainWeapon = m_WeaponFactory->CreateMainWeapon();
	m_SubWeapon = m_WeaponFactory->CreateSubWeapon();
	m_Att = 10;
	m_Def = 5;
}
