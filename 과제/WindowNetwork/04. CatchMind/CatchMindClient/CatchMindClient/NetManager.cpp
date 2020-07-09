#include "NetManager.h"

InfoPoint NetManager::m_InfoPoint = { INFOINDEX_POINT, COLOR_BLACK, {0, 0} };
InfoAnswer NetManager::m_InfoAnswer = { INFOINDEX_ANSWER, "" };

bool NetManager::m_bIsDrawInput = false;
bool NetManager::m_bRecvDrawFlag = false;
bool NetManager::m_bIsAnswerInput = false;
bool NetManager::m_bRecvAnswerFlag = false;

NetManager::NetManager()
{
}


NetManager::~NetManager()
{
	Release();
}

void NetManager::Init(HWND hWnd)
{
	m_hWnd = hWnd;

	// ������ �ʱ�ȭ�մϴ�.
	if (WSAStartup(MAKEWORD(2, 2), &m_WsaData) != 0)
	{
		ErrorHandling("WSAStartup() Error!");
	}

	// socket()
	// ������ �����մϴ�.
	m_Sock = socket(PF_INET, SOCK_STREAM, 0);

	// ����ü�� �ʱ�ȭ�մϴ�.
	ZeroMemory(&m_ServerAddr, sizeof(m_ServerAddr));
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_ServerAddr.sin_port = htons(9000);

	// connect()
	// ������ �����մϴ�.
	if (connect(m_Sock, (SOCKADDR*)&m_ServerAddr, sizeof(m_ServerAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() Error!");
	}

	// Thread�� �����մϴ�
	m_SendThread = (HANDLE)_beginthreadex(NULL, 0, Send, (void*)&m_Sock, 0, NULL);
	m_RecvThread = (HANDLE)_beginthreadex(NULL, 0, Recv, (void*)&m_Sock, 0, NULL);
}

void NetManager::Release()
{
	// Thread ���Ḧ ��ٸ��� �Լ��Դϴ�.
	WaitForSingleObject(m_SendThread, INFINITE);
	WaitForSingleObject(m_RecvThread, INFINITE);
	// ������ �ݽ��ϴ�.
	closesocket(m_Sock);
	// ���� ����
	WSACleanup();
}

unsigned WINAPI NetManager::Send(void * arg)
{
	SOCKET sock = *((SOCKET*)arg);
	while (true)
	{
		if (m_bIsDrawInput)
		{
			send(sock, (char*)&m_InfoPoint, sizeof(InfoPoint), 0);
			m_bIsDrawInput = false;
		}

		if (m_bIsAnswerInput)
		{
			send(sock, (char*)&m_InfoAnswer, sizeof(InfoAnswer), 0);
			m_bIsAnswerInput = false;
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
		// ���� ������ �߻��� ��� �ݺ����� �����մϴ�.
		if (len == SOCKET_ERROR)
		{
			break;
		}

		buf[len] = '\n';

		if (len == sizeof(InfoPoint) && m_bRecvDrawFlag != true)
		{
			InfoPoint* tmpInfoPoint = (InfoPoint*)buf;
			if (tmpInfoPoint->infoIndex == INFOINDEX_POINT)
			{
				m_InfoPoint = *tmpInfoPoint;
				m_bRecvDrawFlag = true;
			}
			else
			{
				continue;
			}
		}
		else if (len == sizeof(InfoAnswer) && m_bRecvAnswerFlag != true)
		{
			InfoAnswer* tmpInfoAnswer = (InfoAnswer*)buf;
			if (tmpInfoAnswer->infoIndex == INFOINDEX_ANSWER)
			{
				m_InfoAnswer = *tmpInfoAnswer;
				m_bRecvAnswerFlag = true;
			}
			else
			{
				continue;
			}
		}
	}

	return 0;
}

void NetManager::ErrorHandling(const char * msg)
{
	MessageBox(m_hWnd, TEXT(msg), TEXT("Error!!"), MB_OK);
}
