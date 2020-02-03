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
	SIZE			m_Size;			// 크기 구조체

public:
	Card();

	void Init(HDC hdc, HINSTANCE hInst, int id);						// 초기화
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);		// 그리기(4, 5번째 인자는 scale을 나타냄)
	SIZE GetCardSize();

	~Card();
};

