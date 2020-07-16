/*=============================================================================
 * 태양계
 *=============================================================================*/
#pragma once
#include "GameManager.h"

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768

/*=============================================================================
 * 전역 변수
 *=============================================================================*/
LPDIRECT3D9				g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

GameManager	GM;

enum PLANETNUM
{
	PLANETNUM_SUN = 0,
	PLANETNUM_MERCURY,
	PLANETNUM_VENUS,
	PLANETNUM_EARTH,
	PLANETNUM_MOON,
	PLANETNUM_MARS,
	PLANETNUM_JUPITER,
	PLANETNUM_SATURN,
	PLANETNUM_URANUS,
	PLANETNUM_NEPTUNE
};

D3DXMATRIXA16		g_matTMSun;		// 태양의 변환 행렬
D3DXMATRIXA16		g_matRSun;			// 태양의 회전 행렬
DWORD					g_SunColor = D3DCOLOR_XRGB(255, 0, 0);				// 태양의 색

D3DXMATRIXA16		g_matSMercury;		// 수성의 스케일 행렬
D3DXMATRIXA16		g_matTMMercury;	// 수성의 변환 행렬
D3DXMATRIXA16		g_matRMercury;		// 수성의 회전 행렬
D3DXMATRIXA16		g_matRevMercury;	// 수성의 공전 행렬
DWORD					g_MercuryColor = D3DCOLOR_XRGB(153, 102, 255);	// 수성의 색

D3DXMATRIXA16		g_matSVenus;		// 금성의 스케일 행렬
D3DXMATRIXA16		g_matTMVenus;		// 금성의 변환 행렬
D3DXMATRIXA16		g_matRVenus;		// 금성의 회전 행렬
D3DXMATRIXA16		g_matRevVenus;		// 금성의 공전 행렬
DWORD					g_VenusColor = D3DCOLOR_XRGB(255, 204, 0);		// 금성의 색

D3DXMATRIXA16		g_matSEarth;			// 지구의 스케일 행렬
D3DXMATRIXA16		g_matTMEarth;		// 지구의 변환 행렬
D3DXMATRIXA16		g_matREarth;			// 지구의 회전 행렬
D3DXMATRIXA16		g_matRevEarth;		// 지구의 공전 행렬
DWORD					g_EarthColor = D3DCOLOR_XRGB(51, 0, 255);			// 지구의 색

D3DXMATRIXA16		g_matSMoon;		// 달의 스케일 행렬
D3DXMATRIXA16		g_matTMMoon;		// 달의 변환 행렬
D3DXMATRIXA16		g_matRMoon;		// 달의 회전 행렬
D3DXMATRIXA16		g_matRevMoon;		// 달의 공전 행렬
DWORD					g_MoonColor = D3DCOLOR_XRGB(0, 102, 102);		// 달의 색

D3DXMATRIXA16		g_matSMars;			// 화성의 스케일 행렬
D3DXMATRIXA16		g_matTMMars;		// 화성의 변환 행렬
D3DXMATRIXA16		g_matRMars;			// 화성의 회전 행렬
D3DXMATRIXA16		g_matRevMars;		// 화성의 공전 행렬
DWORD					g_MarsColor = D3DCOLOR_XRGB(204, 153, 51);		// 화성의 색

D3DXMATRIXA16		g_matSJupiter;		// 목성의 스케일 행렬
D3DXMATRIXA16		g_matTMJupiter;		// 목성의 변환 행렬
D3DXMATRIXA16		g_matRJupiter;		// 목성의 회전 행렬
D3DXMATRIXA16		g_matRevJupiter;	// 목성의 공전 행렬
DWORD					g_JupiterColor = D3DCOLOR_XRGB(51, 204, 204);		// 목성의 색

D3DXMATRIXA16		g_matSSaturn;		// 토성의 스케일 행렬
D3DXMATRIXA16		g_matTMSaturn;		// 토성의 변환 행렬
D3DXMATRIXA16		g_matRSaturn;		// 토성의 회전 행렬
D3DXMATRIXA16		g_matRevSaturn;		// 토성의 공전 행렬
DWORD					g_SaturnColor = D3DCOLOR_XRGB(255, 204, 153);	// 토성의 색

D3DXMATRIXA16		g_matSUranus;		// 천왕성의 스케일 행렬
D3DXMATRIXA16		g_matTMUranus;	// 천왕성의 변환 행렬
D3DXMATRIXA16		g_matRUranus;		// 천왕성의 회전 행렬
D3DXMATRIXA16		g_matRevUranus;	// 천왕성의 공전 행렬
DWORD					g_UranusColor = D3DCOLOR_XRGB(102, 153, 255);	// 천왕성의 색

D3DXMATRIXA16		g_matSNeptune;		// 해왕성의 스케일 행렬
D3DXMATRIXA16		g_matTMNeptune;	// 해왕성의 변환 행렬
D3DXMATRIXA16		g_matRNeptune;		// 해왕성의 회전 행렬
D3DXMATRIXA16		g_matRevNeptune;	// 해왕성의 공전 행렬
DWORD					g_NeptuneColor = D3DCOLOR_XRGB(153, 255, 0);	// 해왕성의 색

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
 * 기하 정보 초기화
 *=============================================================================*/
HRESULT InitGeometry()
{
	if (FAILED(GM.GetVertex(PLANETNUM_SUN)->InitVB(g_pd3dDevice, g_SunColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_MERCURY)->InitVB(g_pd3dDevice, g_MercuryColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_VENUS)->InitVB(g_pd3dDevice, g_VenusColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_EARTH)->InitVB(g_pd3dDevice, g_EarthColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_MOON)->InitVB(g_pd3dDevice, g_MoonColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_MARS)->InitVB(g_pd3dDevice, g_MarsColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_JUPITER)->InitVB(g_pd3dDevice, g_JupiterColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_SATURN)->InitVB(g_pd3dDevice, g_SaturnColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_URANUS)->InitVB(g_pd3dDevice, g_UranusColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetVertex(PLANETNUM_NEPTUNE)->InitVB(g_pd3dDevice, g_NeptuneColor)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetPlanet()->InitIB(g_pd3dDevice)))
	{
		return E_FAIL;
	}

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
	D3DXVECTOR3 vEyePt(80.0f, 50.0f, -25.0f);		// 눈의 위치
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// 눈이 바라보는 위치(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		// 윗 방향을 나타내는 상방 벡터(0.0f, 1.0f, 0.0f)

	// 뷰 행렬(카메라)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);		// 3가지 Point를 이용해 뷰 행렬을 생성합니다.
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);					// 생성한 뷰 행렬을 디바이스에 설정합니다.

	// 프로젝션 행렬을 정의하기 위해서는 시야각(FOV = Field Of View)과 종횡비(aspect ratio), 클리핑 평면의 값이 필요합니다.
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 500.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// 생성한 프로젝션 행렬을 디바이스에 설정합니다.
}

/*=============================================================================
 * 애니메이션 행렬 생성
 *=============================================================================*/
void Animate()
{
	// Sun의 메시는 원점에 있으므로 TMSun은 단위 행렬입니다.
	D3DXMatrixIdentity(&g_matTMSun);
	// Sun 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matTMSun, GetTickCount() / 5000.0f);

	// Mercury 메시는 Sun으로 부터 (10, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMMercury, 10, 0, 0);
	// Mercury의 스케일 조절
	D3DXMatrixScaling(&g_matSMercury, 0.4f, 0.4f, 0.4f);
	// Mercury 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matRMercury, GetTickCount() / 7000.0f);

	// Venus 메시는 Sun으로 부터 (10, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMVenus, 10, 0, 0);
	// Venus의 스케일 조절
	D3DXMatrixScaling(&g_matSVenus, 0.5f, 0.5f, 0.5f);
	// Venus 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matRVenus, GetTickCount() / 3000.0f);

	// Earth 메시는 Sun으로 부터 (12, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMEarth, 12, 0, 0);
	// Earth의 스케일 조절
	D3DXMatrixScaling(&g_matSEarth, 0.7f, 0.7f, 0.7f);
	// Earth 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matREarth, GetTickCount() / 6000.0f);

	// Moon 메시는 Earth으로 부터 (8, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMMoon, 8, 0, 0);
	// Moon의 스케일 조절
	D3DXMatrixScaling(&g_matSMoon, 0.3f, 0.3f, 0.3f);
	// Moon 메시의 Z축 회전 행렬
	D3DXMatrixRotationZ(&g_matRMoon, GetTickCount() / 2000.0f);
	// Moon 메시의 X축 회전 행렬
	//D3DXMatrixRotationX(&g_matRevMoon, GetTickCount() / 2000.0f);

	// Mars 메시는 Sun으로 부터 (12, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMMars, 12, 0, 0);
	// Mars의 스케일 조절
	D3DXMatrixScaling(&g_matSMars, 1.2f, 1.2f, 1.2f);
	// Mars 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matRMars, GetTickCount() / 2000.0f);

	// Jupiter 메시는 Sun으로 부터 (20, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMJupiter, 20, 0, 0);
	// Jupiter의 스케일 조절
	D3DXMatrixScaling(&g_matSJupiter, 0.9f, 0.9f, 0.9f);
	// Jupiter 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matRJupiter, GetTickCount() / 5000.0f);

	// Saturn 메시는 Sun으로 부터 (15, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMSaturn, 15, 0, 0);
	// Saturn의 스케일 조절
	D3DXMatrixScaling(&g_matSSaturn, 0.7f, 0.7f, 0.7f);
	// Saturn 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matRSaturn, GetTickCount() / 4000.0f);

	// Uranus 메시는 Sun으로 부터 (50, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMUranus, 50, 0, 0);
	// Uranus의 스케일 조절
	D3DXMatrixScaling(&g_matSUranus, 0.4f, 0.4f, 0.4f);
	// Uranus 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matRUranus, GetTickCount() / 3000.0f);

	// Neptune 메시는 Sun으로 부터 (12, 0, 0)의 거리에 있다.
	D3DXMatrixTranslation(&g_matTMNeptune, 55, 0, 0);
	// Neptune의 스케일 조절
	D3DXMatrixScaling(&g_matSNeptune, 0.4f, 0.4f, 0.4f);
	// Neptune 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&g_matRNeptune, GetTickCount() / 1000.0f);
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
void DrawMesh(D3DXMATRIXA16* mat, PLANETNUM planetNum)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, mat);
	g_pd3dDevice->SetStreamSource(0, GM.GetVertex(planetNum)->GetVB(), 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	g_pd3dDevice->SetIndices(GM.GetPlanet()->GetIB());
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

/*=============================================================================
 * 화면 그리기
 *=============================================================================*/
void Render()
{
	D3DXMATRIXA16 matWorld;

	// 후면 버퍼를 파란색(0, 0, 255)으로 지우고 Z버퍼를 사용하기 위해 초기화합니다.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	Animate();

	// 랜더링 시작
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		matWorld = g_matTMSun;		
		// Sun을 그립니다.
		DrawMesh(&matWorld, PLANETNUM_SUN);

		// Mercury의 변환을 만듭니다.
		matWorld = g_matTMMercury * g_matSMercury * g_matRMercury * matWorld;
		DrawMesh(&matWorld, PLANETNUM_MERCURY);

		// Venus의 변환을 만듭니다.
		matWorld = g_matTMVenus * g_matSVenus * g_matRVenus * g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_VENUS);

		// Earth의 변환을 만듭니다.
		matWorld = g_matTMEarth* g_matSEarth * g_matREarth* g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_EARTH);

		// Moon의 변환을 만듭니다.
		matWorld = g_matTMMoon * g_matSMoon * g_matRMoon * matWorld;
		DrawMesh(&matWorld, PLANETNUM_MOON);

		// Mars의 변환을 만듭니다.
		matWorld = g_matTMMars * g_matSMars * g_matRMars * g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_MARS);

		// Jupiter의 변환을 만듭니다.
		matWorld = g_matTMJupiter * g_matSJupiter * g_matRJupiter * g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_JUPITER);

		// Saturn의 변환을 만듭니다.
		matWorld = g_matTMSaturn * g_matSSaturn* g_matRSaturn* g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_SATURN);

		// Uranus의 변환을 만듭니다.
		matWorld = g_matTMUranus * g_matSUranus* g_matRUranus* g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_URANUS);

		// Neptune의 변환을 만듭니다.
		matWorld = g_matTMNeptune * g_matSNeptune* g_matRNeptune* g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_NEPTUNE);

		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*=============================================================================
 * WinProc
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
 * Window 생성
 *=============================================================================*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	// 윈도우 클래스를 등록합니다.
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D SolarSystem", NULL };

	// winclass 레지스터에 등록합니다.
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D SolarSystem", L"D3D SolarSystem", WS_OVERLAPPEDWINDOW, 100, 100, WINDOWWIDTH, WINDOWHEIGHT,
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
	UnregisterClass(L"D3D SolarSystem", wc.hInstance);
	return 0;
}