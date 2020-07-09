#pragma once
#include <WinSock2.h>		// windows.h보다 위에 선언되어야 충돌하지 않는다.
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <process.h> 

using namespace std;

// 말의 위치를 저장할 구조체입니다.
struct PIECEPOINT
{
	int x;
	int y;
};

// 피스의 색
enum PIECECOLOR
{
	PIECECOLOR_BLACK = 1,
	PIECECOLOR_WHITE
};

// 절대값을 구하는 매크로입니다.
#define ABVALUE(x) ((x) < 0 ? -(x) : (x))

// 윈도우 크기입니다.
#define WINDOWWIDTH	1038
#define WINDOWHEIGHT	1016

// 블록비트맵의 크기입니다.
#define BLOCKBIT_X 125
#define BLOCKBIT_Y 125

// 보드의 칸 수 입니다.
#define BOARD_X 8
#define BOARD_Y 8
#define BOARD_BLOCKMAX 64

// 플레이어가 가질 피스의 총 개수입니다.
#define PIECEMAX 16
// 피스의 종류 수입니다.
#define PIECECOUNTMAX 6

// 네트워크 관련 매크로입니다.
#define SERVERPORT 9000
#define BUFSIZE			512
#define WM_SOCKET (WM_USER +1) // 네트워크 이벤트를 전달할 사용자 정의 윈도우 메시지

#define PLAYER