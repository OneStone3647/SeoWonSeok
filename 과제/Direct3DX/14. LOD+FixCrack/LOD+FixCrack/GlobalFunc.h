#ifndef _GLOBALFUNC_H_
#define _GLOBALFUNC_H_

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// 2�� ������ �ϴ� ���� n�� �α� ���� ���մϴ�.
int Log2(int n);

// 2^n���� ���մϴ�
int Pow2(int n);

// pt�� rc �ȿ� ���ԵǴ��� �˻��մϴ�.(PtInRect()��� API�Լ��� ����(-)�� ó���� ���Ѵ�.)
BOOL IsInRect(RECT* rc, POINT pt);

#endif // _GLOBALFUNC_H_