#pragma once
#include <WinSock2.h>		// windows.h���� ���� ����Ǿ�� �浹���� �ʴ´�.
#include <windows.h>
#include <process.h>
#include <iostream>

using namespace std;

#define BUF_SIZE	 512
#define WINDOWWIDTH	 480
#define WINDOWHEIGHT 600

enum LOGIN
{
	LOGIN_SUCCESS = 0,
	LOGIN_FAILED
};

// ��Ŷ
#pragma pack(push, 1)	// 1����Ʈ ������ ����
struct PACKET
{
	int login;
	char msg[256];
};
#pragma pack(pop)	// ���� ������ ���� ����(�⺻��)�� ����