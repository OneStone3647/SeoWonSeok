#include <WinSock2.h>
#include <process.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 512
#define MAX_CLIENT 5

enum LOGIN
{
	LOGIN_SUCCESS = 0,
	LOGIN_FAILED
};

// ��Ŷ
#pragma pack(push, 1)	// 1����Ʈ ������ ����
struct PACKET
{
	int login;
	char msg[256];
};
#pragma pack(pop)	// ���� ������ ���� ����(�⺻��)�� ����

int ClientCount = 0;
SOCKET ClientSocks[MAX_CLIENT];
HANDLE Mutex;

unsigned int WINAPI HandleClient(void* arg);
void Send(SOCKET clientSock, PACKET* packet, int len);
void ErrorHandling(const char* msg);

int main()
{
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int clientAddrSize;
	HANDLE thread;

	// ���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() Error!");
	}

	// ���ý� ����
	Mutex = CreateMutex(NULL, FALSE, NULL);

	// ���� ����
	serverSock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(9000);

	// bind() ���� IP �ּҿ� ���� ��Ʈ ��ȣ�� ����
	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() Error!");
	}

	// listen() Ŭ���̾�Ʈ�� ���� �����غ� �Ѵ�.
	// �� ��° ����: ������ ���� ó������ �ʴ��� ���� ������ Ŭ���̾�Ʈ�� ��
	// SOMAXCONN: ��Ʈ��ũ �ִ� ���� ����
	if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	while (true)
	{
		clientAddrSize = sizeof(clientAddr);
		// accept() �ڽſ��� ������ Ŭ���̾�Ʈ�� ����� �� �ִ� ���ο� ������ �����Ѵ�.
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);
		if (clientSock == INVALID_SOCKET)
		{
			cout << "accept Error!!" << '\n';
			continue;
		}
		// Thread ���� ��ٸ��� �Լ�
		WaitForSingleObject(Mutex, INFINITE);

		ClientSocks[ClientCount++] = clientSock;

		// Mutex ������Ʈ�� �������� �ع��մϴ�.
		ReleaseMutex(Mutex);

		thread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);

		cout << "Connected Client IP : " << inet_ntoa(clientAddr.sin_addr) << " Port: " << ntohs(clientAddr.sin_port) << '\n';
	}

	// ������ �ݴ´�.
	closesocket(serverSock);
	// ���� ����
	WSACleanup();
	return 0;
}

unsigned int WINAPI HandleClient(void * arg)
{
	SOCKET clientSock = *((SOCKET*)arg);
	int len = 0;
	PACKET* packet;
	char buf[BUF_SIZE];

	// recv() �Լ��� ���� ������ ����Ʈ ���� �����Ѵ� ���� ���� �ּ� 1, �ִ� 3 ��° ���� ��.
	// ����� ���� ���α׷��� closesocket() �Լ��� ȣ���� ������ �����ϸ�
	// recv() �Լ��� 0�� �����Ѵ�. �� ��� ��������� �θ���.
	while ((len = recv(clientSock, buf, sizeof(buf) - 1, 0)) != 0)
	{
		// ���� ����
		if (len == SOCKET_ERROR)
		{
			break;
		}

		buf[len] = '\n';

		packet = (PACKET*)buf;
		// ���� ��Ŷ ó��
		if (packet->login == LOGIN_SUCCESS)
		{
			Send(clientSock, packet, sizeof(PACKET));
		}
	}

	// Thread ���� ��ٸ��� �Լ�
	WaitForSingleObject(Mutex, INFINITE);

	// ���� ������ Ŭ���̾�Ʈ ����
	for (int i = 0; i < ClientCount; i++)
	{
		if (clientSock == ClientSocks[i])
		{
			while (i++ < ClientCount - 1)
			{
				ClientSocks[i] = ClientSocks[i + 1];
			}
			break;
		}
	}

	ClientCount--;
	// Mutex ������Ʈ�� �������� �ع��մϴ�.
	ReleaseMutex(Mutex);
	// ������ �ݴ´�.
	closesocket(clientSock);
	return 0;
}

void Send(SOCKET clientSock, PACKET * packet, int len)
{
	// Thread ���� ��ٸ��� �Լ�
	WaitForSingleObject(Mutex, INFINITE);

	for (int i = 0; i < ClientCount; i++)
	{
		send(ClientSocks[i], (char*)packet, len, 0);
	}

	ReleaseMutex(Mutex);
}

void ErrorHandling(const char * msg)
{
	cout << msg << '\n';
	system("pause");
	exit(1);
}
