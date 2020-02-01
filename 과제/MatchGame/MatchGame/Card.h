#pragma once
#include <iostream>
#include <Windows.h>
#include "resource.h"

class Card
{
private:
	HDC			MemDC;
	HBITMAP		m_NewCard;
	HBITMAP		m_OldCard;
	SIZE			m_Size;			// ũ�� ����ü

public:
	Card();

	void Init(HDC hdc, HINSTANCE hInst, int id);						// �ʱ�ȭ
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);		// �׸���(4, 5��° ���ڴ� scale�� ��Ÿ��)
	SIZE GetCardSize();

	~Card();
};

