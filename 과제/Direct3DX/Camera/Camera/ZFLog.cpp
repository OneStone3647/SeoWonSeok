#include "ZFLog.h"
#include <time.h>


ZFLog::ZFLog(UINT32 nTarget, LPSTR szFilename)
{
	m_nTarget = nTarget;

	if (nTarget & ZF_LOG_TARGET_FILE)
	{
		strcpy(m_szFilename, szFilename);
	}
	else
	{
		m_szFilename[0] = NULL;
	}

	if (nTarget & ZF_LOG_TARGET_WINDOW)
	{
		CreateLogWindow();
	}
	else
	{
		m_hWnd = NULL;
	}

	Log("F-Killer Logging Starteg...");
}

ZFLog::~ZFLog()
{
	DestroyWindow(m_hWnd);
}

void ZFLog::CreateLogWindow()
{
	int			x, y, cx, cy;
	WNDCLASS	wc;
	RECT		rc;

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)ZFLog::WndProcZFLog;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "ZLogWindow";

	RegisterClass(&wc);

	cx = ZF_LOG_WINDOW_CX;
	cy = ZF_LOG_WINDOW_CY;
	x = GetSystemMetrics(SM_CXSCREEN) - cx;
	y = 0;

	m_hWnd = CreateWindow("ZLogWindow", ZF_LOG_WINDOW_TITLE, WS_POPUP | WS_CAPTION, x, y, cx, cy, NULL, NULL, GetModuleHandle(NULL), NULL);
	GetClientRect(m_hWnd, &rc);
	m_hWndList = CreateWindow("LISTBOX", "", WS_CHILD | WS_VSCROLL, 0, 0, rc.right, rc.bottom, m_hWnd, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(m_hWnd, SW_SHOW);
	ShowWindow(m_hWndList, SW_SHOW);
}

int ZFLog::Log(const char * fmt, ...)
{
	char	buff[1024];
	char	date[128];
	char	time[128];

	_strdate(date);
	_strtime(time);
	vsprintf(buff, fmt, (char*)(&fmt + 1));

	// Console에 출력할 경우
	if (m_nTarget & ZF_LOG_TARGET_CONSOLE)
	{
		printf("(date[%s] time[%s]) : %s\n", date, time, buff);
	}

	// Log File에 출력할 경우
	if (m_nTarget & ZF_LOG_TARGET_FILE)
	{
		FILE* fp = NULL;
		fp = fopen(m_szFilename, "a+");
		if (fp)
		{
			fprintf(fp, "(date[%s] time[%s]): %s\n", date, time, buff);
			fclose(fp);
		}
	}

	// Log Window에 출력할 경우
	if (m_nTarget & ZF_LOG_TARGET_WINDOW)
	{
		SendMessageA(m_hWndList, LB_ADDSTRING, 0, (LPARAM)buff);
		UINT32 n = SendMessageA(m_hWndList, LB_GETCOUNT, 0, 0L) - 1;
		SendMessageA(m_hWndList, LB_SETCURSEL, (WPARAM)n, 0L);
	}

	return 1;
}

LRESULT CALLBACK
ZFLog::WndProcZFLog(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
