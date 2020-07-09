#pragma once
#include <WinSock2.h>		// windows.h보다 위에 선언되어야 충돌하지 않습니다.
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h> 
#include <vector>
#include <string>
#include "Singleton.h"

using namespace std;

// 네트워크 관련 매크로입니다.
#define SERVERPORT			9000
#define BUFSIZE				512

enum COLOR
{
	COLOR_BLACK = 0,
	COLOR_WHITE,
	COLOR_RED,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_YELLOW
};

// 정보를 구분하는 enum입니다.
enum INFOINDEX
{
	INFOINDEX_POINT = 0,
	INFOINDEX_ANSWER
};

struct InfoPoint
{
	int		infoIndex;
	int		color;
	POINT	point;
};

struct InfoAnswer
{
	int		infoIndex;
	char	answer[BUFSIZE];
};

// 윈도우 창의 크기는 테두리와 캡션의 크기까지 합한 크기입니다.
// 작업영역의 크기를 1000x1000로 만들려면 1038x1016으로 생성해야 합니다.
// 윈도우 크기입니다.
#define WINDOWWIDTH		1238
#define WINDOWHEIGHT		816

// 리스트 박스 ID입니다.
#define ID_CHATBOX			100
// 리스트 박스 크기입니다.
#define CHATWIDTH			200
#define CHATHEIGHT			600

// 에디트 박스 ID입니다.
#define ID_EDITBOX			200
// 에디트 박스 크기입니다.
#define EDITWIDTH				200
#define EDITHEIGHT			20

// 그림을 그리는 곳의 크기입니다.
#define PAINTBOXLEFT				250
#define PAINTBOXTOP				100
#define PAINTBOXRIGHT			950
#define PAINTBOXBOTTOM		600
#define PAINTBOXWIDTH			700
#define PAINTBOXHEIGHT			500

// 도구를 모아둔 곳의 크기입니다.
#define TOOLBOXLEFT				250
#define TOOLBOXTOP				620
#define TOOLBOXRIGHT			950
#define TOOLBOXBOTTOM		700

// 더블 버퍼링 크기입니다.
// (0, 0)에서 (PAINTBOXRIGHT, TOOLBOXBOTTOM + 10)까지의 범위입니다.
#define DUBBLEBUFWIDTH		950
#define DUBBLEBUFHEIGHT		710