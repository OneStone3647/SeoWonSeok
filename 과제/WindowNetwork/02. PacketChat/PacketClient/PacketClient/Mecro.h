#pragma once
#include <WinSock2.h>		// windows.h보다 위에 선언되어야 충돌하지 않는다.
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

// 패킷
#pragma pack(push, 1)	// 1바이트 단위로 정렬
struct PACKET
{
	int login;
	char msg[256];
};
#pragma pack(pop)	// 정렬 설정을 이전 상태(기본값)로 돌림