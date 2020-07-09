#pragma once
#include "Mecro.h"

class NetManager : public Singleton<NetManager>
{
private:
	WSADATA		m_WsaData;
	SOCKET		m_Sock;
	SOCKADDR_IN	m_ServerAddr;
	HANDLE		m_SendThread;
	HANDLE		m_RecvThread;
	HWND		m_hWnd;

	static InfoPoint	m_InfoPoint;
	static InfoAnswer	m_InfoAnswer;
	static bool			m_bIsDrawInput;
	static bool			m_bRecvDrawFlag;
	static bool			m_bIsAnswerInput;
	static bool			m_bRecvAnswerFlag;

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
	inline bool GetRecvAnswerFlag()
	{
		return m_bRecvAnswerFlag;
	}
	inline void SetRecvAnswerFlag(bool bFlag)
	{
		m_bRecvAnswerFlag = bFlag;
	}

	inline void SetAnswerInputFlag(bool bFlag)
	{
		m_bIsAnswerInput = bFlag;
	}

	inline InfoAnswer GetInfoAnswer()
	{
		return m_InfoAnswer;
	}
	inline void SetAnswer(const char* str)
	{
		strcpy(m_InfoAnswer.answer, str);
	}

};

