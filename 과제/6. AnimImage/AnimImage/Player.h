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
	static int m_X;
	static int m_Y;
	static int m_Frame;
	CHARACTERPOSITION m_Position;		// 캐릭터 자세 이미지
	bool m_bJump;								// 점프하면 true;
	int m_JumpStartTime;
	int m_JumpEndTime;

public:
	Player();

	void Init(HWND hWnd);
	void Input(WPARAM wParam);
	void SetFrame(CHARACTERPOSITION Position);
	static void CALLBACK Jump(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
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

