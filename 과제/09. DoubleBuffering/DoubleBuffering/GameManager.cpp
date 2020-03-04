#include "GameManager.h"



GameManager::GameManager()
{
}

void GameManager::Init(HDC hdc)
{
	m_MainDC = hdc;
	// 숨겨 그릴 장소(도화지)를 준비한다.
	m_MemDC[0] = CreateCompatibleDC(hdc);
	m_NewBitmap[0] = CreateCompatibleBitmap(hdc, 1024, 768);
	m_OldBitmap[0] = (HBITMAP)SelectObject(m_MemDC[0], m_NewBitmap[0]);

	//숨겨 그릴 장소(도화지)에 배경을 그릴 준비를 한다.
	m_MemDC[1] = CreateCompatibleDC(m_MemDC[0]);

	//숨겨 그릴 장소(도화지)에 캐릭터를 그릴 준비를 한다.
	m_MemDC[2] = CreateCompatibleDC(m_MemDC[0]);

	if (m_Back != NULL)
	{
		delete m_Back;
	}
	m_Back = new Back;
	m_Back->Init(m_MemDC[0], m_MemDC[1], &m_NewBitmap[1], &m_OldBitmap[1]);

	if (m_Player != NULL)
	{
		delete m_Player;
	}
	m_Player = new Player;
	m_Player->Init(m_MemDC[0], m_MemDC[2], &m_NewBitmap[2], &m_OldBitmap[2]);
}

void GameManager::Draw()
{
	//숨겨 그릴 장소(도화지)에 배경을 그린다.
	m_Back->Draw(0, 0);

	m_Player->Draw();

	//숨겨 그린 것을 원래 보여야할 hdc에 그린다.
	//단지 hdc에 그림을 덮어 그리는 행위만 하게된다.
	//그리는 행위는 하지만 뒷배경이 공백이 아니고 무언가를 계속 그리기 때문에 그림이 존재해서 그리는 동안 해당 그림을 보여주고 있는 것이라고 생각하면 된다.
	BitBlt(m_MainDC, 0, 0, 1024, 768, m_MemDC[0], 0, 0, SRCCOPY);
}


GameManager::~GameManager()
{
}
