#include <WinSock2.h>
#include <process.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 100
#define MAX_CLIENT 2
#define PLAYER1 0
#define PLAYER2 1

// ���� ��ġ�� ��Ÿ�� ����ü
struct Point
{
	int		X;
	int		Y;
};

//https://enginius.tistory.com/497

unsigned WINAPI HandleClient(void* arg);
void SetClient(SOCKET clientSock);
void Send(SOCKET clientSock, Point* point, int len);
void ErrorHandling(const char* msg);

int ClientCount = 0;
SOCKET ClientSocks[MAX_CLIENT];
HANDLE Mutex;

bool bSetClient1 = false;
bool bSetClient2 = false;

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
	if (listen(serverSock, 5) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	while (true)
	{
		clientAddrSize = sizeof(clientAddr);
		// accept() �ڽſ��� ������ Ŭ���̾�Ʈ�� ����� �� �ִ� ���ο� ������ �����Ѵ�.
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);

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

unsigned WINAPI HandleClient(void * arg)
{
	SOCKET clientSock = *((SOCKET*)arg);
	int len = 0;
	Point* point;
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

		// ���� ������ Ŭ�� ������ �����ߴٴ� ������ ���
		if (len == sizeof(bool) && (bool)buf == true)
		{
			SetClient(clientSock);
		}
		else
		{
			point = (Point*)buf;

			if (clientSock == ClientSocks[PLAYER1])
			{
				cout << "PLAYER1 - X: " << point->X << " Y: " << point->Y << '\n';
			}
			else if (clientSock == ClientSocks[PLAYER2])
			{
				cout << "PLAYER2 - X: " << point->X << " Y: " << point->Y << '\n';
			}

			Send(clientSock, point, sizeof(Point));
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

void SetClient(SOCKET clientSock)
{
	int setPlayer;
	WaitForSingleObject(Mutex, INFINITE);

	if (!bSetClient1 && clientSock == ClientSocks[PLAYER1])
	{
		cout << "SetPlayer1" << '\n';
		bSetClient1 = true;
		setPlayer = PLAYER1;
		send(clientSock, (char*)&setPlayer, sizeof(setPlayer), 0);
		ReleaseMutex(Mutex);
		return;
	}
	else if (!bSetClient2 && clientSock == ClientSocks[PLAYER2])
	{
		cout << "SetPlayer2" << '\n';
		bSetClient2 = true;
		setPlayer = PLAYER2;
		send(clientSock, (char*)&setPlayer, sizeof(setPlayer), 0);
		ReleaseMutex(Mutex);
		return;
	}
}

// �ٸ� Ŭ���̾�Ʈ�� ���� ����
void Send(SOCKET clientSock, Point * point, int len)
{
	// Thread ���� ��ٸ��� �Լ�
	WaitForSingleObject(Mutex, INFINITE);

	for (int i = 0; i < ClientCount; i++)
	{
		if (ClientSocks[i] != clientSock)
		{
			send(ClientSocks[i], (char*)point, len, 0);
		}
	}

	ReleaseMutex(Mutex);
}

void ErrorHandling(const char * msg)
{
	cout << msg << '\n';
	system("pause");
	exit(1);
}
