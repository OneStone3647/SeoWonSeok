#include "ColoredPaper.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"
#include "TimeManager.h"



ColoredPaper::ColoredPaper()
{
}


ColoredPaper::~ColoredPaper()
{
}

void ColoredPaper::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);

	m_BackBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\ColoredPaperBack.bmp");

	m_TimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\ColoredPaperTimeBar.bmp");
	m_TimeBar->SetAnchor(JEngine::ANCHOR_CENTER);

	m_ScoreBitmap[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FlightGameStar1.bmp");
	m_ScoreBitmap[0]->SetAnchor(JEngine::ANCHOR_CENTER);
	m_ScoreBitmap[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FlightGameStar2.bmp");
	m_ScoreBitmap[1]->SetAnchor(JEngine::ANCHOR_CENTER);

	m_TimeOverBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\TimeOver.bmp");
	m_TimeOverBitmap->SetAnchor(JEngine::ANCHOR_CENTER);

	m_FeverBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\Fever1.bmp");
	m_FeverBar->SetAnchor(JEngine::ANCHOR_CENTER);

	m_FeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\FeverEffect3.bmp");
	
	m_Score = 0;
	m_bGetScore = false;
	m_bIsFever = false;
	m_FeverStack = 0;
	m_HaveScore = 100;

	ClearPaper(m_Paper);
	while (m_Paper.size() < 2)
	{
		SetPaper(m_Paper);
	}

	m_ElapseTime = 0;
	m_Time = 0;
	m_bIsTimeOver = false;
}

bool ColoredPaper::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAMESELECT);
	}
	else
	{
		if (!m_bIsTimeOver)
		{
			if (JEngine::InputManager::GetInstance()->isKeyDown(VK_UP))
			{
				CheckPaper(m_Paper, COLOR_GREEN);
			}
			else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_DOWN))
			{
				CheckPaper(m_Paper, COLOR_YELLOW);
			}
			else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_RIGHT))
			{
				CheckPaper(m_Paper, COLOR_RED);
			}
			else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_LEFT))
			{
				CheckPaper(m_Paper, COLOR_BLUE);
			}
		}
	}	

	return false;
}

void ColoredPaper::Update(float fETime)
{
	if (fETime)
	{
		m_ElapseTime++;
		m_Time = m_ElapseTime / 100;
	}

	if (m_Time > 19)
	{
		m_bIsTimeOver = true;
		if (m_bIsTimeOver && m_Time > 21)
		{
			SaveScore();
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAMESELECT);
		}
	}

	if (m_bIsFever)
	{
		m_HaveScore = 1400;
	}
	else
	{
		m_HaveScore = 100;
	}
}

void ColoredPaper::Draw(HDC hdc)
{
	m_BackBitmap->DrawBitblt(0, 0);
	DrawScore();
	DrawTimeBar();
	DrawFeverBar();
	m_Paper.back()->GetBitmap()->Draw(160, 300);
	m_Paper.front()->GetBitmap()->Draw(150, 290);

	if (m_bIsFever)
	{
		m_FeverEffect->Draw(0, 0);
	}

	if (m_bGetScore)
	{
		if (m_bIsFever)
		{
			m_ScoreBitmap[1]->Draw(WindowX / 2, WindowY / 2 + 20);
		}
		else
		{
			m_ScoreBitmap[0]->Draw(WindowX / 2, WindowY / 2 + 20);
		}
	}

	if (m_bIsTimeOver)
	{
		m_TimeOverBitmap->Draw(WindowX / 2, WindowY / 2);
	}
}

void ColoredPaper::Release()
{
	JEngine::UIManager::GetInstance()->RelaaseUI();

	ClearPaper(m_Paper);
	while (m_Paper.size() < 2)
	{
		SetPaper(m_Paper);
	}
	m_bIsTimeOver = false;
}

void ColoredPaper::ClearPaper(queue<Paper*>& targetQueue)
{
	// queue √ ±‚»≠
	if (!targetQueue.empty())
	{
		queue<Paper*> tmpQueue;
		swap(targetQueue, tmpQueue);
	}
}

void ColoredPaper::SetPaper(queue<Paper*>& targetQueue)
{
	// ∑£¥˝ «‘ºˆ∞° æ»µ ;;
	//srand((unsigned int)time(NULL));
	//int random = rand() % 4;

	int random = GetTickCount() % 4;

	Paper* tmpPaper = new Paper;
	tmpPaper->Init(random);
	m_Paper.push(tmpPaper);
}

void ColoredPaper::CheckPaper(queue<Paper*>& targetQueue, COLOR color)
{
	if (targetQueue.front()->GetColor() == color)
	{
		m_Score += m_HaveScore;
		if (!m_bIsFever)
		{
			m_FeverStack++;
		}
		if (m_FeverStack >= 10)
		{
			m_bIsFever = true;
		}
		m_bGetScore = true;
		JEngine::UIManager::GetInstance()->RelaaseUI();
		SAFE_DELETE(m_Paper.front());
		m_Paper.pop();
		SetPaper(m_Paper);
	}
	else
	{
		m_Score -= m_HaveScore;
		if (m_Score < 0)
		{
			m_Score = 0;
		}

		if (m_bIsFever)
		{
			m_FeverStack = 0;
			m_bIsFever = false;
		}

		if (m_FeverStack > 0)
		{
			m_FeverStack--;
		}
		m_ElapseTime += 100;
		m_bGetScore = false;
		JEngine::UIManager::GetInstance()->RelaaseUI();
	}
}

void ColoredPaper::DrawScore()
{
	JEngine::UIManager::GetInstance()->AddLabel(to_string(m_Score), WindowX / 2, 20, DT_CENTER);
}

void ColoredPaper::DrawTimeBar()
{
	float percent = (20 - m_Time) * 0.05f;
	
	m_TimeBar->Draw(WindowX / 2, WindowY - 14, percent);
}

void ColoredPaper::DrawFeverBar()
{
	float percent = m_FeverStack * 0.1f;

	m_FeverBar->Draw(WindowX / 2, 66, percent);
}

void ColoredPaper::SaveScore()
{
	int LoadScore = 0;
	HANDLE hFile = CreateFile(TEXT("ColoredPaperScore.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &LoadScore, sizeof(int), &dwRead, NULL);
		CloseHandle(hFile);
	}

	if (m_Score > LoadScore)
	{
		hFile = CreateFile(TEXT("ColoredPaperScore.txt"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		WriteFile(hFile, &m_Score, sizeof(int), &dwRead, NULL);
		CloseHandle(hFile);
	}
}
