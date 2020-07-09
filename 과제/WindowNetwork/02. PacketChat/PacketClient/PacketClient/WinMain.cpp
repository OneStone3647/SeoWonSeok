#include "Mecro.h"
#include "resource.h"


// WINAPI ����
HWND	g_hWndList;		// ä��â
HWND	g_hWnd;

// WINSOCK ����
SOCKET			Sock;
SOCKADDR_IN	ServerAddr;
HANDLE			SendThread;
HANDLE			RecvThread;

bool		g_bIsSend;

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Init(HWND hWnd);
void Connect(HWND hWnd);					// ����
unsigned WINAPI Send(void* arg);
unsigned WINAPI Recv(void* arg);
void AddStrToList(HWND hWnd, char* msg);
void ErrorHandling(HWND hWnd, const char* msg);		// ����
void Release(HWND hWnd);				// ����

// API�� Main�Լ�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// ��ȭ���� ����
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, (DLGPROC)&DlgProc);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		// �ʱ�ȭ
	case WM_INITDIALOG:
		Init(hWnd);
		return TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_SEND)
		{
			g_bIsSend = true;
			return TRUE;
		}
		if (LOWORD(wParam) == ID_END)
		{
			EndDialog(hWnd, LOWORD(wParam));
			Release(hWnd);
			return TRUE;
		}
		break;
	case WM_CLOSE:
		EndDialog(hWnd, LOWORD(wParam));
		Release(hWnd);
		return TRUE;
	}

	return FALSE;
}

void Init(HWND hWnd)
{
	g_hWnd = hWnd;
	g_bIsSend = false;
	// ����Ʈ�ڽ� �ڵ� ���ϱ�
	g_hWndList = GetDlgItem(hWnd, IDC_LIST1);
	Connect(hWnd);
}

void Connect(HWND hWnd)
{
	// ���� �ʱ�ȭ
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling(hWnd, "WSAStartup() Error!!");
	}

	// ���� ����
	Sock = socket(PF_INET, SOCK_STREAM, 0);

	// ���� �ּ� ����
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerAddr.sin_port = htons(9000);

	// ������ ����
	if (connect(Sock, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		ErrorHandling(hWnd, "connect() Error!!");
	}

	// Thread ����
	SendThread = (HANDLE)_beginthreadex(NULL, 0, Send, (void*)&Sock, 0, NULL);
	RecvThread = (HANDLE)_beginthreadex(NULL, 0, Recv, (void*)&Sock, 0, NULL);
}

unsigned WINAPI Send(void * arg)
{
	SOCKET sock = *((SOCKET*)arg);
	char buf[BUF_SIZE];
	PACKET tmpPacket;
	while (true)
	{
		if (g_bIsSend)
		{
			// IDC_EDIT1���� ���� ����
			GetDlgItemText(g_hWnd, IDC_EDIT1, buf, BUF_SIZE);
			tmpPacket.login = LOGIN_SUCCESS;
			strcpy(tmpPacket.msg, buf);
			send(sock, (char*)&tmpPacket, sizeof(PACKET), 0);
			
			// ������ ���� ����
			SetDlgItemText(g_hWnd, IDC_EDIT1, "");
			SetFocus(GetDlgItem(g_hWnd, IDC_EDIT1));
			g_bIsSend = false;
		}
	}
	return 0;
}

unsigned WINAPI Recv(void * arg)
{
	SOCKET sock = *((SOCKET*)arg);
	int len = 0;
	char buf[BUF_SIZE];

	while (true)
	{
		len = recv(sock, buf, sizeof(buf) - 1, 0);
		buf[len] = '\n';

		PACKET* tmpPacket = (PACKET*)buf;
		AddStrToList(g_hWndList, tmpPacket->msg);
	}

	while ((len = recv(sock, buf, sizeof(buf) - 1, 0)) != 0)
	{
		// ���� ����
		if (len == SOCKET_ERROR)
		{
			break;
		}

		buf[len] = '\n';

		PACKET* tmpPacket = (PACKET*)buf;
		AddStrToList(g_hWndList, tmpPacket->msg);
	}
	return 0;
}

void AddStrToList(HWND hWnd, char * msg)
{
	SendMessage(hWnd, LB_ADDSTRING, 0, (LPARAM)msg);
	// ĭ�� �и��� ��
	int count = (int)SendMessage(hWnd, LB_GETCOUNT, 0, 0);
	SendMessage(hWnd, LB_SETTOPINDEX, count - 1, 0);
}

void ErrorHandling(HWND hWnd, const char * msg)
{
	MessageBox(hWnd, TEXT(msg), TEXT("Error!!"), MB_OK);
}

void Release(HWND hWnd)
{
	// Thread ���� ��ٸ��� �Լ�
	WaitForSingleObject(SendThread, INFINITE);
	WaitForSingleObject(RecvThread, INFINITE);
	// ������ �ݴ´�.
	closesocket(Sock);
	// ���� ����
	WSACleanup();
}
