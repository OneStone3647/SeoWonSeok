#include "NetManager.h"

Point NetManager::m_Point = { 0, 0 };
bool NetManager::m_bMyTurn = false;
bool NetManager::m_bIsInput = false;
bool NetManager::m_bRecvFlag = false;

bool NetManager::bIsConnect = false;
bool NetManager::bSendConnectFlag = false;
bool NetManager::bSetTeamFlag = false;
int NetManager::SetPlayer = 0;

NetManager::NetManager()
{
}


NetManager::~NetManager()
{
	Release();
}

void NetManager::Init()
{
	// ���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &m_WsaData) != 0)
	{
		ErrorHandling("WSAStartup() Error!");
	}

	// ���� ����
	m_Sock = socket(PF_INET, SOCK_STREAM, 0);

	// ���� �ּ� ����
	memset(&m_ServerAddr, 0, sizeof(m_ServerAddr));
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	m_ServerAddr.sin_port = htons(9000);

	// ������ ����
	if (connect(m_Sock, (SOCKADDR*)&m_ServerAddr, sizeof(m_ServerAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("Connet() Error!");
	}
	else
	{
		// ���� �Ǿ��ٰ� �˸�
		bIsConnect = true;
	}

	// Thread ����
	m_SendThread = (HANDLE)_beginthreadex(NULL, 0, Send, (void*)&m_Sock, 0, NULL);
	m_RecvThread = (HANDLE)_beginthreadex(NULL, 0, Recv, (void*)&m_Sock, 0, NULL);
}

void NetManager::Release()
{
	// Thread ���� ��ٸ��� �Լ�
	WaitForSingleObject(m_SendThread, INFINITE);
	WaitForSingleObject(m_RecvThread, INFINITE);
	// ������ �ݴ´�.
	closesocket(m_Sock);
	// ���� ����
	WSACleanup();
}

unsigned WINAPI NetManager::Send(void * arg)
{
	SOCKET sock = *((SOCKET*)arg);
	while (true)
	{
		if (!bSendConnectFlag)
		{
			send(sock, (char*)&bIsConnect, sizeof(bool), 0);
			bSendConnectFlag = true;
		}
		else if(m_bIsInput)
		{
			send(sock, (char*)&m_Point, sizeof(Point), 0);
			m_bIsInput = false;
			m_bMyTurn = false;
		}
	}

	return 0;
}

unsigned WINAPI NetManager::Recv(void * arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int len = 0;
	char buf[BUF_SIZE];

	while ((len = recv(sock, buf, sizeof(buf) - 1, 0)) != 0)
	{
		// ���� ����
		if (len == SOCKET_ERROR)
		{
			break;
		}

		buf[len] = '\n';

		// �÷��̾� ����
		if (len == sizeof(int) && !bSetTeamFlag)
		{
			SetPlayer = (int)*buf;
			cout << SetPlayer << '\n';
			if (SetPlayer == PLAYER1)
			{
				m_bMyTurn = true;
			}
			else
			{
				m_bMyTurn = false;
			}
			bSetTeamFlag = true;
		}
		// ������� ����Ʈ
		else if (len == sizeof(Point) && !m_bRecvFlag)
		{
			Point* tmpPoint = (Point*)buf;
			m_Point = *tmpPoint;
			m_bRecvFlag = true;
		}
	}
	return 0;
}

void NetManager::ErrorHandling(const char * msg)
{
	cout << msg << '\n';
	system("pause");
	exit(1);
}
