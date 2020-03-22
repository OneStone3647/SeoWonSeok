#pragma once
#include <Windows.h>
#include "resource.h"
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

enum MOUSECLICK
{
	MOUSECLICK_IDLE,
	MOUSECLICK_LEFT,
	MOUSECLICK_RIGHT
};

// ������ â�� ũ��� �׵θ��� ĸ���� ũ����� ���� ũ���̴�.
// �۾������� ũ�⸦ 1000x1000�� ������� 1016x1038���� �����ؾ� �Ѵ�.
// �޴� �߰��� ���� 20�߰�

// ������ â ��ü ũ��
#define WindowWidth					1616
#define WindowHeight					958
#define ScreenWidth					1600
#define ScreenHeight					900

#define BlockSize						40
#define BlockStartXEasy				18
#define BlockStartYEasy				38
#define BlockStartXNormal			32
#define BlockStartYNormal			64
#define BlockStartXHard				32
#define BlockStartYHard				64

// 9x9���� ũ��
#define WindowWidthEasy			414
#define WindowHeightEasy			498
#define ScreenWidthEasy				398
#define ScreenHeightEasy				438
#define TimerPosXEasy					80
#define TimerPosYEasy					410
#define MineCountPosXEasy			300
#define MineCountPosYEasy			410

// 16x16���� ũ��
#define WindowWidthNormal			726
#define WindowHeightNormal		830
#define ScreenWidthNormal			710
#define ScreenHeightNormal			772	
#define TimerPosXNormal				150
#define TimerPosYNormal				730
#define MineCountPosXNormal		550
#define MineCountPosYNormal		730	

// 16x30���� ũ��
#define WindowWidthHard			1316
#define WindowHeightHard			830
#define ScreenWidthHard				1300
#define ScreenHeightHard				772
#define TimerPosXHard				300
#define TimerPosYHard				730
#define MineCountPosXHard			1000
#define MineCountPosYHard			730
