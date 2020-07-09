#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "resource.h"
#include <time.h>

using namespace std;

enum DIRECTION
{
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP
};

// 윈도우 창의 크기는 테두리와 캡션의 크기까지 합한 크기이다.
// 작업영역의 크기를 1000x1000로 만들려면 1016x1038으로 생성해야 한다.
// 메뉴 추가시 가로 20추가

// 윈도우 창 전체 크기
#define WindowWidth		1616
#define WindowHeight		958

#define WindowPosX		200
#define WindowPosY		100

#define GameWidth			1200
#define GameHeight		900

#define MaptoolWidth		1600
#define MaptoolHeight		900

#define BlockSizeX			66
#define BlockSizeY			50

#define MapSizeX			15
#define MapSizeY			15