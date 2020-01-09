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
		m_NPC->GetCharacterInfo();
		cout << endl << endl;
		cout << "1.°¡À§ 2.¹ÙÀ§ 3.º¸" << endl;
		cout << "¼±ÅÃ: ";
		cin >> PlayerSelect;
		NPCSelect = SelectNPC();

		if (PlayerSelect == SELECT_SCISSORS || PlayerSelect == SELECT_ROCK || PlayerSelect == SELECT_PAPER)
		{
			if (PlayerSelect == NPCSelect)
			{
				cout << "ºñ±è" << endl;
			}
			else if (PlayerSelect > NPCSelect)
			{
				if (NPCSelect == SELECT_SCISSORS && PlayerSelect == SELECT_PAPER)
				{
					cout << "NPC ½Â!!" << endl;
					m_Player->SetDamage(m_NPC->GetAtt());
				}
				else
				{
					cout << "Player ½Â!!" << endl;
					m_NPC->SetDamage(m_Player->GetAtt());
				}
			}
			else
			{
				if (PlayerSelect == SELECT_SCISSORS && NPCSelect == SELECT_PAPER)
				{
					cout << "Player ½Â!!" << endl;
					m_NPC->SetDamage(m_Player->GetAtt());
				}
				else
				{
					cout << "NPC ½Â!!" << endl;
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
	CharacterFactory* characterFactory;
	Character* character;
	string tmp;
	int select;
	cout << "ÇÃ·¹ÀÌ¾î ÀÌ¸§ ÀÔ·Â : ";
	cin >> tmp;
	cout << "1.±â»ç 2.±Ã¼ö 3.¸¶¹ý»ç" << endl;
	cout << "Á÷¾÷ ¼±ÅÃ : ";
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
	return character;
}

Character * GameManager::SetNPC()
{
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
	return character;
}

char GameManager::SelectNPC()
{
	srand((unsigned int)time(NULL));
	return (rand() % 3) + 49;
}

bool GameManager::CheckWinner(Character* player, Character* npc)
{
	if (player->GetCurHP() <= 0)
	{
		system("cls");
		cout << "NPC ½Â¸®!!" << endl;
		system("pause");
		return true;
	}
	else if (npc->GetCurHP() <= 0)
	{
		system("cls");
		cout << "Player ½Â¸®!!" << endl;
		system("pause");
		return true;
	}
	else
	{
		return false;
	}
}
