#pragma once
#include <Windows.h>

enum CHARACTERPOSITION
{
	CHARACTERPOSITION_DOWN = 0,
	CHARACTERPOSITION_UP,
	CHARACTERPOSITION_LEFT,
	CHARACTERPOSITION_RIGHT
};

class Player
{
private:
	static Player* m_This;

public:
	static Player* GetInstance()
	{
		if (m_This == NULL)
		{
			m_This = new Player;
		}
		return m_This;
	}

private:
	HWND m_hWnd;
	WPARAM m_wParam;
	int m_X;
	int m_Y;
	int m_Frame;
	CHARACTERPOSITION m_Position;		// 캐릭터 자세 이미지
	bool m_bJump;							// 점프하면 true;

public:
	Player();

	void Init(HWND hWnd, WPARAM wParam);
	void Input();
	void SetFrame(CHARACTERPOSITION Position);
	void Jump();
	void Release();

	~Player();

public:
	inline int GetPlayerX()
	{
		return m_X;
	}
	inline int GetPlayerY()
	{
		return m_Y;
	}
	inline int GetFrame()
	{
		return m_Frame;
	}
	inline CHARACTERPOSITION GetPalyerPosition()
	{
		return m_Position;
	}
	inline bool GetJumpFlag()
	{
		return m_bJump;
	}
};

