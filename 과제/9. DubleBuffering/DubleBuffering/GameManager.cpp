#include "GameManager.h"



GameManager::GameManager()
{
}

void GameManager::Init(HDC hdc)
{
	m_MainDC = hdc;
	// ���� �׸� ���(��ȭ��)�� �غ��Ѵ�.
	m_MemDC[0] = CreateCompatibleDC(hdc);
	m_NewBitmap[0] = CreateCompatibleBitmap(hdc, 1024, 768);
	m_OldBitmap[0] = (HBITMAP)SelectObject(m_MemDC[0], m_NewBitmap[0]);

	//���� �׸� ���(��ȭ��)�� ����� �׸� �غ� �Ѵ�.
	m_MemDC[1] = CreateCompatibleDC(m_MemDC[0]);

	//���� �׸� ���(��ȭ��)�� ĳ���͸� �׸� �غ� �Ѵ�.
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
	//���� �׸� ���(��ȭ��)�� ����� �׸���.
	m_Back->Draw(0, 0);

	m_Player->Draw();

	//���� �׸� ���� ���� �������� hdc�� �׸���.
	//���� hdc�� �׸��� ���� �׸��� ������ �ϰԵȴ�.
	//�׸��� ������ ������ �޹���� ������ �ƴϰ� ���𰡸� ��� �׸��� ������ �׸��� �����ؼ� �׸��� ���� �ش� �׸��� �����ְ� �ִ� ���̶�� �����ϸ� �ȴ�.
	BitBlt(m_MainDC, 0, 0, 1024, 768, m_MemDC[0], 0, 0, SRCCOPY);
}


GameManager::~GameManager()
{
}
