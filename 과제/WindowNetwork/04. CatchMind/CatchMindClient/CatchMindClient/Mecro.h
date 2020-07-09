#pragma once
#include <WinSock2.h>		// windows.h���� ���� ����Ǿ�� �浹���� �ʽ��ϴ�.
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h> 
#include <vector>
#include <string>
#include "Singleton.h"

using namespace std;

// ��Ʈ��ũ ���� ��ũ���Դϴ�.
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

// ������ �����ϴ� enum�Դϴ�.
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

// ������ â�� ũ��� �׵θ��� ĸ���� ũ����� ���� ũ���Դϴ�.
// �۾������� ũ�⸦ 1000x1000�� ������� 1038x1016���� �����ؾ� �մϴ�.
// ������ ũ���Դϴ�.
#define WINDOWWIDTH		1238
#define WINDOWHEIGHT		816

// ����Ʈ �ڽ� ID�Դϴ�.
#define ID_CHATBOX			100
// ����Ʈ �ڽ� ũ���Դϴ�.
#define CHATWIDTH			200
#define CHATHEIGHT			600

// ����Ʈ �ڽ� ID�Դϴ�.
#define ID_EDITBOX			200
// ����Ʈ �ڽ� ũ���Դϴ�.
#define EDITWIDTH				200
#define EDITHEIGHT			20

// �׸��� �׸��� ���� ũ���Դϴ�.
#define PAINTBOXLEFT				250
#define PAINTBOXTOP				100
#define PAINTBOXRIGHT			950
#define PAINTBOXBOTTOM		600
#define PAINTBOXWIDTH			700
#define PAINTBOXHEIGHT			500

// ������ ��Ƶ� ���� ũ���Դϴ�.
#define TOOLBOXLEFT				250
#define TOOLBOXTOP				620
#define TOOLBOXRIGHT			950
#define TOOLBOXBOTTOM		700

// ���� ���۸� ũ���Դϴ�.
// (0, 0)���� (PAINTBOXRIGHT, TOOLBOXBOTTOM + 10)������ �����Դϴ�.
#define DUBBLEBUFWIDTH		950
#define DUBBLEBUFHEIGHT		710