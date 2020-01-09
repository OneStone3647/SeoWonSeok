#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Update()
{
	while (true)
	{
		if (CheckWinner(m_Player, m_NPC))
		{
			return;
		}
		char PlayerSelect;
		char NPCSelect;
		system("cls");
		m_Player->GetCharacterInfo();
		cout << "===================" << endl;
		m_NPC->GetCharacterInfo();
		cout << endl << endl;
		PlayerSelect = m_Player->PlayerSelect();
		NPCSelect = m_NPC->NPCSelect();

		if (PlayerSelect == SELECT_SCISSORS || PlayerSelect == SELECT_ROCK || PlayerSelect == SELECT_PAPER)
		{
			if (PlayerSelect == NPCSelect)
			{
				cout << "���" << endl;
			}
			else if (PlayerSelect > NPCSelect)
			{
				if (NPCSelect == SELECT_SCISSORS && PlayerSelect == SELECT_PAPER)
				{
					cout << "NPC ��!!" << endl;
					m_Player->SetDamage(m_NPC->GetAtt());
				}
				else
				{
					cout << "Player ��!!" << endl;
					m_NPC->SetDamage(m_Player->GetAtt());
				}
			}
			else
			{
				if (PlayerSelect == SELECT_SCISSORS && NPCSelect == SELECT_PAPER)
				{
					cout << "Player ��!!" << endl;
					m_NPC->SetDamage(m_Player->GetAtt());
				}
				else
				{
					cout << "NPC ��!!" << endl;
					m_Player->SetDamage(m_NPC->GetAtt());
				}
			}
		}
		system("pause");
	}
}

void GameManager::Finish()
{
	if (m_Player != NULL)
	{
		delete m_Player;
	}
	if (m_NPC != NULL)
	{
		delete m_NPC;
	}
}

void GameManager::Init()
{
	m_Player = SetPlayer();
	m_NPC = SetNPC();
}

Character * GameManager::SetPlayer()
{
	// �߻� ���丮
	CharacterFactory* characterFactory;
	Character* character;
	string tmp;
	int select;
	cout << "�÷��̾� �̸� �Է� : ";
	cin >> tmp;
	cout << "1.��� 2.�ü� 3.������" << endl;
	cout << "���� ���� : ";
	cin >> select;
	switch (select)
	{
	case 1:
		characterFactory = new KnightFactory;
		break;
	case 2:
		characterFactory = new ArcherFactory;
		break;
	case 3:
		characterFactory = new WizardFactory;
		break;
	}
	character = characterFactory->SpawnCharacter();
	delete characterFactory;
	return character;
}

Character * GameManager::SetNPC()
{
	// �߻� ���丮
	CharacterFactory* characterFactory;
	Character* character;
	int select;
	srand((unsigned int)time(NULL));
	select = (rand() % 3) + 1;
	switch (select)
	{
	case 1:
		characterFactory = new KnightFactory;
		break;
	case 2:
		characterFactory = new ArcherFactory;
		break;
	case 3:
		characterFactory = new WizardFactory;
		break;
	}
	character = characterFactory->SpawnCharacter();
	delete characterFactory;
	return character;
}

bool GameManager::CheckWinner(Character* player, Character* npc)
{
	if (player->GetCurHP() <= 0)
	{
		system("cls");
		cout << "NPC �¸�!!" << endl;
		system("pause");
		return true;
	}
	else if (npc->GetCurHP() <= 0)
	{
		system("cls");
		cout << "Player �¸�!!" << endl;
		system("pause");
		return true;
	}
	else
	{
		return false;
	}
}
