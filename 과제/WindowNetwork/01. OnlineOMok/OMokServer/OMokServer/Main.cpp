#include <WinSock2.h>
#include <process.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 100
#define MAX_CLIENT 2
#define PLAYER1 0
#define PLAYER2 1

// 돌의 위치를 나타낼 구조체
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

	// 윈속 초기화
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() Error!");
	}

	// 뮤택스 생성
	Mutex = CreateMutex(NULL, FALSE, NULL);

	// 소켓 생성
	serverSock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(9000);

	// bind() 지역 IP 주소와 지역 포트 번호를 결정
	if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() Error!");
	}

	// listen() 클라이언트를 접속 받을준비를 한다.
	// 두 번째 인자: 서버가 당장 처리하지 않더라도 접속 가능한 클라이언트의 수
	if (listen(serverSock, 5) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	while (true)
	{
		clientAddrSize = sizeof(clientAddr);
		// accept() 자신에게 접속한 클라이언트와 통신할 수 있는 새로운 소켓을 생성한다.
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);

		// Thread 종료 기다리기 함수
		WaitForSingleObject(Mutex, INFINITE);

		ClientSocks[ClientCount++] = clientSock;

		// Mutex 오브젝트의 소유권을 해방합니다.
		ReleaseMutex(Mutex);

		thread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);

		cout << "Connected Client IP : " << inet_ntoa(clientAddr.sin_addr) << " Port: " << ntohs(clientAddr.sin_port) << '\n';
	}
	
	// 소켓을 닫는다.
	closesocket(serverSock);
	// 윈속 종료
	WSACleanup();
	return 0;
}

unsigned WINAPI HandleClient(void * arg)
{
	SOCKET clientSock = *((SOCKET*)arg);
	int len = 0;
	Point* point;
	char buf[BUF_SIZE];

	// recv() 함수는 실제 복사한 바이트 수를 리턴한다 리턴 값은 최소 1, 최대 3 번째 인자 값.
	// 상대편 응용 프로그램이 closesocket() 함수를 호출해 접속을 종료하면
	// recv() 함수는 0을 리턴한다. 이 경우 정상종료라 부른다.
	while ((len = recv(clientSock, buf, sizeof(buf) - 1, 0)) != 0)
	{
		// 소켓 에러
		if (len == SOCKET_ERROR)
		{
			break;
		}

		buf[len] = '\n';

		// 받은 정보가 클라가 서버에 접속했다는 정보일 경우
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

	// Thread 종료 기다리기 함수
	WaitForSingleObject(Mutex, INFINITE);

	// 연결 해제된 클라이언트 제거
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
	// Mutex 오브젝트의 소유권을 해방합니다.
	ReleaseMutex(Mutex);
	// 소켓을 닫는다.
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

// 다른 클라이언트에 정보 전달
void Send(SOCKET clientSock, Point * point, int len)
{
	// Thread 종료 기다리기 함수
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
