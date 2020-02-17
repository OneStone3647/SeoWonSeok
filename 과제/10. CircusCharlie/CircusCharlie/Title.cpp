#include "Title.h"



Title::Title()
{
}


Title::~Title()
{
}

void Title::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	HDC hdc = GetDC(hWnd);

	m_TitleDC = CreateCompatibleDC(hdc);
	m_TitleBitmap = CreateCompatibleBitmap(hdc, 1024, 768);
	m_OldBitmap = (HBITMAP)SelectObject(m_TitleDC, m_TitleBitmap);

	m_Star[0].Init(m_TitleDC, "Bitmap\\star.bmp");
	m_Star[1].Init(m_TitleDC, "Bitmap\\star1.bmp");
	m_Star[2].Init(m_TitleDC, "Bitmap\\star2.bmp");
}

void Title::Update()
{
}

void Title::Input()
{
}

void Title::Draw()
{
}
