#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Initialized()
{
	if (m_Player != NULL)
	{
		delete m_Player;
	}
	if (m_NPC != NULL)
	{
		delete m_NPC;
	}
	// 팩토리 매서드
	m_Player = m_Creator->CreateCharater(SELECTCHARACTER_PLAYER);
	m_NPC = m_Creator->CreateCharater(SELECTCHARACTER_NPC);
}

void GameManager::Update()
{
	while (true)
	{
		system("cls");
		int select;
		m_Player->ShowCharacterInfo();
		cout << "========================" << endl;
		m_NPC->ShowCharacterInfo();
		cout << endl << endl;
		cout << "1.가위 2.바위 3. 보" << endl;
		cout << "선택 : ";
		cin >> select;
		system("pause");
	}
}

void GameManager::Finishied()
{

}

Character * Creator::CreateCharater(SELECTCHARACTER select)
{
	KnightCharacter* knightFactory = new KnightCharacter();
	ArcherCharacter* archerFactory = new ArcherCharacter();
	WizardCharacter* wizardFactory = new WizardCharacter();

	Weapon* sword = knightFactory->CreateWeapon();
	Weapon* bow = archerFactory->CreateWeapon();
	Weapon* staff = wizardFactory->CreateWeapon();

	Character* character;
	string name;

	// 플레이어 생성
	if (select == SELECTCHARACTER_PLAYER)
	{
		int select;
		cout << "플레이어 이름 입력 : ";
		cin >> name;
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업 선택 : ";
		cin >> select;

		switch (select)
		{
		case SELECTJOB_KNIGHT:
			character = knightFactory->CreateCharacter(name);
			character->SetWeapon(sword);
			break;
		case SELECTJOB_ARCHER:
			character = archerFactory->CreateCharacter(name);
			character->SetWeapon(bow);
			break;
		case SELECTJOB_WIZARD:
			character = wizardFactory->CreateCharacter(name);
			character->SetWeapon(staff);
			break;
		}
	}
	// NPC 생성
	else if (select == SELECTCHARACTER_NPC)
	{
		int select;

		srand((unsigned int)time(NULL));
		select = rand() % 3;

		switch (select)
		{
		case SELECTJOB_KNIGHT:
			name = "떠돌이 기사";
			character = knightFactory->CreateCharacter(name);
			character->SetWeapon(sword);
			break;
		case SELECTJOB_ARCHER:
			name = "떠돌이 궁수";
			character = archerFactory->CreateCharacter(name);
			character->SetWeapon(bow);
			break;
		case SELECTJOB_WIZARD:
			name = "떠돌이 마법사";
			character = wizardFactory->CreateCharacter(name);
			character->SetWeapon(staff);
			break;
		}
	}
	return character;
}
