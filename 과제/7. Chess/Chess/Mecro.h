#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

// ���밪�� ���ϴ� ��ũ��.
#define ABVALUE(x) ((x) < 0 ? -(x) : (x))

#define BLOCKX 125
#define BLOCKY 125

#define PIECEMAX 16

#define BOARDX 8
#define BOARDY 8
#define BOARDMAX 64

#define FIELDCOUNTMAX 3		// �ʵ��� ����
#define PIECECOUNTMAX 6		// �ǽ��� ����
