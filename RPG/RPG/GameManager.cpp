#include "GameManager.h"



GameManager::GameManager()
{
	Player = NULL;
	NPC = NULL;
}


GameManager::~GameManager()
{
}

void GameManager::Initialized()
{
	if (Player != NULL)
	{
		delete Player;
	}
	if (NPC != NULL)
	{
		delete NPC;
	}
	Player = CreateCharater(SELECTCHARACTER_PLAYER);
	NPC = CreateCharater(SELECTCHARACTER_NPC);
}

void GameManager::Update()
{
	while (true)
	{
		system("cls");
		int select;
		Player->ShowCharacterInfo();
		cout << "========================" << endl;
		NPC->ShowCharacterInfo();
		cout << endl << endl;
		cout << "1.���� 2.���� 3. ��" << endl;
		cout << "���� : ";
		cin >> select;
		system("pause");
	}
}

void GameManager::Finishied()
{

}

Character * Game::CreateCharater(SELECTCHARACTER select)
{
	KnightCharacter* knightFactory = new KnightCharacter();
	ArcherCharacter* archerFactory = new ArcherCharacter();
	WizardCharacter* wizardFactory = new WizardCharacter();

	Weapon* sword = knightFactory->CreateWeapon();
	Weapon* bow = archerFactory->CreateWeapon();
	Weapon* staff = wizardFactory->CreateWeapon();

	Character* character;
	string name;

	// �÷��̾� ����
	if (select == SELECTCHARACTER_PLAYER)
	{
		int select;
		cout << "�÷��̾� �̸� �Է� : ";
		cin >> name;
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "���� ���� : ";
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
	// NPC ����
	else if (select == SELECTCHARACTER_NPC)
	{
		int select;

		srand((unsigned int)time(NULL));
		select = rand() % 3;

		switch (select)
		{
		case SELECTJOB_KNIGHT:
			name = "������ ���";
			character = knightFactory->CreateCharacter(name);
			character->SetWeapon(sword);
			break;
		case SELECTJOB_ARCHER:
			name = "������ �ü�";
			character = archerFactory->CreateCharacter(name);
			character->SetWeapon(bow);
			break;
		case SELECTJOB_WIZARD:
			name = "������ ������";
			character = wizardFactory->CreateCharacter(name);
			character->SetWeapon(staff);
			break;
		}
	}
	return character;
}
