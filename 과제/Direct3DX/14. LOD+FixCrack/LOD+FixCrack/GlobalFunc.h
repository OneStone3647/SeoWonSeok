#ifndef _GLOBALFUNC_H_
#define _GLOBALFUNC_H_

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// 2를 밑으로 하는 숫자 n의 로그 값을 구합니다.
int Log2(int n);

// 2^n값을 구합니다
int Pow2(int n);

// pt가 rc 안에 포함되는지 검사합니다.(PtInRect()라는 API함수는 음수(-)값 처리를 못한다.)
BOOL IsInRect(RECT* rc, POINT pt);

#endif // _GLOBALFUNC_H_