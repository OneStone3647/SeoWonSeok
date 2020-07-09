#include "GameSelectScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"
#include "TimeManager.h"



GameSelectScene::GameSelectScene()
{
}


GameSelectScene::~GameSelectScene()
{
}

void GameSelectScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);

	m_BackBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\GameSelect.bmp");

	JEngine::UIManager::GetInstance()->AddButton(320, 166, "Bitmap\\OnSelect.bmp", std::bind(&GameSelectScene::LoadColorGame, this));
	JEngine::UIManager::GetInstance()->AddButton(320, 248, "Bitmap\\OnSelect.bmp", std::bind(&GameSelectScene::LoadFightGame, this));

	LoadScore();
}

bool GameSelectScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		return true;
	}

	return false;
}

void GameSelectScene::Update(float fETime)
{
}

void GameSelectScene::Draw(HDC hdc)
{
	m_BackBitmap->DrawBitblt(0, 0);
}

void GameSelectScene::Release()
{
}

bool GameSelectScene::LoadColorGame()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_IDNEX_COLOREDPAPER);
	JEngine::TimeManager::GetInstance()->init(false, 30);
	return true;
}

bool GameSelectScene::LoadFightGame()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_FIGHTGAME);
	JEngine::TimeManager::GetInstance()->init(false, 30);
	return true;
}

void GameSelectScene::LoadScore()
{
	int ColoredPaperScore = 0;
	int FightGameScore = 0;

	string ColoredStr;
	string FightStr;

	HANDLE hFile = CreateFile(TEXT("ColoredPaperScore.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwRead;
	if (hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &ColoredPaperScore, sizeof(int), &dwRead, NULL);
		CloseHandle(hFile);
	}
	if (ColoredPaperScore == 0)
	{
		ColoredStr = "점수없음";
		JEngine::UIManager::GetInstance()->AddLabel(ColoredStr, 200, 200, DT_CENTER);
	}
	else
	{
		JEngine::UIManager::GetInstance()->AddLabel(to_string(ColoredPaperScore), 200, 200, DT_CENTER);
	}

	hFile = CreateFile(TEXT("FightGameScore.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &FightGameScore, sizeof(int), &dwRead, NULL);
		CloseHandle(hFile);
	}
	if (FightGameScore == 0)
	{
		FightStr = "점수없음";
		JEngine::UIManager::GetInstance()->AddLabel(FightStr, 200, 282, DT_CENTER);
	}
	else
	{
		JEngine::UIManager::GetInstance()->AddLabel(to_string(FightGameScore), 200, 282, DT_CENTER);
	}
	
}
