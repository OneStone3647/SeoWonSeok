#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"


TitleScene::TitleScene()
{
	m_TitleX = WindowX;
	m_TitleY = WindowY;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RETURN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);

	m_TitleBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("Bitmap\\Title.bmp");
	m_TitleBitmap->SetAnchor(JEngine::ANCHOR_LT);

	JEngine::UIManager::GetInstance()->AddLabel("Press Enter", WindowX / 2 - 30, WindowY - 80, DT_CENTER);
}

bool TitleScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyPress(VK_RETURN))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAMESELECT);
	}
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		return true;
	}

	return false;
}

void TitleScene::Update(float fETime)
{

}

void TitleScene::Draw(HDC hdc)
{
	m_TitleBitmap->DrawBitblt(0, 0);
}

void TitleScene::Release()
{

}

bool TitleScene::OnClick()
{
	return true;
}