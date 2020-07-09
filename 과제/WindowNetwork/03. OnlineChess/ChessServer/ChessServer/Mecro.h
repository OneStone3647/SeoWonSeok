#pragma once
#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE			512
#define WM_SOCKET (WM_USER +1) // 네트워크 이벤트를 전달할 사용자 정의 윈도우 메시지

#define WINDOWWIDTH	600
#define WINDOWHEIGHT	400

#define ID_LISTBOX		100