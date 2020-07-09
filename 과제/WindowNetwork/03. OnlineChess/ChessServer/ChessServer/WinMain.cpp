#include "Mecro.h"

// 소켓 정보를 저장할 구조체
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE + 1];
	int recvBytes;
	int sendBytes;
	BOOL recvDelayed;
	SOCKETINFO* next;
};

// 말의 위치를 저장할 구조체
struct PiecePoint
{
	int prev_X;
	int prev_Y;
	int cur_X;
	int cur_Y;
};

// 피스의 색
enum PIECECOLOR
{
	PIECECOLOR_BLACK = 1,
	PIECECOLOR_WHITE
};

// 소켓 정보를 가진 구조체의 연결리스트
SOCKETINFO* SocketInfoList;

SOCKET PlayerBlack = NULL;
SOCKET PlayerWhite = NULL;
bool bSetPlayerBlack = false;
bool bSetPlayerWhite = false;

HWND g_hWnd;
HWND g_LogBox;	// 로그를 표시할 창
HINSTANCE g_hInst;	// 글로벌 인스턴스 핸들값
LPCTSTR IpszClass = TEXT("ChessServer");	// 창 이름

// WINDOW 메시지 처리
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
// 소켓 메시지 처리
void ProcessSocketMessage(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
// 소켓 관리 함수
BOOL AddSocketInfo(SOCKET sock);
SOCKETINFO* GetSocketInfo(SOCKET sock);
SOCKETINFO* GetAnotherSocketInfo(SOCKET sock);
void RemoveSocketInfo(SOCKET sock);

// 접속한 클라이언트의 순서대로 플레이어가 소유한 피스의 종류에 맞는 색을 설정합니다.
void SetClient(SOCKET sock);

// 로그 박스에 텍스트를 출력하는 함수
void AddStrToLog(char* msg);

// 오류 출력 함수
void ErrorQuit(const char* msg);
void ErrorDisplay(const char* msg);
void ErrorDisplay(int errorCode);

// WinAPI의 Main함수
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int retval;

	MSG Message;
	WNDCLASS WndClass;		// 기본 윈도우 환경을 만드는 구조체입니다.
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;	// 예약영역
	WndClass.cbWndExtra = 0;	// 예약영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// 배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// 커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// 아이콘 모양
	WndClass.hInstance = hInstance;		// 프로그램 핸들값(번호) 등록합니다.
	WndClass.lpfnWndProc = WndProc;		// 프로세스 함수 호출한다.
	WndClass.lpszClassName = IpszClass;		// 클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	// 윈도우의 수직과 수평이 변경되면 다시 그립니다.
	RegisterClass(&WndClass);	// 만들어진 WndClass룰 등록합니다.

	// 윈도우 창의 크기는 테두리와 캡션의 크기까지 합한 크기입니다.
	// 작업영역의 크기를 1000x1000로 만들려면 1038x1016으로 생성해야 합니다.
	g_hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOWWIDTH + 38, WINDOWHEIGHT + 16, NULL,
		(HMENU)NULL, hInstance, NULL);
	if (g_hWnd == NULL)
	{
		return 1;
	}

	ShowWindow(g_hWnd, nCmdShow);
	// 무효화 영역(생성된 윈도우의 일부가 다른 윈도우 등에 가려졌거나 리사이즈 되었을 경우)을 갱신시켜주는 함수입니다.
	UpdateWindow(g_hWnd);

	// 윈속을 초기화합니다.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorQuit("WSAStartup() Error!");
	}

	// socket()
	// 소켓을 생성합니다.
	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock == INVALID_SOCKET)
	{
		ErrorQuit("socket() Error!");
	}
	// 구조체를 초기화합니다.
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(9000);

	// bind()
	// 지역 IP 주소와 지역포트 번호를 결정합니다.
	retval = bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (retval == SOCKET_ERROR)
	{
		ErrorQuit("bind() Error!");
	}

	// listen()
	// 클라이언트를 접속 받을 준비를 합니다.
	retval = listen(serverSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		ErrorQuit("listen() Error!");
	}

	// WSAAsySelect()
	// FD_ACCEPT, FD_CLOSE 이벤트만 등록합니다.
	// FD_ACCEPT: 접속한 클라이언트가 있다.
	// FD_CLOSE: 상대가 접속을 종료했다.
	retval = WSAAsyncSelect(serverSock, g_hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		ErrorQuit("WSAAsynSelect Error!");
	}

	while (GetMessage(&Message, NULL, 0, 0))	// 사용자에게 메시지를 받아오는 함수(WM_QUIT 메시지를 받을 경우 종료합니다.)
	{
		TranslateMessage(&Message);		// 키보드 입력 메시지 처리함수입니다.
		DispatchMessage(&Message);		// 받은 메시지를 WndProc에 전달하는 함수입니다.
	}

	// 윈속 종료
	WSACleanup();
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		g_LogBox = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
			LBS_NOTIFY | WS_VSCROLL, 10, 10, WINDOWWIDTH, WINDOWHEIGHT - 40, hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		break;
		//등록한 유저 메시지를 받게 되면 처리하는 부분입니다.
		//메시지 처리를 위한 공간이 길어질 경우를 대비해서 따로 메시지를 처리하는 함수를 만들어줍니다.
		//윈도우 메시지를 그대로 처리해야하기때문에 인자를 그대로 넘겨주는 네트워크 메시지 처리 함수를 만들어 줍니다.
	case WM_SOCKET://소켓 관련 윈도우 메시지
		ProcessSocketMessage(hWnd, iMessage, wParam, lParam);
		break;
	case WM_DESTROY:// 윈도우가 파괴되었다는 메세지
		PostQuitMessage(0); //GetMessage함수에 WM_QUIT 메시지를 보냅니다.
		return 0; //WndProc의 Switch는 break 대신 return 0; 를 씁니다.
	}
	// case에 있는 메시지를 제외한 나머지 메시지를 처리합니다.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// 소켓 관련 윈도우 메시지를 처리하는 함수 입니다.
void ProcessSocketMessage(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	SOCKETINFO* recvSock;
	SOCKETINFO* sendSock;
	SOCKET clientSock;
	SOCKADDR_IN clientAddr;
	int addrLen;
	int retval;
	char buf[BUFSIZE];

	// 오류 발행 여부를 확인합니다.
	if (WSAGETSELECTERROR(lParam))
	{
		ErrorDisplay(WSAGETSELECTERROR(lParam));
		RemoveSocketInfo(wParam);
		return;
	}

	// 메시지를 처리합니다.
	switch ((WSAGETSELECTEVENT(lParam)))
	{
		// 대응 함수: accept()
		// accept() 함수를 호출하고 리턴 값을 확인하여 오류를 처리한다.
	case FD_ACCEPT:
		addrLen = sizeof(clientAddr);
		clientSock = accept(wParam, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSock == INVALID_SOCKET)
		{
			ErrorDisplay("accept() Error!");
			return;
		}

		sprintf(buf, "[TCP 서버] 클라이언트 접속: IP 주소=%s, 포트 번호=%d",
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		AddStrToLog(buf);

		// 접속한 클라이언트 소켓을 등록합니다.
		AddSocketInfo(clientSock);

		// FD_READ, FD_WRITE, FD_CLOSE를 등록합니다.
		retval = WSAAsyncSelect(clientSock, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
		if (retval == SOCKET_ERROR)
		{
			ErrorDisplay("SWAAsyncSelect() Error!");
			RemoveSocketInfo(clientSock);
		}

		break;

		// 대응함수: recv(), recvfrom()
	case FD_READ:
		// 소켓 정보 구조체를 받습니다.
		recvSock = GetSocketInfo(wParam);
		if (recvSock == nullptr)
		{
			return;
		}
		// 이번에 받았지만 아직 보내지 않은 데이터가 있다면 받았다는 사실만 기록하고 리턴합니다.
		if (recvSock->recvBytes > 0)
		{
			recvSock->recvDelayed = TRUE;
			return;
		}

		// 데이터를 받습니다.
		retval = recv(recvSock->sock, recvSock->buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			ErrorDisplay("recv() Error!");
			RemoveSocketInfo(wParam);
			return;
		}

		recvSock->recvBytes = retval;

		// 받은 데이터를 출력합니다.
		recvSock->buf[retval] = '\n';
		//addrLen = sizeof(clientAddr);
		//// 소켓에 해당하는 SOCKADDR_IN 구조체 정보를 두 번째 인자에 저장합니다.
		//getpeername(wParam, (SOCKADDR*)&clientAddr, &addrLen);

		//sprintf(buf, "[TCP / %s:%d] % s",
		//	inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), tmpSock->buf);
		//AddStrToLog(buf);

		//// 받은 정보가 클라가 서버에 접속했다는 정보일 경우
		//if (retval == sizeof(bool) && (bool)recvSock->buf == true)
		//{
		//	SetClient(recvSock->sock);
		//}
		// 받은 정보가 피스의 위치일 경우
		if(retval == sizeof(PiecePoint))
		{
			PiecePoint* tmpPoint = (PiecePoint*)recvSock->buf;

			if (recvSock->sock == PlayerBlack)
			{
				sprintf(buf, "PlayerBlack Prev[X: %d, Y: %d] Cur[X: %d, Y: %d]",
					tmpPoint->prev_X, tmpPoint->prev_Y, tmpPoint->cur_X, tmpPoint->cur_Y);
				AddStrToLog(buf);
			}
			else if (recvSock->sock == PlayerWhite)
			{
				sprintf(buf, "PlayerWhite Prev[X: %d, Y: %d] Cur[X: %d, Y: %d]",
					tmpPoint->prev_X, tmpPoint->prev_Y, tmpPoint->cur_X, tmpPoint->cur_Y);
				AddStrToLog(buf);
			}
		}

		// Write까지 처리해야 하기 때문에 break문은 없습니다.

		// 대응함수: send(), sendto()
	case FD_WRITE:
		recvSock = GetSocketInfo(wParam);
		sendSock = GetAnotherSocketInfo(wParam);

		// 받은 정보가 클라가 서버에 접속했다는 정보일 경우
		if (recvSock->recvBytes == sizeof(bool) && (bool)recvSock->buf == true)
		{
			SetClient(recvSock->sock);
			recvSock->recvBytes = recvSock->sendBytes = 0;
		}

		if (recvSock == nullptr)
		{
			return;
		}
		if (recvSock->recvBytes <= recvSock->sendBytes)
		{
			return;
		}

		// 데이터 보내기
		if (recvSock->sock == PlayerBlack)
		{
			retval = send(PlayerWhite, recvSock->buf + recvSock->sendBytes,
				recvSock->recvBytes - recvSock->sendBytes, 0);
		}
		else if (recvSock->sock == PlayerWhite)
		{
			retval = send(PlayerBlack, recvSock->buf + recvSock->sendBytes,
				recvSock->recvBytes - recvSock->sendBytes, 0);
		}

		if (retval == SOCKET_ERROR)
		{
			ErrorDisplay("send() Error!");
			RemoveSocketInfo(wParam);
			return;
		}

		recvSock->sendBytes += retval;

		// 받은 데이터를 모두 보냈는지 체크합니다.
		// 받았지만 보내지 않은 파일 즉 TRUE로만 만들어둔 데이터들을 보냅니다.
		if (recvSock->recvBytes == recvSock->sendBytes)
		{
			recvSock->recvBytes = recvSock->sendBytes = 0;
			if (recvSock->recvDelayed)
			{
				recvSock->recvDelayed = FALSE;
				PostMessage(hWnd, WM_SOCKET, wParam, FD_READ);
			}
		}

		break;
	case FD_CLOSE:
		RemoveSocketInfo(wParam);
		break;
	}
}

// 소켓 정보를 연결리스트에 추가하는 함수입니다.
BOOL AddSocketInfo(SOCKET sock)
{
	SOCKETINFO* tmpSock = new SOCKETINFO;
	if (tmpSock == nullptr)
	{
		MessageBox(g_hWnd, TEXT("[오류] 메모리가 부족합니다"), TEXT("Error"), MB_OK);
		return FALSE;
	}

	tmpSock->sock = sock;
	tmpSock->recvBytes = 0;
	tmpSock->sendBytes = 0;
	tmpSock->recvDelayed = FALSE;
	tmpSock->next = SocketInfoList;
	SocketInfoList = tmpSock;

	if (PlayerBlack == NULL)
	{
		PlayerBlack = sock;
	}
	else if (PlayerWhite == NULL)
	{
		PlayerWhite = sock;
	}

	return TRUE;
}

// 소켓 정보를 연결리스트 얻는 함수입니다.
SOCKETINFO * GetSocketInfo(SOCKET sock)
{
	SOCKETINFO* tmpSock = SocketInfoList;

	while (tmpSock)
	{
		if (tmpSock->sock == sock)
		{
			return tmpSock;
		}

		tmpSock = tmpSock->next;
	}

	return nullptr;
}

SOCKETINFO * GetAnotherSocketInfo(SOCKET sock)
{
	SOCKETINFO* tmpSock = SocketInfoList;

	while (tmpSock)
	{
		if (tmpSock->sock != sock)
		{
			return tmpSock;
		}

		tmpSock = tmpSock->next;
	}

	return nullptr;
}

// 연결리스트에서 소켓 정보를 제거하는 함수입니다.
void RemoveSocketInfo(SOCKET sock)
{
	SOCKADDR_IN tmpClientAddr;
	int addrLen = sizeof(tmpClientAddr);
	// 소켓에 해당하는 SOCKADDR_IN 구조체 정보를 두 번째 인자에 저장합니다.
	getpeername(sock, (SOCKADDR*)&tmpClientAddr, &addrLen);

	char buf[BUFSIZE];
	sprintf(buf, "[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d",
		inet_ntoa(tmpClientAddr.sin_addr), ntohs(tmpClientAddr.sin_port));
	AddStrToLog(buf);

	SOCKETINFO* curSock = SocketInfoList;
	SOCKETINFO* prevSock = NULL;

	while (curSock)
	{
		if (curSock->sock == sock)
		{
			if (prevSock)
			{
				prevSock->next = curSock->next;
			}
			else
			{
				SocketInfoList = curSock->next;
			}

			closesocket(curSock->sock);
		}

		prevSock = curSock;
		curSock = curSock->next;
	}
}

void SetClient(SOCKET sock)
{
	int SetPlayer;
	char buf[BUFSIZE];
	if (!bSetPlayerBlack&&sock == PlayerBlack)
	{
		SetPlayer = PIECECOLOR_BLACK;
		send(sock, (char*)&SetPlayer, sizeof(SetPlayer), 0);
		bSetPlayerBlack = true;
		sprintf(buf, "PlayerBlack Set!!");
		AddStrToLog(buf);
		return;
	}
	else if (!bSetPlayerWhite && sock == PlayerWhite)
	{
		SetPlayer = PIECECOLOR_WHITE;
		send(sock, (char*)&SetPlayer, sizeof(SetPlayer), 0);
		bSetPlayerWhite = true;
		sprintf(buf, "PlayerWhite Set!!");
		AddStrToLog(buf);
		return;
	}

	return;
}

void AddStrToLog(char * msg)
{
	SendMessage(g_LogBox, LB_ADDSTRING, 0, (LPARAM)msg);
	// 칸을 밀리게 합니다
	int count = (int)SendMessage(g_LogBox, LB_GETCOUNT, 0, 0);
	SendMessage(g_LogBox, LB_SETTOPINDEX, count - 1, 0);
}

// 소켓 함수 오류를 출력한 후 종료합니다.
void ErrorQuit(const char * msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// 소켓 함수 오류를 출력합니다.
void ErrorDisplay(const char * msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	char buf[BUFSIZE];
	sprintf(buf, "[%s] %s", msg, (const char*)lpMsgBuf);
	AddStrToLog(buf);

	LocalFree(lpMsgBuf);
}

// 소켓 함수 오류를 출력합니다.
void ErrorDisplay(int errorCode)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	char buf[BUFSIZE];
	sprintf(buf, "[오류] %s", (const char*)lpMsgBuf);
	AddStrToLog(buf);

	LocalFree(lpMsgBuf);
}
