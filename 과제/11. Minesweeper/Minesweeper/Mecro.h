#pragma once
#include <Windows.h>
#include "resource.h"

// 윈도우 창의 크기는 테두리와 캡션의 크기까지 합한 크기이다.
// 작업영역의 크기를 1000x1000로 만들려면 1016x1038으로 생성해야 한다.
// 메뉴 추가시 가로 20추가

// 윈도우 창 전체 크기
#define WindowWidth				1616
#define WindowHeight				958
#define ScreenWidth				1600
#define ScreenHeight				900

#define BlockSize					40
#define BlockStartX9				18
#define BlockStartY9				38
#define BlockStartX16				32
#define BlockStartY16				64
#define BlockStartX30				32
#define BlockStartY30				64

// 9x9보드 크기
#define WindowWidth9			414
#define WindowHeight9			498
#define ScreenWidth9				398
#define ScreenHeight9				438

// 16x16보드 크기
#define WindowWidth16			726
#define WindowHeight16			830
#define ScreenWidth16				710
#define ScreenHeight16			772		

// 16x30보드 크기
#define WindowWidth30			1316
#define WindowHeight30			830
#define ScreenWidth30				1300
#define ScreenHeight30			772