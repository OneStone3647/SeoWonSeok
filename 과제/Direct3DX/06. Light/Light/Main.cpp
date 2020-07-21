/*=============================================================================
 * Light
 *=============================================================================*/
#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include "Vertex.h"

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768

 /*=============================================================================
  * 전역 변수
  *=============================================================================*/
LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

Vertex				VT;

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

	// Z버퍼 사용을 위한 설정
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
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 버퍼 기능을 켭니다.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

/*=============================================================================
 * 기하 정보 초기화
 *=============================================================================*/
HRESULT InitGeometry()
{
	if (FAILED(VT.InitVB(g_pd3dDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}

/*=============================================================================
 * 초기화 객체를 Release
 *=============================================================================*/
void Release()
{
	if (VT.GetVB() != NULL)
	{
		VT.GetVB()->Release();
	}

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
 * 행렬 설정: 행렬에는 3가지가 있으며, 각각 월드, 뷰, 프로젝션 행렬입니다.
 *=============================================================================*/
void SetupMatrices()
{
	// 월드 행렬
	D3DXMATRIXA16 matWorld;
	
	D3DXMatrixIdentity(&matWorld);		// 월드 행렬을 단위 행렬로 생성합니다.
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);	// 생성한 단위 행렬을 월드 행렬로 디바이스에 설정합니다.

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
	// 첫 번째 : 설정될 행렬
	// 두 번째 : 시야각
	// 세 번째 : 종횡비
	// 네 번째 : 근접 클리핑
	// 다섯 번째 : 원거리 클리핑
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// 생성한 프로젝션 행렬을 디바이스에 설정합니다.
}

/*=============================================================================
 * 광원 설정
 *=============================================================================*/
void SetupLights()
{
	// 재질 설정
	// 재질은 디바이스에 단 하나만 설정될 수 있습니다.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pd3dDevice->SetMaterial(&mtrl);

	// 광원 설정
	D3DXVECTOR3 vecDir;
	// 방향성 광원(directional light)이 향한 빛의 방향
	// 광원 구조체
	D3DLIGHT9 light;
	D3DLIGHT9 spotlight;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	// 광원의 확산광 색깔의 밝기를 지정합니다.
	// 광원의 종류를 설정한다(포인트 라이트, 다이렉션 라이트, 스포트 라이트)
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	spotlight.Type = D3DLIGHT_DIRECTIONAL;
	spotlight.Diffuse.r = 1.0f;
	spotlight.Diffuse.g = 1.0f;
	spotlight.Diffuse.b = 1.0f;
	spotlight.Direction = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	//광원의 방향 설정
	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 350.0f), 1.0f, sinf(timeGetTime() / 350.0f));

	//광원의 방향을 단위 벡터로 만듭니다.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f; // 광원이 다다를 수 있는 최대거리
	g_pd3dDevice->SetLight(0, &light); // 디바이스에 광원 0번을 설치
	g_pd3dDevice->LightEnable(0, TRUE); // 광원 0번을 활성화 합니다.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);// 광원 설정을 활성화 합니다.

	//환경 광원의 값 설정
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

/*=============================================================================
 * 화면 그리기
 *=============================================================================*/
void Render()
{
	D3DXMATRIXA16 matWorld;

	// 후면 버퍼를 파란색(0, 0, 255)으로 지우고 Z버퍼를 사용하기 위해 초기화합니다.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	SetupLights();

	SetupMatrices();

	// 랜더링 시작
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// 정점 정보가 담겨 있는 정점 버퍼를 출력 스트림으로 할당합니다.
		g_pd3dDevice->SetStreamSource(0, VT.GetVB(), 0, sizeof(CUSTOMVERTEX));

		// D3D에게 정점 셰이더 정보를 지정합니다.
		// 대부분 FCF만 지정합니다.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// 기하 정보를 출력하기 위한 DrawPrimitive() 함수를 호출합니다.
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2);

		// 랜더링 종료
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
		L"D3D Light", NULL };

	// winclass 레지스터에 등록합니다.
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D Light", L"D3D Light", WS_OVERLAPPEDWINDOW, 100, 100, WINDOWWIDTH, WINDOWHEIGHT,
		GetDesktopWindow(), NULL, NULL, wc.hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitGeometry()))
		{
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

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
	UnregisterClass(L"D3D Light", wc.hInstance);
	return 0;
}