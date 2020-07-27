/*=============================================================================*
 * HeightMap(높이맵)
 * HeightMAp구현 - Triangle List
 *=============================================================================*/
#define MAINBODY

#include <d3d9.h>
#include <d3dx9.h>
#include "ZFLog.h"

#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	L"HeightMap_TList"
#define BMP_HEIGHTMAP	L"map128.bmp"

/*=============================================================================*
 * 전역 변수
 *=============================================================================*/
HWND					g_hWnd;

LPDIRECT3D9				g_pD3D			= NULL;
LPDIRECT3DDEVICE9		g_pd3dDevice	= NULL;
LPDIRECT3DVERTEXBUFFER9	g_pVB			= NULL;
LPDIRECT3DINDEXBUFFER9	g_pIB			= NULL;

LPDIRECT3DTEXTURE9		g_pTexHeight	= NULL;	// Texture 높이맵
LPDIRECT3DTEXTURE9		g_pTexDiffuse	= NULL;	// Texture 색깔맵
D3DXMATRIXA16			g_matAni;

DWORD					g_cxHeight = 0;
DWORD					g_czHeight = 0;

struct CUSTOMVERTEX
{
	D3DXVECTOR3		p;
	D3DXVECTOR3		n;
	D3DXVECTOR3		t;
};

// 사용자 정점 구조체에 관한 정보를 나타내는 FVF값
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct MYINDEX
{
	WORD	_0, _1, _2;
};

/*=============================================================================*
 * Direct3D 초기화
 *=============================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

/*=============================================================================*
 * 텍스처 초기화
 *=============================================================================*/
HRESULT InitTexture()
{
	// 높이맵 텍스처
	// D3DFMT_X8R8G8B8와  D3DPOOL_MANAGED를 주기 위해서 이 함수를 사용하였습니다.
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, BMP_HEIGHTMAP,
		D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, 0,
		D3DFMT_X8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0,
		NULL, NULL, &g_pTexHeight)))
	{
		return E_FAIL;
	}

	// 색깔맵
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"tile2.tga", &g_pTexDiffuse)))
	{
		return E_FAIL;
	}

	return S_OK;
}

/*=============================================================================*
 * 정점버퍼를 생성하고 정점값을 채워 넣습니다.
 *=============================================================================*/
HRESULT InitVB()
{
	D3DSURFACE_DESC		ddsd;
	D3DLOCKED_RECT		d3drc;

	g_pTexHeight->GetLevelDesc(0, &ddsd);	// 텍스처의 정보
	g_cxHeight = ddsd.Width;				// 텍스처의 가로 크기
	g_czHeight = ddsd.Height;				// 텍스처의 세로 크기

	g_pLog->Log("Texture Size: [%d, %d]", g_cxHeight, g_czHeight);
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(ddsd.Width * ddsd.Height * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	// 텍스처 메모리 락
	g_pTexHeight->LockRect(0, &d3drc, NULL, D3DLOCK_READONLY);
	VOID* pVertices;
	// 정점버퍼 락
	if (FAILED(g_pVB->Lock(0, g_cxHeight*g_czHeight * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	CUSTOMVERTEX v;
	CUSTOMVERTEX* pV = (CUSTOMVERTEX*)pVertices;

	for (DWORD z = 0; z < g_czHeight; z++)
	{
		for (DWORD x = 0; x < g_czHeight; x++)
		{
			v.p.x = (float)x - g_czHeight / 2.0f;		// 정점의 x좌표(메시를 원점에 정렬)
			v.p.z = -((float)z - g_czHeight / 2.0f);	// 정점의 z좌표(메시를 원점에 정렬), z축이 모니터 안쪽이므로 -를 곱한다.
			v.p.y = ((float)(*((LPDWORD)d3drc.pBits + x + z * (d3drc.Pitch / 4)) & 0x000000ff)) / 10.0f;	// DWORD이므로 pitch/4
			v.n.x = v.p.x;
			v.n.y = v.p.y;
			v.n.z = v.p.z;
			/*-----------------------------------------------------------------------------*
			 * D3DXVECTOR3 *WINAPI D3DXVec3Normalize(
			 * D3DXVECTOR3 *pOut,
			 * CONST D3DXVECTOR3 *pV
			 * );
			 * 3D 벡터의 정규화한 벡터를 돌려준다.
			 * pOut: 연산 결과인 D3DXVECTOR3 구조체의 포인터
			 * pV: 정규화할 D3DVECTOR3 구조체의 포인터
			 *-----------------------------------------------------------------------------*/
			D3DXVec3Normalize(&v.n, &v.n);
			v.t.x = (float)x / (g_cxHeight - 1);
			v.t.y = (float)z / (g_czHeight - 1);
			*pV++ = v;
			//g_pLog->Log( "[%f, %f, %f]", v.x, v.y, v.z);
		}
	}

	g_pVB->Unlock();
	g_pTexHeight->UnlockRect(0);

	return S_OK;
}

/*=============================================================================*
 * 인덱스 버퍼 초기화
 *=============================================================================*/
HRESULT InitIB()
{
	if (FAILED(g_pd3dDevice->CreateIndexBuffer((g_czHeight - 1)*(g_czHeight - 1) * 2 * sizeof(MYINDEX),
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}

	MYINDEX		i;
	MYINDEX*	pI;
	if (FAILED(g_pIB->Lock(0, (g_cxHeight - 1) * (g_czHeight - 1) * 2 * sizeof(MYINDEX), (void**)&pI, 0)))
	{
		return E_FAIL;
	}

	for (DWORD z = 0; z < g_czHeight - 1; z++)
	{
		for (DWORD x = 0; x < g_cxHeight - 1; x++)
		{
			i._0 = (z*g_cxHeight + x);
			i._1 = (z + g_cxHeight + x + 1);
			i._2 = ((z + 1)*g_cxHeight + x);

			*pI++ = i;

			i._0 = ((z + 1)*g_cxHeight + x);
			i._1 = (z*g_cxHeight + x + 1);
			i._2 = ((z + 1)*g_cxHeight + x + 1);

			*pI++ = i;
		}
	}

	g_pIB->Unlock();

	return S_OK;
}

/*=============================================================================*
 * 기하 정보 초기화
 *=============================================================================*/
HRESULT InitGeometry()
{
	if (FAILED(InitTexture()))
	{
		return E_FAIL;
	}

	if (FAILED(InitVB()))
	{
		return E_FAIL;
	}

	if (FAILED(InitIB()))
	{
		return E_FAIL;
	}

	return S_OK;
}

/*=============================================================================*
 * 카메라 행렬 설정
 *=============================================================================*/
void SetupCamera()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3		vEyePt(0.0f, 100.0f, -(float)g_czHeight);
	D3DXVECTOR3		vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3		vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

/*=============================================================================*
 * 광원 설정
 *=============================================================================*/
VOID SetupLights()
{
	// 재질 설정
	// 대질은 디바이스에 단 하남나 설정될 수 있습니다.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(_D3DMATERIAL9));
	// Diffuse(확산광): 표면의 모든 점에 균일하게 비춰지는 빛
	// Ambient(주변광): 최저 평균 밝기를 말한다. 똑같은 양으로 모든 면에서 나오는 빛
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
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	// 광원의 확산광 색깔의 밝기를 지정합니다.
	// 광원의 종류를 설정합니다.(포인트 라이트, 다이렉션 라이트, 스포트 라이트)
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	// 광원의 방향 설정
	vecDir = D3DXVECTOR3(1, 1, 1);
	vecDir = D3DXVECTOR3(cosf(GetTickCount() / 350.0f),
		1.0f,
		sinf(GetTickCount() / 350.0f));

	// 광원의 방향을 단위 벡터로 만듭니다.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f;								// 광원이 다다를 수 있는 최대거리
	g_pd3dDevice->SetLight(0, &light);					// 디바이스에 광원 0번을 설치
	g_pd3dDevice->LightEnable(0, TRUE);					// 광원 0번을 활성화 합니다.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	// 광원 설정을 활성화 합니다.

	// 환경 광원의 값 설정
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00909090);
}

/*=============================================================================*
 * FPS(Frame Per Second) 출력
 *=============================================================================*/
void LogFPS(void)
{
	static DWORD nTick = 0;
	static DWORD nFPS = 0;

	if (GetTickCount() - nTick > 1000)
	{
		nTick = GetTickCount();
		g_pLog->Log("FPS: %d", nFPS);
		nFPS = 0;
		return;
	}
	nFPS++;
}

/*=============================================================================*
 * 애니메이션 설정
 *=============================================================================*/
VOID Animate()
{
	static DWORD t = 0;
	static bool flag = false;
	// 0 ~ 2PI까지 (0 ~ 360도) 값을 변화시킵니다. Fixed Point기법을 사용
	DWORD d = GetTickCount() % ((int)((D3DX_PI * 2) * 1000));
	// Y축 회전행렬
	D3DXMatrixRotationY(&g_matAni, d / 1000.0f);
	// D3DXMatrixIdentity(&g_matAni);

	// 카메라 행렬설정
	SetupCamera();
	SetupLights();

	if (d < t)
	{
		flag = !flag;
	}
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, flag ? D3DFILL_WIREFRAME : D3DFILL_SOLID);
	t = d;

	LogFPS();
}

/*=============================================================================*
 * 초기화 객체를 소거
 *=============================================================================*/
VOID Cleanup()
{
	if (g_pTexHeight != NULL)
	{
		g_pTexHeight->Release();
	}

	if (g_pTexDiffuse != NULL)
	{
		g_pTexDiffuse->Release();
	}

	if (g_pIB != NULL)
	{
		g_pIB->Release();
	}

	if (g_pVB != NULL)
	{
		g_pVB->Release();
	}

	if (g_pd3dDevice != NULL)
	{
		g_pd3dDevice->Release();
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
	}
}

/*=============================================================================*
 * 메시 그리기
 *=============================================================================*/
void DrawMesh(D3DXMATRIXA16* pMat)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, pMat);
	g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	g_pd3dDevice->SetIndices(g_pIB);
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, g_cxHeight*g_czHeight, 0, (g_cxHeight - 1)*(g_czHeight - 1) * 2);
}

/*=============================================================================*
 * 화면 그리기
 *=============================================================================*/
VOID Render()
{
	// 후면버퍼와 Z버퍼를 포기화합니다.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);

	// 애니메이션 행렬설정
	Animate();

	// 랜더링 시작
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pd3dDevice->SetTexture(0, g_pTexDiffuse);								// 0번 텍스처 스테이지에 텍스처 고정(색깔맵)
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 0번 텍스처 스테이지의 확대 필터
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);			// 0번 텍스처: 0번 텍스처 인덱스 사용

		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

		DrawMesh(&g_matAni);
		// 랜더링 종료
		g_pd3dDevice->EndScene();
	}

	// 후면 버퍼를 보이는 화면으로
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*=============================================================================*
 * 윈도우 프로시져
 *=============================================================================*/
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0L);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*=============================================================================*
 * 프로그램 시작점
 *=============================================================================*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	//윈도우 클래스 등록
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"HeightMap_TList", NULL };

	//winclass 레지스터에 등록
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"HeightMap_TList", WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_W, WINDOW_H,
		GetDesktopWindow(), NULL, wc.hInstance, NULL);

	g_hWnd = hWnd;
	g_pLog = new ZFLog(ZF_LOG_TARGET_WINDOW);
	// Direct3D 초기화
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitGeometry()))
		{
			// 윈도우 출력
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// 메시지 루프
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
					// 처리할 메시지가 없으면 Render()함수 호출
					Render();
				}					
			}
		}
	}

	delete g_pLog;

	//등록된 레지스트 winclass 릴리즈.
	UnregisterClass(L"HeightMap_TList", wc.hInstance);
	return 0;
}