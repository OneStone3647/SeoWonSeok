#include "GameManager.h"



GameManager::GameManager()
{
	m_Width = WIDTH;
	m_Height = HEIGHT;
	bPlayState = false;
	bFirstInput = true;
	m_Snake = new Snake;
	FoodCount = 0;
	FoodCountptr = &FoodCount;
}

void GameManager::MainMenu()
{
	while (1)
	{
		Score = 0;
		int Height = m_Height / 2;
		system("cls");
		m_DrawManager.DrawBox(m_Width, m_Height);
		m_DrawManager.DrawMidText("Score : " + to_string(Score), m_Width, m_Height + 2);
		m_DrawManager.DrawMidText("�� �� �� Snake Game �� �� ��", m_Width, Height - 9);
		m_DrawManager.DrawMidText("1.���� ����", m_Width, Height - 6);
		m_DrawManager.DrawMidText("2.���� ����", m_Width, Height - 3);
		m_DrawManager.DrawMidText("���� : ", m_Width, Height);
		int select;
		cin >> select;
		switch (select)
		{
		case MAINMENU_PLAY:
			Init();
			Play();
			break;
		case MAINMENU_END:
			return;
		}
	}
}

void GameManager::Init()
{
	m_Snake->SetSnake(m_Width, m_Height);
	m_ObjectManager.ObjectInit();
	FoodCount = 0;
}

void GameManager::Play()
{
	bPlayState = true;
	system("cls");
	m_DrawManager.DrawBox(m_Width, m_Height);
	m_DrawManager.DrawMidText("Score : " + to_string(Score), m_Width, m_Height + 2);
	m_ObjectManager.SetBlock();
	m_ObjectManager.DrawBlock();
	while (bPlayState)
	{
		m_Snake->DrawSnake(m_Snake->GetSnakeHead());
		Input();
	}
}

void GameManager::GameOver()
{
	int Height = m_Height / 2;
	system("cls");
	m_DrawManager.DrawBox(m_Width, m_Height);
	m_DrawManager.DrawMidText("Score : " + to_string(Score), m_Width, m_Height + 2);
	m_DrawManager.DrawMidText("�� �� �� Game Over �� �� ��", m_Width, Height);
	m_DrawManager.DrawMidText("Continue : Space Bar", m_Width, Height + 2);
	int select;
	while (1)
	{
		select = getch();
		if (select == KEY_CONTINUE)
		{
			bPlayState = false;
			break;
		}
	}
}

void GameManager::Input()
{
	Point SnakeHead;
	char key = NULL;
	char tmp = NULL;
	while (1)
	{
		m_Snake->Input();
		m_Snake->Move(m_Width, m_Height);
		// ���̸� ���� ���
		if (m_ObjectManager.CheckFood(m_Snake->GetSnakeHead()->X, m_Snake->GetSnakeHead()->Y))
		{
			m_ObjectManager.EatFood(m_Snake->GetSnakeHead()->X, m_Snake->GetSnakeHead()->Y, FoodCountptr);
			m_Snake->AddTail(m_Snake->GetSnakeHead());
			AddScore();
		}
		// ���� üũ
		if (m_Snake->CheckIsDead() || m_ObjectManager.CheckBlock(m_Snake->GetSnakeHead()->X, m_Snake->GetSnakeHead()->Y))
		{
			m_Snake->Release(m_Snake->GetSnakeHead());
			GameOver();
			return;
		}
		m_Snake->Draw();
		// ���� ����
		if (FoodCount != MAXFOODCOUNT)
		{
			m_ObjectManager.SetFood(FoodCountptr);
		}
	}
}

void GameManager::AddScore()
{
	Score = m_Snake->GetSnakeTailCount();
	m_DrawManager.DrawMidText("Score : " + to_string(Score), m_Width, m_Height + 2);
}


GameManager::~GameManager()
{
	delete m_Snake;
}
