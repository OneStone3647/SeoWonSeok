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

D3DXMATRIXA16		g_matTMSun;			// 태양의 변환 행렬
D3DXMATRIXA16		g_matRSun;			// 태양의 회전 행렬
DWORD				g_SunColor = D3DCOLOR_XRGB(255, 0, 0);		// 태양의 색

D3DXMATRIXA16		g_matSMercury;		// 수성의 스케일 행렬
D3DXMATRIXA16		g_matTMMercury;		// 수성의 변환 행렬
D3DXMATRIXA16		g_matRMercury;		// 수성의 회전 행렬
DWORD				g_MercuryColor = D3DCOLOR_XRGB(153, 102, 255);	// 수성의 색

D3DXMATRIXA16		g_matSVenus;		// 금성의 스케일 행렬
D3DXMATRIXA16		g_matTMVenus;		// 금성의 변환 행렬
D3DXMATRIXA16		g_matRVenus;		// 금성의 회전 행렬
DWORD				g_VenusColor = D3DCOLOR_XRGB(255, 204, 0);	// 금성의 색

D3DXMATRIXA16		g_matSEarth;		// 지구의 스케일 행렬
D3DXMATRIXA16		g_matTMEarth;		// 지구의 변환 행렬
D3DXMATRIXA16		g_matREarth;		// 지구의 회전 행렬
DWORD				g_EarthColor = D3DCOLOR_XRGB(51, 0, 255);	// 지구의 색

D3DXMATRIXA16		g_matSMoon;			// 달의 스케일 행렬
D3DXMATRIXA16		g_matTMMoon;		// 달의 변환 행렬
D3DXMATRIXA16		g_matRMoon;			// 달의 회전 행렬
DWORD				g_MoonColor = D3DCOLOR_XRGB(0, 102, 102);		// 달의 색

D3DXMATRIXA16		g_matSMars;			// 화성의 스케일 행렬
D3DXMATRIXA16		g_matTMMars;		// 화성의 변환 행렬
D3DXMATRIXA16		g_matRMars;			// 화성의 회전 행렬
DWORD				g_MarsColor = D3DCOLOR_XRGB(204, 153, 51);		// 화성의 색

D3DXMATRIXA16		g_matSJupiter;		// 목성의 스케일 행렬
D3DXMATRIXA16		g_matTMJupiter;		// 목성의 변환 행렬
D3DXMATRIXA16		g_matRJupiter;		// 목성의 회전 행렬
DWORD				g_JupiterColor = D3DCOLOR_XRGB(51, 204, 204);	// 목성의 색

D3DXMATRIXA16		g_matSSaturn;		// 토성의 스케일 행렬
D3DXMATRIXA16		g_matTMSaturn;		// 토성의 변환 행렬
D3DXMATRIXA16		g_matRSaturn;		// 토성의 회전 행렬
DWORD				g_SaturnColor = D3DCOLOR_XRGB(255, 204, 153);	// 토성의 색

D3DXMATRIXA16		g_matSUranus;		// 천왕성의 스케일 행렬
D3DXMATRIXA16		g_matTMUranus;		// 천왕성의 변환 행렬
D3DXMATRIXA16		g_matRUranus;		// 천왕성의 회전 행렬
DWORD				g_UranusColor = D3DCOLOR_XRGB(153, 255, 255);	// 천왕성의 색

D3DXMATRIXA16		g_matSNeptune;		// 해왕성의 스케일 행렬
D3DXMATRIXA16		g_matTMNeptune;		// 해왕성의 변환 행렬
D3DXMATRIXA16		g_matRNeptune;		// 해왕성의 회전 행렬
DWORD				g_NeptuneColor = D3DCOLOR_XRGB(102, 51, 255);	// 해왕성의 색

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

	d3dpp.Windowed = TRUE;						// 창 모드로 생성합니다.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 가장 효율적인 SWAP 효과입니다.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	// 현재 바탕화면 모드에 맞춰서 후면 버퍼를 생성합니다.
	d3dpp.EnableAutoDepthStencil = TRUE;		// 길이가 있는 Z버퍼가 필요하므로 설정합니다.
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
 * 카메라 행렬 설정
 *=============================================================================*/
void SetupMatrices()
{
	D3DXMatrixIdentity(GM.GetmatWorld());	// 월드 행렬을 단위 행렬로 생성합니다.
	//D3DXMatrixRotationY(&matWorld, GetTickCount() / 500.0f); // Y축을 회전축으로 회전 행렬을 생성한다.
	//D3DXMatrixTranslation(GM.GetmatWorld(), GM.GetSpeed(), 0.0f, 0.0f);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, GM.GetmatWorld());	// 생성한 회전 행렬을 월드 행렬로 디바이스에 설정합니다.

	// 뷰 행렬(카메라)을 정의하기 위해서는 3가지 값이 필요합니다.
	D3DXVECTOR3 vEyePt(0.0f, 10.0f, -25.0f);	// 눈의 위치
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// 눈이 바라보는 위치(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		// 윗 방향을 나타내는 상방 벡터(0.0f, 1.0f, 0.0f)

	// 뷰 행렬(카메라)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);		// 3가지 Point를 이용해 뷰 행렬을 생성합니다.
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);	// 생성한 뷰 행렬을 디바이스에 설정합니다.

	// 프로젝션 행렬을 정의하기 위해서는 시야각(FOV = Field Of View)과 종횡비(aspect ratio), 클리핑 평면의 값이 필요합니다.
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// 생성한 프로젝션 행렬을 디바이스에 설정합니다.
}

/*=============================================================================
 * 애니메이션 행렬 생성
 *=============================================================================*/

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