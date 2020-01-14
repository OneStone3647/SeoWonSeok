#include "GameManager.h"



GameManager::GameManager()
{
	m_Width = WIDTH;
	m_Height = HEIGHT;
	m_bPlayState = false;
	m_bFirstInput = true;
	m_Snake = new Snake;
	m_FoodCount = 0;
	m_FoodCountptr = &m_FoodCount;
}

void GameManager::MainMenu()
{
	while (1)
	{
		m_Score = 0;
		int Height = m_Height / 2;
		system("cls");
		m_DrawManager.DrawBox(m_Width, m_Height);
		m_DrawManager.DrawMidText("Score : " + to_string(m_Score), m_Width, m_Height + 2);
		m_DrawManager.DrawMidText("★ ☆ ★ Snake Game ★ ☆ ★", m_Width, Height - 9);
		m_DrawManager.DrawMidText("1.게임 시작", m_Width, Height - 6);
		m_DrawManager.DrawMidText("2.게임 종료", m_Width, Height - 3);
		m_DrawManager.DrawMidText("선택 : ", m_Width, Height);
		//m_DrawManager.gotoxy(m_Width + 4, Height);
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
	m_FoodCount = 0;
}

void GameManager::Play()
{
	m_bPlayState = true;
	system("cls");
	m_DrawManager.DrawBox(m_Width, m_Height);
	m_DrawManager.DrawMidText("Score : " + to_string(m_Score), m_Width, m_Height + 2);
	m_ObjectManager.SetBlock();
	m_ObjectManager.DrawBlock();
	while (m_bPlayState)
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
	m_DrawManager.DrawMidText("Score : " + to_string(m_Score), m_Width, m_Height + 2);
	m_DrawManager.DrawMidText("★ ☆ ★ Game Over ★ ☆ ★", m_Width, Height);
	m_DrawManager.DrawMidText("Continue : Space Bar", m_Width, Height + 2);
	int select;
	while (1)
	{
		select = getch();
		if (select == KEY_CONTINUE)
		{
			m_bPlayState = false;
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
		// 먹이를 먹을 경우
		if (m_ObjectManager.CheckFood(m_Snake->GetSnakeHead()->m_X, m_Snake->GetSnakeHead()->m_Y))
		{
			m_ObjectManager.EatFood(m_Snake->GetSnakeHead()->m_X, m_Snake->GetSnakeHead()->m_Y, m_FoodCountptr);
			m_Snake->AddTail(m_Snake->GetSnakeHead());
			AddScore();
		}
		// 죽음 체크
		if (m_Snake->CheckIsDead() || m_ObjectManager.CheckBlock(m_Snake->GetSnakeHead()->m_X, m_Snake->GetSnakeHead()->m_Y))
		{
			m_Snake->Release(m_Snake->GetSnakeHead());
			GameOver();
			return;
		}
		m_Snake->Draw();
		// 먹이 생성
		if (m_FoodCount != FOODCOUNT)
		{
			m_ObjectManager.SetFood(m_FoodCountptr);
		}
	}
}

void GameManager::AddScore()
{
	m_Score = m_Snake->GetSnakeTailCount();
	m_DrawManager.DrawMidText("Score : " + to_string(m_Score), m_Width, m_Height + 2);
}


GameManager::~GameManager()
{
	delete m_Snake;
}
