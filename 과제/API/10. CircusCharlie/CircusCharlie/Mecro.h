#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <list>
#include <time.h>

using namespace std;

// ������ â ��ü ũ��
#define WindowWidth				1296
#define WindowHeight				758

// ������ ��µǴ� â ũ��
#define ScreenWidth				1280
#define ScreenHeight				720

// �ִ� �ʵ� ����
#define MaxField					12

// ������ �ʵ� �Ÿ�
#define LastFieldWidth				9700

// �ִ� Front ����
#define MaxFront					9

// �ִ� Enemy ��ȯ ����
#define MaxEnemy					4

enum STATE
{
	STATE_IDLE,
	STATE_MOVELEFT,
	STATE_MOVERIGHT,
	STATE_JUMP,
	STATE_LEFTJUMP,
	STATE_RIGHTJUMP,
	STATE_WIN,
	STATE_DIE
};