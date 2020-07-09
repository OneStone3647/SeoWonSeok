#include "Mecro.h"

// ���� ������ ������ ����ü
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE + 1];
	int recvBytes;
	int sendBytes;
	BOOL recvDelayed;
	SOCKETINFO* next;
};

// ���� ��ġ�� ������ ����ü
struct PiecePoint
{
	int prev_X;
	int prev_Y;
	int cur_X;
	int cur_Y;
};

// �ǽ��� ��
enum PIECECOLOR
{
	PIECECOLOR_BLACK = 1,
	PIECECOLOR_WHITE
};

// ���� ������ ���� ����ü�� ���Ḯ��Ʈ
SOCKETINFO* SocketInfoList;

SOCKET PlayerBlack = NULL;
SOCKET PlayerWhite = NULL;
bool bSetPlayerBlack = false;
bool bSetPlayerWhite = false;

HWND g_hWnd;
HWND g_LogBox;	// �α׸� ǥ���� â
HINSTANCE g_hInst;	// �۷ι� �ν��Ͻ� �ڵ鰪
LPCTSTR IpszClass = TEXT("ChessServer");	// â �̸�

// WINDOW �޽��� ó��
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
// ���� �޽��� ó��
void ProcessSocketMessage(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
// ���� ���� �Լ�
BOOL AddSocketInfo(SOCKET sock);
SOCKETINFO* GetSocketInfo(SOCKET sock);
SOCKETINFO* GetAnotherSocketInfo(SOCKET sock);
void RemoveSocketInfo(SOCKET sock);

// ������ Ŭ���̾�Ʈ�� ������� �÷��̾ ������ �ǽ��� ������ �´� ���� �����մϴ�.
void SetClient(SOCKET sock);

// �α� �ڽ��� �ؽ�Ʈ�� ����ϴ� �Լ�
void AddStrToLog(char* msg);

// ���� ��� �Լ�
void ErrorQuit(const char* msg);
void ErrorDisplay(const char* msg);
void ErrorDisplay(int errorCode);

// WinAPI�� Main�Լ�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	WSADATA wsaData;
	SOCKET serverSock, clientSock;
	SOCKADDR_IN serverAddr, clientAddr;
	int retval;

	MSG Message;
	WNDCLASS WndClass;		// �⺻ ������ ȯ���� ����� ����ü�Դϴ�.
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;	// ���࿵��
	WndClass.cbWndExtra = 0;	// ���࿵��
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	// ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		// Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// ������ ���
	WndClass.hInstance = hInstance;		// ���α׷� �ڵ鰪(��ȣ) ����մϴ�.
	WndClass.lpfnWndProc = WndProc;		// ���μ��� �Լ� ȣ���Ѵ�.
	WndClass.lpszClassName = IpszClass;		// Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	// �������� ������ ������ ����Ǹ� �ٽ� �׸��ϴ�.
	RegisterClass(&WndClass);	// ������� WndClass�� ����մϴ�.

	// ������ â�� ũ��� �׵θ��� ĸ���� ũ����� ���� ũ���Դϴ�.
	// �۾������� ũ�⸦ 1000x1000�� ������� 1038x1016���� �����ؾ� �մϴ�.
	g_hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOWWIDTH + 38, WINDOWHEIGHT + 16, NULL,
		(HMENU)NULL, hInstance, NULL);
	if (g_hWnd == NULL)
	{
		return 1;
	}

	ShowWindow(g_hWnd, nCmdShow);
	// ��ȿȭ ����(������ �������� �Ϻΰ� �ٸ� ������ � �������ų� �������� �Ǿ��� ���)�� ���Ž����ִ� �Լ��Դϴ�.
	UpdateWindow(g_hWnd);

	// ������ �ʱ�ȭ�մϴ�.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorQuit("WSAStartup() Error!");
	}

	// socket()
	// ������ �����մϴ�.
	serverSock = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSock == INVALID_SOCKET)
	{
		ErrorQuit("socket() Error!");
	}
	// ����ü�� �ʱ�ȭ�մϴ�.
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(9000);

	// bind()
	// ���� IP �ּҿ� ������Ʈ ��ȣ�� �����մϴ�.
	retval = bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (retval == SOCKET_ERROR)
	{
		ErrorQuit("bind() Error!");
	}

	// listen()
	// Ŭ���̾�Ʈ�� ���� ���� �غ� �մϴ�.
	retval = listen(serverSock, SOMAXCONN);
	if (retval == SOCKET_ERROR)
	{
		ErrorQuit("listen() Error!");
	}

	// WSAAsySelect()
	// FD_ACCEPT, FD_CLOSE �̺�Ʈ�� ����մϴ�.
	// FD_ACCEPT: ������ Ŭ���̾�Ʈ�� �ִ�.
	// FD_CLOSE: ��밡 ������ �����ߴ�.
	retval = WSAAsyncSelect(serverSock, g_hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
	if (retval == SOCKET_ERROR)
	{
		ErrorQuit("WSAAsynSelect Error!");
	}

	while (GetMessage(&Message, NULL, 0, 0))	// ����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽����� ���� ��� �����մϴ�.)
	{
		TranslateMessage(&Message);		// Ű���� �Է� �޽��� ó���Լ��Դϴ�.
		DispatchMessage(&Message);		// ���� �޽����� WndProc�� �����ϴ� �Լ��Դϴ�.
	}

	// ���� ����
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
		//����� ���� �޽����� �ް� �Ǹ� ó���ϴ� �κ��Դϴ�.
		//�޽��� ó���� ���� ������ ����� ��츦 ����ؼ� ���� �޽����� ó���ϴ� �Լ��� ������ݴϴ�.
		//������ �޽����� �״�� ó���ؾ��ϱ⶧���� ���ڸ� �״�� �Ѱ��ִ� ��Ʈ��ũ �޽��� ó�� �Լ��� ����� �ݴϴ�.
	case WM_SOCKET://���� ���� ������ �޽���
		ProcessSocketMessage(hWnd, iMessage, wParam, lParam);
		break;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� �����ϴ�.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ���ϴ�.
	}
	// case�� �ִ� �޽����� ������ ������ �޽����� ó���մϴ�.
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

// ���� ���� ������ �޽����� ó���ϴ� �Լ� �Դϴ�.
void ProcessSocketMessage(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	SOCKETINFO* recvSock;
	SOCKETINFO* sendSock;
	SOCKET clientSock;
	SOCKADDR_IN clientAddr;
	int addrLen;
	int retval;
	char buf[BUFSIZE];

	// ���� ���� ���θ� Ȯ���մϴ�.
	if (WSAGETSELECTERROR(lParam))
	{
		ErrorDisplay(WSAGETSELECTERROR(lParam));
		RemoveSocketInfo(wParam);
		return;
	}

	// �޽����� ó���մϴ�.
	switch ((WSAGETSELECTEVENT(lParam)))
	{
		// ���� �Լ�: accept()
		// accept() �Լ��� ȣ���ϰ� ���� ���� Ȯ���Ͽ� ������ ó���Ѵ�.
	case FD_ACCEPT:
		addrLen = sizeof(clientAddr);
		clientSock = accept(wParam, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSock == INVALID_SOCKET)
		{
			ErrorDisplay("accept() Error!");
			return;
		}

		sprintf(buf, "[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d",
			inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
		AddStrToLog(buf);

		// ������ Ŭ���̾�Ʈ ������ ����մϴ�.
		AddSocketInfo(clientSock);

		// FD_READ, FD_WRITE, FD_CLOSE�� ����մϴ�.
		retval = WSAAsyncSelect(clientSock, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
		if (retval == SOCKET_ERROR)
		{
			ErrorDisplay("SWAAsyncSelect() Error!");
			RemoveSocketInfo(clientSock);
		}

		break;

		// �����Լ�: recv(), recvfrom()
	case FD_READ:
		// ���� ���� ����ü�� �޽��ϴ�.
		recvSock = GetSocketInfo(wParam);
		if (recvSock == nullptr)
		{
			return;
		}
		// �̹��� �޾����� ���� ������ ���� �����Ͱ� �ִٸ� �޾Ҵٴ� ��Ǹ� ����ϰ� �����մϴ�.
		if (recvSock->recvBytes > 0)
		{
			recvSock->recvDelayed = TRUE;
			return;
		}

		// �����͸� �޽��ϴ�.
		retval = recv(recvSock->sock, recvSock->buf, BUFSIZE, 0);
		if (retval == SOCKET_ERROR)
		{
			ErrorDisplay("recv() Error!");
			RemoveSocketInfo(wParam);
			return;
		}

		recvSock->recvBytes = retval;

		// ���� �����͸� ����մϴ�.
		recvSock->buf[retval] = '\n';
		//addrLen = sizeof(clientAddr);
		//// ���Ͽ� �ش��ϴ� SOCKADDR_IN ����ü ������ �� ��° ���ڿ� �����մϴ�.
		//getpeername(wParam, (SOCKADDR*)&clientAddr, &addrLen);

		//sprintf(buf, "[TCP / %s:%d] % s",
		//	inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), tmpSock->buf);
		//AddStrToLog(buf);

		//// ���� ������ Ŭ�� ������ �����ߴٴ� ������ ���
		//if (retval == sizeof(bool) && (bool)recvSock->buf == true)
		//{
		//	SetClient(recvSock->sock);
		//}
		// ���� ������ �ǽ��� ��ġ�� ���
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

		// Write���� ó���ؾ� �ϱ� ������ break���� �����ϴ�.

		// �����Լ�: send(), sendto()
	case FD_WRITE:
		recvSock = GetSocketInfo(wParam);
		sendSock = GetAnotherSocketInfo(wParam);

		// ���� ������ Ŭ�� ������ �����ߴٴ� ������ ���
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

		// ������ ������
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

		// ���� �����͸� ��� ���´��� üũ�մϴ�.
		// �޾����� ������ ���� ���� �� TRUE�θ� ������ �����͵��� �����ϴ�.
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

// ���� ������ ���Ḯ��Ʈ�� �߰��ϴ� �Լ��Դϴ�.
BOOL AddSocketInfo(SOCKET sock)
{
	SOCKETINFO* tmpSock = new SOCKETINFO;
	if (tmpSock == nullptr)
	{
		MessageBox(g_hWnd, TEXT("[����] �޸𸮰� �����մϴ�"), TEXT("Error"), MB_OK);
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

// ���� ������ ���Ḯ��Ʈ ��� �Լ��Դϴ�.
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

// ���Ḯ��Ʈ���� ���� ������ �����ϴ� �Լ��Դϴ�.
void RemoveSocketInfo(SOCKET sock)
{
	SOCKADDR_IN tmpClientAddr;
	int addrLen = sizeof(tmpClientAddr);
	// ���Ͽ� �ش��ϴ� SOCKADDR_IN ����ü ������ �� ��° ���ڿ� �����մϴ�.
	getpeername(sock, (SOCKADDR*)&tmpClientAddr, &addrLen);

	char buf[BUFSIZE];
	sprintf(buf, "[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d",
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
	// ĭ�� �и��� �մϴ�
	int count = (int)SendMessage(g_LogBox, LB_GETCOUNT, 0, 0);
	SendMessage(g_LogBox, LB_SETTOPINDEX, count - 1, 0);
}

// ���� �Լ� ������ ����� �� �����մϴ�.
void ErrorQuit(const char * msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

// ���� �Լ� ������ ����մϴ�.
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

// ���� �Լ� ������ ����մϴ�.
void ErrorDisplay(int errorCode)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	char buf[BUFSIZE];
	sprintf(buf, "[����] %s", (const char*)lpMsgBuf);
	AddStrToLog(buf);

	LocalFree(lpMsgBuf);
}
