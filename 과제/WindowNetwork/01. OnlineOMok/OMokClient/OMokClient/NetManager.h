#pragma once
#include "Mecro.h"
#include "Singleton.h"

#define BUF_SIZE 100

struct Point
{
	int		X;
	int		Y;
};

class NetManager : public Singleton<NetManager>
{
private:
	WSADATA		m_WsaData;
	SOCKET			m_Sock;
	SOCKADDR_IN	m_ServerAddr;
	HANDLE			m_SendThread;
	HANDLE			m_RecvThread;
	
	static Point		m_Point;
	static bool		m_bMyTurn;
	static bool		m_bIsInput;
	static bool		m_bRecvFlag;

	static bool		bIsConnect;
	static bool		bSendConnectFlag;
	static bool		bSetTeamFlag;
	static int			SetPlayer;

public:
	NetManager();
	virtual ~NetManager();

public:
	void Init();
	void Release();
	static unsigned WINAPI Send(void* arg);
	static unsigned WINAPI Recv(void* arg);
	void ErrorHandling(const char* msg);

public:
	inline Point GetPoint()
	{
		return m_Point;
	}

	inline void SetPointX(int x)
	{
		m_Point.X = x;
	}
	inline void SetPointY(int y)
	{
		m_Point.Y = y;
	}

	inline void SetInputFlag(bool bFlag)
	{
		m_bIsInput = bFlag;
	}

	inline bool GetsetTeam()
	{
		return bSetTeamFlag;
	}

	inline bool GetMyTurn()
	{
		return m_bMyTurn;
	}
	inline void SetMyTurn(bool bFlag)
	{
		m_bMyTurn = bFlag;
	}

	inline int GetPlayerSet()
	{
		return SetPlayer;
	}

	inline bool GetRecvFlag()
	{
		return m_bRecvFlag;
	}
	inline void SetRecvFlag(bool bFlag)
	{
		m_bRecvFlag = bFlag;
	}
};

