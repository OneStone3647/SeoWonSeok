#include "NetManager.h"

PiecePoint NetManager::m_Point = { 0, 0, 0, 0 };
bool NetManager::m_bIsTurn = false;
bool NetManager::m_bIsInput = false;
bool NetManager::m_bRecvFlag = false;

bool NetManager::bIsConnect = false;
bool NetManager::bSendConnectFlag = false;
bool NetManager::bSetTeamFlag = false;
int NetManager::SetPieceColor = 0;

NetManager::NetManager()
{
}


NetManager::~NetManager()
{
}

void NetManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	// 윈속을 초기화합니다.
	if (WSAStartup(MAKEWORD(2, 2), &m_WsaData) != 0)
	{
		ErrorHandling("WSAStartup() Error!");
	}

	// socket()
	// 소켓을 생성합니다.
	m_Sock = socket(PF_INET, SOCK_STREAM, 0);

	// 구조체를 초기화합니다.
	ZeroMemory(&m_ServerAddr, sizeof(m_ServerAddr));
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_ServerAddr.sin_port = htons(9000);

	// 서버에 접속합니다.
	if (connect(m_Sock, (SOCKADDR*)&m_ServerAddr, sizeof(m_ServerAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("Connet() Error!");
	}
	else
	{
		// 연결 되었다고 알림
		bIsConnect = true;
	}

	// Thread를 생성합니다.
	m_SendThread = (HANDLE)_beginthreadex(NULL, 0, Send, (void*)&m_Sock, 0, NULL);
	m_RecvThread = (HANDLE)_beginthreadex(NULL, 0, Recv, (void*)&m_Sock, 0, NULL);
}

void NetManager::Release()
{
	// Thread 종료를 기다리는 함수입니다.
	WaitForSingleObject(m_SendThread, INFINITE);
	WaitForSingleObject(m_RecvThread, INFINITE);
	// 소켓을 닫습니다.
	closesocket(m_Sock);
	// 윈속 종료
	WSACleanup();
}

unsigned WINAPI NetManager::Send(void * arg)
{
	SOCKET sock = *((SOCKET*)arg);
	while (true)
	{
		if (!bSendConnectFlag)
		{
			// 서버에 접속했다는 정보를 서버에 전송한다.
			send(sock, (char*)&bIsConnect, sizeof(bool), 0);
			bSendConnectFlag = true;
		}
		else if (m_bIsInput)
		{
			send(sock, (char*)&m_Point, sizeof(PiecePoint), 0);
			m_bIsInput = false;
			m_bIsTurn = false;
		}
	}

	return 0;
}

unsigned WINAPI NetManager::Recv(void * arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int len = 0;
	char buf[BUFSIZE];

	while ((len = recv(sock, buf, sizeof(buf) - 1, 0)) != 0)
	{
		// 소켓 에러
		if (len == SOCKET_ERROR)
		{
			break;
		}

		buf[len] = '\n';

		// 플레이어 설정
		if (len == sizeof(int) && !bSetTeamFlag)
		{
			SetPieceColor = (int)*buf;
			if (SetPieceColor == PIECECOLOR_BLACK)
			{
				m_bIsTurn = true;
			}
			else
			{
				m_bIsTurn = false;
			}
			bSetTeamFlag = true;
		}
		// 상대편의 포인트
		else if (len == sizeof(PiecePoint) && !m_bRecvFlag)
		{
			PiecePoint* tmpPoint = (PiecePoint*)buf;
			m_Point = *tmpPoint;
			m_bRecvFlag = true;
		}
	}
	return 0;
}

void NetManager::ErrorHandling(const char * msg)
{
	MessageBox(m_hWnd, TEXT(msg), TEXT("Error!!"), MB_OK);
}
