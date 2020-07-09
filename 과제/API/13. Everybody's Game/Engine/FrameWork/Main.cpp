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
	//엔진 객체를 생성하고 타이틀과 윈도우 사이즈를 넣어준다.
	JEngine::EngineMain engine("Everybody's Game", WindowX, WindowY);
	//씬을 등록한다. 첫번째 등록하는 씬이 초기화면이 된다.
	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new GameSelectScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new ColoredPaper);
	JEngine::SceneManager::GetInstance()->RegistScene(new FightGame);

	//엔진 시작
	return engine.StartEngine(hInstance);
}