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

// 윈도우 창의 크기는 테두리와 캡션의 크기까지 합한 크기이다.
// 작업영역의 크기를 1000x1000로 만들려면 1016x1038으로 생성해야 한다.
// 메뉴 추가시 가로 20추가

// 윈도우 창 전체 크기
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

// 9x9보드 크기
#define WindowWidthEasy			414
#define WindowHeightEasy			498
#define ScreenWidthEasy				398
#define ScreenHeightEasy				438
#define TimerPosXEasy					80
#define TimerPosYEasy					410
#define MineCountPosXEasy			300
#define MineCountPosYEasy			410

// 16x16보드 크기
#define WindowWidthNormal			726
#define WindowHeightNormal		830
#define ScreenWidthNormal			710
#define ScreenHeightNormal			772	
#define TimerPosXNormal				150
#define TimerPosYNormal				730
#define MineCountPosXNormal		550
#define MineCountPosYNormal		730	

// 16x30보드 크기
#define WindowWidthHard			1316
#define WindowHeightHard			830
#define ScreenWidthHard				1300
#define ScreenHeightHard				772
#define TimerPosXHard				300
#define TimerPosYHard				730
#define MineCountPosXHard			1000
#define MineCountPosYHard			730
