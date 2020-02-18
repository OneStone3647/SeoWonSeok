#pragma once
#include "Bitmap.h"

class Scene
{
private:
	HWND		m_hWnd;
	HDC			m_TitleDC;
	Bitmap		m_Star[3];
	Bitmap		m_Icon;
	HBITMAP		m_TitleBitmap;
	HBITMAP		m_OldBitmap;

	int			m_CurTimer;
	int			m_LastTimer;
	int			m_DeltaTimer;
	int			m_AnimTimer;

	int			m_StarIndex;

public:
	Scene();
	~Scene();

	void Init(HWND hWnd);
	void Update();
	void Input();
	void DrawStarBox(int start_X, int start_Y, int width, int height);
	void DrawMenu(int start_X, int start_Y);

public:
	inline HDC GetHDC()
	{
		return m_TitleDC;
	}
};

