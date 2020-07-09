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

// ������ â�� ũ��� �׵θ��� ĸ���� ũ����� ���� ũ���̴�.
// �۾������� ũ�⸦ 1000x1000�� ������� 1016x1038���� �����ؾ� �Ѵ�.
// �޴� �߰��� ���� 20�߰�

// ������ â ��ü ũ��
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