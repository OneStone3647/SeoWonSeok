#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include "resource.h"
#include "Singleton.h"

using namespace std;

// ������ â�� ũ��� �׵θ��� ĸ���� ũ����� ���� ũ���̴�.
// �۾������� ũ�⸦ 1000x1000�� ������� 1016x1038���� �����ؾ� �Ѵ�.
// �޴� �߰��� ���� 20�߰�

// ������ â ��ü ũ��
#define WindowWidth		1616
#define WindowHeight		958

#define GameWidth			600
#define GameHeight		560

#define MaptoolWidth		1600
#define MaptoolHeight		900

#define BlockSizeX			33
#define BlockSizeY			25

#define MapSizeX			14
#define MapSizeY			14