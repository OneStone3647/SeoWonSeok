#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

// 절대값을 구하는 매크로.
#define ABVALUE(x) ((x) < 0 ? -(x) : (x))

#define BLOCKX 125
#define BLOCKY 125

#define PIECEMAX 16

#define BOARDX 8
#define BOARDY 8
#define BOARDMAX 64

#define FIELDCOUNTMAX 3		// 필드의 종류
#define PIECECOUNTMAX 6		// 피스의 종류
