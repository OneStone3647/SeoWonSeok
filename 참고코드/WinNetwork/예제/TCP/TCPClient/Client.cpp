#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define SERVERIP	"127.0.0.1" // 서버 머신의 IP주소
#define SERVERPORT	9000 
#define BUFSIZE		512

// 소켓 함수 오류 출력 후 종료
void err_quit(const char* msg);
// 소켓 함수 오류 출력
void err_display(const char* msg);
// 사용자 정의 데이터 수신 함수
int recvn(SOCKET s, char *buf, int len, int flags);

int main()
{
	int retval;

	//윈속 초기화
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET)
		err_quit("socket()");

	//connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = connect(sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	if (retval == SOCKET_ERROR)
		err_quit("connect()");

	//데이터 통신에 사용할 변수
	char buf[BUFSIZE + 1];
	int len;

	//서버와 데이터 통신
	while (1)
	{
		//데이터 입력
		printf("\n[보낼데이터] ");

		if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
			break;

		//'\n' 문자 제거
		len = strlen(buf);

		if (buf[len - 1] == '\n')
			buf[len - 1] = '\0';

		if (strlen(buf) == 0)
		{
			err_display("buf가 0");
			break;
		}

		//데이터 보내기
		retval = send(sock, buf, strlen(buf), 0);

		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
			break;
		}

		printf("[TCP 클라이언트] %d바이트를 보냈습니다. \n", retval);

		//데이터 받기
		retval = recvn(sock, buf, retval, 0);

		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			break;
		}
		else if (retval == 0)
		{
			err_display("받은양 0");
			break;
		}

		//받은 데이터 출력
		buf[retval] = '\0';
		printf("[TCP 클라이언트] %d바이트를 받았습니다. \n", retval);
		printf("[받은 데이터] %s\n", buf);
	}

	//closesocket()
	closesocket(sock);

	//윈속 종료
	WSACleanup();

	system("pause");
	return 0;
}

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	//연속성인 TCP는 데이터를 처리하는 순간 그 데이터가 한개 이상일 수도 있다.
	while (left > 0)
	{
		received = recv(s, ptr, left, flags);

		if (received == SOCKET_ERROR)
			return SOCKET_ERROR;
		else if (received == 0)
			break;

		left -= received;
		ptr += received;
	}

	return (len - left);
}

void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void err_display(const char* msg)
{
	PVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	printf("[%s] %s", msg, (const char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
