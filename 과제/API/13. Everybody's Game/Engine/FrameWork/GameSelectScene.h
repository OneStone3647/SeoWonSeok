#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class GameSelectScene : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_BackBitmap;



public:
	GameSelectScene();
	virtual ~GameSelectScene();

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool LoadColorGame();
	bool LoadFightGame();
	void LoadScore();
};

