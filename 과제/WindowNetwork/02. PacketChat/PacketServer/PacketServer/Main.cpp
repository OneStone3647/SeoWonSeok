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

// 패킷
#pragma pack(push, 1)	// 1바이트 단위로 정렬
struct PACKET
{
	int login;
	char msg[256];
};
#pragma pack(pop)	// 정렬 설정을 이전 상태(기본값)로 돌림

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
	// SOMAXCONN: 네트워크 최대 연결 개수
	if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	while (true)
	{
		clientAddrSize = sizeof(clientAddr);
		// accept() 자신에게 접속한 클라이언트와 통신할 수 있는 새로운 소켓을 생성한다.
		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);
		if (clientSock == INVALID_SOCKET)
		{
			cout << "accept Error!!" << '\n';
			continue;
		}
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

unsigned int WINAPI HandleClient(void * arg)
{
	SOCKET clientSock = *((SOCKET*)arg);
	int len = 0;
	PACKET* packet;
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

		packet = (PACKET*)buf;
		// 받은 패킷 처리
		if (packet->login == LOGIN_SUCCESS)
		{
			Send(clientSock, packet, sizeof(PACKET));
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

void Send(SOCKET clientSock, PACKET * packet, int len)
{
	// Thread 종료 기다리기 함수
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
