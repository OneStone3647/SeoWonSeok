#pragma once
#include "Mecro.h"
#include "Singleton.h"

// 말의 위치를 저장할 구조체
struct PiecePoint
{
	int prev_X;
	int prev_Y;
	int cur_X;
	int cur_Y;
};

class NetManager : public Singleton<NetManager>
{
private:
	WSADATA		m_WsaData;
	SOCKET			m_Sock;
	SOCKADDR_IN	m_ServerAddr;
	HANDLE			m_SendThread;
	HANDLE			m_RecvThread;

	HWND				m_hWnd;
	static PiecePoint		m_Point;
	static bool			m_bIsTurn;
	static bool			m_bIsInput;
	static bool			m_bRecvFlag;

	static bool			bIsConnect;
	static bool			bSendConnectFlag;
	static bool			bSetTeamFlag;
	static int				SetPieceColor;

public:
	NetManager();
	~NetManager();

public:
	void Init(HWND hWnd);
	void Release();
	static unsigned WINAPI Send(void* arg);
	static unsigned WINAPI Recv(void* arg);
	void ErrorHandling(const char* msg);

public:
	inline int GetPieceColorSet()
	{
		return SetPieceColor;
	}

	inline bool GetTurn()
	{
		return m_bIsTurn;
	}
	inline void SetTurn(bool bFlag)
	{
		m_bIsTurn = bFlag;
	}

	inline bool GetRecvFlag()
	{
		return m_bRecvFlag;
	}
	inline void SetRecvFlag(bool bFlag)
	{
		m_bRecvFlag = bFlag;
	}

	inline PiecePoint GetPoint()
	{
		return m_Point;
	}
	inline void SetPoint(int prevX, int prevY, int curX, int curY)
	{
		m_Point =  { prevX, prevY, curX, curY };
	}

	inline void SetInputFlag(bool bFlag)
	{
		m_bIsInput = bFlag;
	}

	inline bool GetSetTeam()
	{
		return bSetTeamFlag;
	}
};

