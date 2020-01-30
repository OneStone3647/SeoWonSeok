#pragma once
#include <iostream>
#include <Windows.h>
#include "resource.h"

class CardManager
{
	// ΩÃ±€≈Ê
private:
	static CardManager* m_CManager;
public:
	static CardManager* GetInstance()
	{
		if (m_CManager == NULL)
		{
			m_CManager = new CardManager;
		}
		return m_CManager;
	}

	static void DestroyInstance()
	{
		if (m_CManager)
		{
			delete m_CManager;
			m_CManager = NULL;
		}
	}
private:
	int Card_X;
	int Card_Y;
	int Card_Width;
	int Card_Height;
public:
	CardManager();
	~CardManager();
	void DrawCard(HINSTANCE g_hInst, HDC hdc, HDC CardDC);
	void CheckCard(HWND hWnd, int Mouse_X, int Mouse_Y);
};

