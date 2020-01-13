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
				cout << "∫Ò±Ë" << endl;
			}
			else if (PlayerSelect > NPCSelect)
			{
				if (NPCSelect == SELECT_SCISSORS && PlayerSelect == SELECT_PAPER)
				{
					cout << "NPC Ω¬!!" << endl;
					m_Player->SetDamage(m_NPC->GetAtt());
				}
				else
				{
					cout << "Player Ω¬!!" << endl;
					m_NPC->SetDamage(m_Player->GetAtt());
				}
			}
			else
			{
				if (PlayerSelect == SELECT_SCISSORS && NPCSelect == SELECT_PAPER)
				{
					cout << "Player Ω¬!!" << endl;
					m_NPC->SetDamage(m_Player->GetAtt());
				}
				else
				{
					cout << "NPC Ω¬!!" << endl;
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
	// √ﬂªÛ ∆—≈‰∏Æ
	CharacterFactory* characterFactory;
	Character* character;
	string tmp;
	int select;
	cout << "«√∑π¿ÃæÓ ¿Ã∏ß ¿‘∑¬ : ";
	cin >> tmp;
	cout << "1.±‚ªÁ 2.±√ºˆ 3.∏∂π˝ªÁ" << endl;
	cout << "¡˜æ˜ º±≈√ : ";
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
	// √ﬂªÛ ∆—≈‰∏Æ
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
		cout << "NPC Ω¬∏Æ!!" << endl;
		system("pause");
		return true;
	}
	else if (npc->GetCurHP() <= 0)
	{
		system("cls");
		cout << "Player Ω¬∏Æ!!" << endl;
		system("pause");
		return true;
	}
	else
	{
		return false;
	}
}
