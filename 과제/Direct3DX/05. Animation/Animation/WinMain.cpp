/*=============================================================================
 * KeyFrameAnimation
 * 선형 보간을 이용한 애니메이션 처리
 * 부모, 자식의 회전, 이동 키를 각각 만들어서 적용
 *=============================================================================*/
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <cmath>

#include "GameManager.h"

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768


/*=============================================================================
 * 전역 변수
 *=============================================================================*/
LPDIRECT3D9			g_pD3D		 = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

GameManager	GM;

D3DXMATRIXA16		g_matTMParent;	// 부모의 기본 행렬
D3DXMATRIXA16		g_matRParent;	// 부모의 회전 행렬

D3DXMATRIXA16		g_matTMChild;	// 자식의 기본 행렬
D3DXMATRIXA16		g_matRChild;	// 자식의 회전 행렬

LPD3DXFONT			g_Font;
RECT				g_Rect;

float				g_fRot = 0.0f;
float				g_fRevRot = 0.0f;
float				g_X = 0.0f;
float				g_Y = 0.0f;

bool				g_bStart = true;

#define ROT_DELTA 0.1f;

D3DXVECTOR3		g_aniPos[2];
D3DXQUATERNION	g_aniRot[2];

/*=============================================================================
 * Direct3D 초기화
 *=============================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	// 디바이스를 생성하기 위한 D3D 객체를 생성합니다.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;				// 디바이스 생성을 위한 구조체입니다.
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// 반드시 ZeroMemory() 함수로 미리 구조체를 깨끗이 지워야 합니다.

	d3dpp.Windowed = TRUE;								// 창 모드로 생성합니다.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 가장 효율적인 SWAP 효과입니다.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	// 현재 바탕화면 모드에 맞춰서 후면 버퍼를 생성합니다.
	d3dpp.EnableAutoDepthStencil = TRUE;				// 길이가 있는 Z버퍼가 필요하므로 설정합니다.
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// 16비트의 깊이 버퍼 포맷으로 설정합니다.

	// 디바이스를 설정해서 생성합니다.
	// 디폴트 비디오카드를 사용하고, HAL 디바이스를 생성합니다.
	// 정점 처리는 모든 카드에서 지원하는 SW처리로 생성합니다.
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// 컬링을 설정합니다.
	/*==================================================================================
	* 옵션 플래그
	* D3DCULL_NONE: 후면 추려내기를 완전히 끕니다.
	* D3DCULL_CW: 시계 방향 두르기를 가진 삼각형을 추려냅니다.
	* D3DCULL_CCW: 시계 반대 방향 두르기를 가진 삼각형을 추려냅니다. 디폴트 상태입니다.
	*===================================================================================*/
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// 버퍼 기능을 켭니다.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// 광원 기능을 끕니다.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

/*=============================================================================
 * 애니메이션 초기화
 *=============================================================================*/
void InitAnimation()
{
	// 위치 변화에 사용할 벡터 값
	g_aniPos[0] = D3DXVECTOR3(0, 0, 0);		
	g_aniPos[1] = D3DXVECTOR3(5, 5, 5);

	FLOAT Yaw = D3DX_PI * 90.0f / 180.0f;	// Y축 90도 회전
	FLOAT Pitch = 0;
	FLOAT Roll = 0;

	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[0], Yaw, Pitch, Roll);	// 사원수(Y축 90도)

	Yaw = 0;
	Pitch = D3DX_PI * 90.0f / 180.0f;	// X축 90도 회전
	Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[1], Yaw, Pitch + g_fRot, Roll);	// 사원수(X축 90도)
}

/*=============================================================================
 * 기하 정보 초기화
 *=============================================================================*/
HRESULT InitGeometry()
{
	if (FAILED(GM.GetVertex()->InitVB(g_pd3dDevice)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetCube()->InitIB(g_pd3dDevice)))
	{
		return E_FAIL;
	}

	SetRect(&g_Rect, 100, 430, 0, 0);

	// 폰트 개체를 생성합니다.
	D3DXCreateFont(g_pd3dDevice, 20, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_Font);

	InitAnimation();

	return S_OK;
}

/*=============================================================================
 * 카메라 행렬 설정
 *=============================================================================*/
void SetupCamera()
{
	D3DXMatrixIdentity(GM.GetmatWorld());		// 월드 행렬을 단위 행렬로 생성합니다.
	g_pd3dDevice->SetTransform(D3DTS_WORLD, GM.GetmatWorld());	// 생성한 단위 행렬을 월드 행렬로 디바이스에 설정합니다.

	// 뷰 행렬(카메라)을 정의하기 위해서는 3가지 값이 필요합니다.
	D3DXVECTOR3 vEyePt(0.0f, 10.0f, -20.0f);		// 눈의 위치
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// 눈이 바라보는 위치(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		// 윗 방향을 나타내는 상방 벡터(0.0f, 1.0f, 0.0f)

	// 뷰 행렬(카메라)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);		// 3가지 Point를 이용해 뷰 행렬을 생성합니다.
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);					// 생성한 뷰 행렬을 디바이스에 설정합니다.

	// 프로젝션 행렬을 정의하기 위해서는 시야각(FOV = Field Of View)과 종횡비(aspect ratio), 클리핑 평면의 값이 필요합니다.
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// 생성한 프로젝션 행렬을 디바이스에 설정합니다.
}

/*=============================================================================
 * 애니메이션 행렬 생성
 *=============================================================================*/
void Animate()
{
	static float t = 0;
	static float add = 0.005;
	float x, y, z;
	D3DXQUATERNION quat;

	FLOAT Yaw = D3DX_PI * 90.0f / 180.0f;	// Y축 90도 회전
	FLOAT Pitch = 0;
	FLOAT Roll = 0;

	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[0], Yaw + g_fRevRot, Pitch + g_fRot, Roll);	// 사원수(Y축 90도)

	Yaw = 0;
	Pitch = D3DX_PI * 90.0f / 180.0f;	// X축 90도 회전
	Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[1], Yaw + g_fRevRot, Pitch + g_fRot, Roll);	// 사원수(X축 90도)

	D3DXVECTOR3 v;
	/*=============================================================================
	 * 이동값의 선형 보간
	 * D3DVECTOR3* D3DXVec3Lerp(D3DVECTOR3* pOut,
	 * D3DVECTOR3* v1,
	 * D3DVECTOR3* v2,
	 * FLOAT t);
	 * v1과 v2 사이의 선형 보간을 t 크기만큼 만들어 pOut에 저장한다.
	 *=============================================================================*/
	D3DXVec3Lerp(&v, &g_aniPos[0], &g_aniPos[1], t);
	// 이동 행렬값으로 변환
	D3DXMatrixTranslation(&g_matTMParent, v.x + g_X, v.y + g_Y, v.z);

	/*=============================================================================
	 * 회전값의 구면 선형 보간
	 * D3DXQUATERNION* D3DXQuaternionSlerp
	 * (D3DXQUATERNION *pOut,
	 * CONST D3DXQUATERNION *pQ1,
	 * CONST D3DXQUATERNION *pQ2);
	 * Q1과 Q2 사이의 구면 선형 보간을 t 크기만큼 만들어 pOut에 저장한다.
	 *=============================================================================*/
	D3DXQuaternionSlerp(&quat, &g_aniRot[0], &g_aniRot[1], t);
	// 사원수를 회전 행렬값으로 변환
	D3DXMatrixRotationQuaternion(&g_matRParent, &quat);

	if (g_bStart == true)
	{
		// 반대 방향으로 전환
		if (t<0.0f || t>1.0f)
		{
			add *= -1;
		}

		t += add;
	}

	// 자식 메시의 Z축 회전 행렬
	D3DXMatrixRotationZ(&g_matRChild, GetTickCount() / 500.0f);

	// 특정 vector를 축으로 하는 행렬
	//D3DXMatrixRotationAxis(&g_matRChild, nomalVec, Angle);

	// 자식 메시는 원점으로부터 (3, 3, 3)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMChild, 3, 3, 3);
}

/*=============================================================================
 * 초기화 객체를 Release
 *=============================================================================*/
void Release()
{
	GM.Release();

	// 해제 순서가 중요합니다.
	// 인터페이스 생성의 역순으로 해제합니다.
	if (g_pd3dDevice != NULL)
	{
		g_pd3dDevice->Release();
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
	}
}

/*=============================================================================
 * 메시 그리기
 *=============================================================================*/
void DrawMesh(D3DXMATRIXA16* pMat)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, pMat);
	g_pd3dDevice->SetStreamSource(0, GM.GetVertex()->GetVB(), 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	g_pd3dDevice->SetIndices(GM.GetCube()->GetIB());
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

/*=============================================================================
 * 화면 그리기
 *=============================================================================*/
void Render()
{
	D3DXMATRIXA16 matWorld;

	// 후면 버퍼를 파란색(0, 0, 255)으로 지우고 Z버퍼를 사용하기 위해 초기화합니다.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// 폰트 그리기
	if (g_bStart == true)
	{
		g_Font->DrawText(NULL, "START", -1, &g_Rect, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	else
	{
		g_Font->DrawText(NULL, "NOT START", -1, &g_Rect, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	Animate();

	// 랜더링 시작
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// 그리는 순서가 아닌 행렬 적용 순서가 중요합니다.
		
		// 부모의 변환을 만듭니다.
		// 회전 * 기본 변환
		matWorld = g_matRParent * g_matTMParent;
		// 적용된 변환을 기반으로 부모 객체를 그립니다.	
		DrawMesh(&matWorld);

		// 자식의 변환을 만듭니다.
		// 자식의 회전 * 자식의 기본 변환 * 부모의 회전 * 부모의 기본 변환
		matWorld = g_matRChild * g_matTMChild * g_matRParent * g_matTMParent;
		// 적용된 변환을 기반으로 부모 객체를 그립니다
		DrawMesh(&matWorld);

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*=============================================================================
 * 윈도우 프로시저
 *=============================================================================*/
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Release();
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			g_X -= ROT_DELTA;
		}

		if (wParam == VK_RIGHT)
		{
			g_X += ROT_DELTA;
		}

		if (wParam == VK_UP)
		{
			g_Y += ROT_DELTA;
		}

		if (wParam == VK_DOWN)
		{
			g_Y -= ROT_DELTA;
		}

		if (wParam == VK_SHIFT)
		{
			g_fRot += ROT_DELTA;
		}

		if (wParam == VK_RETURN)
		{
			g_fRevRot += ROT_DELTA;
		}

		if (wParam == VK_SPACE)
		{
			if (g_bStart == false)
			{
				g_bStart = true;
			}
			else
			{
				g_bStart = false;
			}

		}

		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*=============================================================================
 * WinMain
 *=============================================================================*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	// 윈도우 클래스를 등록합니다.
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"D3D Animation", NULL };

	// winclass 레지스터에 등록합니다.
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow("D3D Animation", "D3D Animation", WS_OVERLAPPEDWINDOW, 100, 100, WINDOWWIDTH, WINDOWHEIGHT,
		GetDesktopWindow(), NULL, NULL, wc.hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitGeometry()))
		{
			SetupCamera();

			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);
			GM.Init(hWnd);

			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					Render();
				}
			}
		}
	}

	// 등록된 레지시트 winclass를 릴리즈 합니다.
	UnregisterClass("D3D Animation", wc.hInstance);
	return 0;
}