#include "GameManager.h"



GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}

void GameManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(hWnd);
	// hdc�� ȣȯ�Ǵ� DC�� �����.
	m_MemDC = CreateCompatibleDC(hdc);
	// hdc�� ȣȯ�Ǵ� ��Ʈ���� �� ScreenWidth, ���� ScreenHeight�� ũ��� �����.
	m_NewBitmap = CreateCompatibleBitmap(hdc, ScreenWidth, ScreenHeight);
	// m_MemDC�� m_NewBitmap�� �����ϰ� ���� ��Ʈ���� m_OldBitmap�� �����Ѵ�.
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_NewBitmap);

	// ����� DC�� ���� �Ѵ�.
	ReleaseDC(hWnd, hdc);

	// ��� ��Ʈ�� �ʱ�ȭ
	m_Back.Init(m_MemDC, "Bitmap\\back.bmp");

	// ��� Ŭ���� �ʱ�ȭ
	m_Block.Init(m_MemDC);
}

void GameManager::Release()
{
	// m_MemDC�� ���� ��Ʈ���� �����Ѵ�.
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_NewBitmap);
	// CreateCompatibleDC�� ����� �� DC�� DeleteDC�� �������Ѵ�.
	DeleteDC(m_MemDC);
}

void GameManager::Update(LPARAM lParam)
{
	int startX = BlockStartX16;
	int startY = BlockStartY16;

	m_Back.Draw(m_MemDC, 0, 0, ScreenWidth30, ScreenHeight30);

	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			m_Block.DrawBlock(BLOCKINDEX_BLANK, x * BlockSize + startX, y * BlockSize + startY, BlockSize, BlockSize);
		}
	}


	// GetDC�� ���� DC�� �޴´�.
	HDC hdc = GetDC(m_hWnd);
	// ���� �׸� ���� ���� �������� hdc�� �׸���.
	BitBlt(hdc, 0, 0, ScreenWidth, ScreenHeight, m_MemDC, 0, 0, SRCCOPY);
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::InitBlock()
{
}
