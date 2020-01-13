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
	cout << "캐릭터 이름 : " << m_Name << "CurHP / MaxHP : " << m_CurHP << " / " << m_MaxHP << endl;
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
	cout << "1.가위 2.바위 3.보" << endl;
	cout << "선택: ";
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
	m_Name = "기사";
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
	m_Name = "궁수";
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
	m_Name = "마법사";
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
