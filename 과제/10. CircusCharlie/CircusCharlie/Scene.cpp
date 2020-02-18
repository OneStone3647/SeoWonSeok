#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	HDC hdc = GetDC(hWnd);

	m_TitleDC = CreateCompatibleDC(hdc);
	m_TitleBitmap = CreateCompatibleBitmap(hdc, 1024, 768);
	m_OldBitmap = (HBITMAP)SelectObject(m_TitleDC, m_TitleBitmap);

	m_Star[0].Init(m_TitleDC, "Bitmap\\star.bmp");
	m_Star[1].Init(m_TitleDC, "Bitmap\\star1.bmp");
	m_Star[2].Init(m_TitleDC, "Bitmap\\star2.bmp");

	m_CurTimer = 0;
	m_LastTimer = 0;
	m_DeltaTimer = 0;
	m_AnimTimer = 0;

	m_StarIndex = 0;

	ReleaseDC(hWnd, hdc);
}

void Scene::Update()
{
	//매 프레임마다 찍히는 TickCount를 받는다. -  현제의 틱카운드를 받아온다.
	m_CurTimer = GetTickCount();

	//현재 시간을 저장한다. 루틴이 돌아간 후 이전 루틴에서의 틱 카운트간의 차이를 체크하기 위해서 이다.
	//1000 이상의 차이가 나면 1초이므로  / 1000해서 초로 환산.
	m_DeltaTimer = (m_CurTimer - m_LastTimer) / 1000.0f;

	//현재 타임을 받는다.
	//결론적으로 이전 타임의 시간을 받는것.
	m_LastTimer = m_CurTimer;

	m_AnimTimer += m_DeltaTimer;
	if (m_AnimTimer > 1.0f)
	{
		m_AnimTimer = 0.0f;
		m_StarIndex++;
		if (m_StarIndex == 3)
		{
			m_StarIndex = 0;
		}
	}

	DrawStarBox(500, 200, 40, 10);

	Input();
}

void Scene::Input()
{
}

void Scene::DrawStarBox(int start_X, int start_Y, int width, int height)
{
	HDC hdc = GetDC(m_hWnd);
	SIZE BitmapSize = m_Star[0].GetSize();

	for (int y = 0; y < height; y++)
	{
		// 가로 줄
		if (y == 0 || y == height - 1)
		{
			for (int x = 0; x < width; x++)
			{
				if (x % 3 == 0)
				{
					m_Star[m_StarIndex].Draw(hdc, start_X + (x * BitmapSize.cx), start_Y + (y * BitmapSize.cy));
				}
				else if (x % 3 == 1)
				{
					m_Star[m_StarIndex].Draw(hdc, start_X + (x * BitmapSize.cx), start_Y + (y * BitmapSize.cy));
				}
				else if (x % 3 == 2)
				{
					m_Star[m_StarIndex].Draw(hdc, start_X + (x * BitmapSize.cx), start_Y + (y * BitmapSize.cy));
				}
			}
		}
		// 세로 줄
		else
		{
			for (int x = 0; x < width; x++)
			{
				if (x == 0 || x == width - 1)
				{
					if (y % 3 == 0)
					{
						m_Star[m_StarIndex].Draw(hdc, start_X + (x * BitmapSize.cx), start_Y + (y * BitmapSize.cy));
					}
					else if (y % 3 == 1)
					{
						m_Star[m_StarIndex].Draw(hdc, start_X + (x * BitmapSize.cx), start_Y + (y * BitmapSize.cy));
					}
					else if (y % 3 == 2)
					{
						m_Star[m_StarIndex].Draw(hdc, start_X + (x * BitmapSize.cx), start_Y + (y * BitmapSize.cy));
					}
				}
			}
		}
	}
}

void Scene::DrawMenu(int start_X, int start_Y)
{

}
