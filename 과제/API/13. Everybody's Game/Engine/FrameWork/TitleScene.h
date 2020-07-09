#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class TitleScene : public JEngine::Scene
{
private:
	JEngine::BitMap*	m_TitleBitmap;

	float				m_TitleX;
	float				m_TitleY;

public:
	TitleScene();
	virtual ~TitleScene();

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnClick();
};

