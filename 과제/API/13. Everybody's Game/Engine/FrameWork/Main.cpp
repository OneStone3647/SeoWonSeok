#include <Windows.h>
#include "EngineMain.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameSelectScene.h"
#include "ColoredPaper.h"
#include "FightGame.h"
#include "defines.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//���� ��ü�� �����ϰ� Ÿ��Ʋ�� ������ ����� �־��ش�.
	JEngine::EngineMain engine("Everybody's Game", WindowX, WindowY);
	//���� ����Ѵ�. ù��° ����ϴ� ���� �ʱ�ȭ���� �ȴ�.
	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new GameSelectScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new ColoredPaper);
	JEngine::SceneManager::GetInstance()->RegistScene(new FightGame);

	//���� ����
	return engine.StartEngine(hInstance);
}