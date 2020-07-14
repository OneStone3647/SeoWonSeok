/*=============================================================================
 * 2개 이상의 육면체를 인덱스로 생성해서 행렬을 적용
 * 뷰 행렬의 값을 조정
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

float	g_X = 0.0f;
float	g_Y = 20.0f;
float	g_Z = -20.0f;

float	g_Speed = 0.5f;

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
 * 행렬 설정
 * 행렬에는 3가지가 있으며, 각각 월, 뷰, 프로젝션, 행렬입니다.
 *=============================================================================*/
void SetupMatrices()
{
	D3DXMatrixIdentity(GM.GetmatWorld());	// 월드 행렬을 단위 행렬로 생성합니다.

	//D3DXMatrixRotationY(&matWorld, GetTickCount() / 500.0f); // Y축을 회전축으로 회전 행렬을 생성한다.
	//D3DXMatrixTranslation(GM.GetmatWorld(), GM.GetSpeed(), 0.0f, 0.0f);

	g_pd3dDevice->SetTransform(D3DTS_WORLD, GM.GetmatWorld());	// 생성한 회전 행렬을 월드 행렬로 디바이스에 설정합니다.

	// 뷰 행렬(카메라)을 정의하기 위해서는 3가지 값이 필요합니다.
	D3DXVECTOR3 vEyePt(g_X, g_Y, g_Z);			// 눈의 위치
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// 눈이 바라보는 위치(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);				// 윗 방향을 나타내는 상방 벡터(0.0f, 1.0f, 0.0f)

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
 * 입력
 *=============================================================================*/
void Input()
{
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		g_X += g_Speed;
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		g_X -= g_Speed;
	}

	if (GetKeyState(VK_UP) & 0x8000)
	{
		g_Z += g_Speed;
	}

	if (GetKeyState(VK_DOWN) & 0x8000)
	{
		g_Z -= g_Speed;
	}

	if (GetKeyState(VK_RBUTTON) & 0x8000)
	{
		g_Y += g_Speed;
	}

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		g_Y -= g_Speed;
	}
}

/*=============================================================================
 * 화면 그리기
 *=============================================================================*/
void Render()
{
	if (NULL == g_pd3dDevice)
	{
		return;
	}

	// 후면 버퍼를 파란색(0, 0, 255)으로 지우고 Z버퍼를 사용하기 위해 초기화합니다.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//월드, 뷰, 프로젝션 행렬을 설정한다.
	SetupMatrices();

	// 랜더링 시작
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// 정점 정보가 담겨 있는 정점 버퍼를 출력 스트림으로 할당합니다.
		g_pd3dDevice->SetStreamSource(0, GM.GetVertex(0)->GetVB(), 0, sizeof(CUSTOMVERTEX));

		// D3D에게 정점 셰이더 정보를 지정합니다. 대부분의 경우에는 FVF만 지정합니다.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// 인덱스 버퍼를 지정합니다.
		g_pd3dDevice->SetIndices(GM.GetCube()->GetIB());

		// 기하 정보를 출력하기 위한 DrawIndexPrimitive() 함수를 호출합니다.
		/*=============================================================================
		 * HRESULT DrawIndexPrimitive
		 * (
		 *   D3DPRIMITIVETYPE Type,
		 *   INT BaseVertexIndex,
		 *	 UINT MinIndex,
		 *	 UINT NumVertices,
		 *	 UINT StartIndex,
		 *	 UINT PrimitiveCount
		 * );
		 * Type: 그리고자 하는 기본 타입
		 * BaseVertexIndex: 여러 오브젝트를 하나로 묶을 때 더해질 넘버
		 * MinIndex: 참조할 최소 인덱스 값
		 * NumVertices: 이번 호출에 참조될 버텍스의 수
		 * StartIndex: 인덱스 버퍼 내에서 읽기를 시작할 인덱스 번호
		 * PrimitiveCount: 랜더링 하는 기본 도형의 수
		 *=============================================================================*/
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

		g_pd3dDevice->SetStreamSource(0, GM.GetVertex(1)->GetVB(), 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

		// 렌더링 종료
		g_pd3dDevice->EndScene();
	}

	// 후면 버퍼를 보이는 화면으로 전환합니다.
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
		L"D3D IndexBuffer", NULL };

	// winclass 레지스터에 등록합니다.
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D IndexBuffer", L"D3D IndexBuffer", WS_OVERLAPPEDWINDOW, 100, 100, WINDOWWIDTH, WINDOWHEIGHT,
		GetDesktopWindow(), NULL, NULL, wc.hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(GM.GetVertex(0)->InitVB(g_pd3dDevice, 0, 0, 0, 1)) && SUCCEEDED(GM.GetVertex(1)->InitVB(g_pd3dDevice, 4, -2, 3, 1)))
		{
			if (SUCCEEDED(GM.GetCube()->InitIB(g_pd3dDevice)))
			{
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
						GM.Update();
						Input();
						Render();
					}
				}
			}
		}
	}

	// 등록된 레지시트 winclass를 릴리즈 합니다.
	UnregisterClass(L"D3D IndexBuffer", wc.hInstance);
	return 0;
}