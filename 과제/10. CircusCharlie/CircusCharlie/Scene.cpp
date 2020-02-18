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
	//�� �����Ӹ��� ������ TickCount�� �޴´�. -  ������ ƽī��带 �޾ƿ´�.
	m_CurTimer = GetTickCount();

	//���� �ð��� �����Ѵ�. ��ƾ�� ���ư� �� ���� ��ƾ������ ƽ ī��Ʈ���� ���̸� üũ�ϱ� ���ؼ� �̴�.
	//1000 �̻��� ���̰� ���� 1���̹Ƿ�  / 1000�ؼ� �ʷ� ȯ��.
	m_DeltaTimer = (m_CurTimer - m_LastTimer) / 1000.0f;

	//���� Ÿ���� �޴´�.
	//��������� ���� Ÿ���� �ð��� �޴°�.
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
		// ���� ��
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
		// ���� ��
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
