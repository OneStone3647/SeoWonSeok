#pragma once
#include <WinSock2.h>		// windows.h���� ���� ����Ǿ�� �浹���� �ʴ´�.
#include <Windows.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <process.h> 

using namespace std;

// ���� ��ġ�� ������ ����ü�Դϴ�.
struct PIECEPOINT
{
	int x;
	int y;
};

// �ǽ��� ��
enum PIECECOLOR
{
	PIECECOLOR_BLACK = 1,
	PIECECOLOR_WHITE
};

// ���밪�� ���ϴ� ��ũ���Դϴ�.
#define ABVALUE(x) ((x) < 0 ? -(x) : (x))

// ������ ũ���Դϴ�.
#define WINDOWWIDTH	1038
#define WINDOWHEIGHT	1016

// ��Ϻ�Ʈ���� ũ���Դϴ�.
#define BLOCKBIT_X 125
#define BLOCKBIT_Y 125

// ������ ĭ �� �Դϴ�.
#define BOARD_X 8
#define BOARD_Y 8
#define BOARD_BLOCKMAX 64

// �÷��̾ ���� �ǽ��� �� �����Դϴ�.
#define PIECEMAX 16
// �ǽ��� ���� ���Դϴ�.
#define PIECECOUNTMAX 6

// ��Ʈ��ũ ���� ��ũ���Դϴ�.
#define SERVERPORT 9000
#define BUFSIZE			512
#define WM_SOCKET (WM_USER +1) // ��Ʈ��ũ �̺�Ʈ�� ������ ����� ���� ������ �޽���

#define PLAYER