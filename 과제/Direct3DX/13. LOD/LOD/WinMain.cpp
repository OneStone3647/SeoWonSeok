/*===================================================================================*
 * HeightMap + LOD
 *===================================================================================*/

#define MAINBODY

#include "define.h"
#include "ZCamera.h"
#include "ZFrustum.h"
#include "ZTerrain.h"
#include "ZFLog.h"

#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	L"QuadTree+LOD"
#define BMP_HEIGHTMAP	"map129.bmp"

 /*===================================================================================*
  * 전역변수
  *===================================================================================*/
HWND						g_hWnd				= NULL;

LPDIRECT3D9					g_pD3D				= NULL;		// D3D 디아비스를 생성할 D3D객체변수
LPDIRECT3DDEVICE9		g_pd3dDevice		= NULL;		// 렌더링에 사용될 D3D디바이스

D3DXMATRIXA16			g_matAni;
D3DXMATRIXA16			g_matWorld;
D3DXMATRIXA16			g_matView;
D3DXMATRIXA16			g_matProj;

DWORD						g_dwMouseX		= 0;			// 마우스의 좌표
DWORD						g_dwMouseY		= 0;			// 마우스의 좌표
BOOL							g_bHideFrustum		= TRUE;		// Frustum을 안그릴 것인가?
BOOL							g_bLockFrustum		= FALSE;		// Frustum을 고정할 것인가?
BOOL							g_bWireframe		= FALSE;		// 와이어프레임으로 그릴것인가?

ZCamera*						g_pCamera			= NULL;		// Camera 클래스
ZFrustum*					g_pFrustum			= NULL;		// Frustum 클래스
ZTerrain*						g_pTerrain			= NULL;

/*===================================================================================*
 * Direct3D 초기화
 *===================================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	// 디바이스를 생성하기 위한 D3D객체 생성
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	// 디바이스를 생성할 구조체
	// 복잡한 오브젝트를 그릴것이기 때문에 Z버퍼가 필요합니다.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// 디바이스 생성
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// 기본 컬링(후면 추려내기), CCW(시계 반대 방향 두르기를 가진 삼격형을 추려내기)
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Z버퍼 기능을 켭니다.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

/*===================================================================================*
 * 행렬 설정
 *===================================================================================*/
void InitMatrix()
{
	// 월드 행렬 설정
	D3DXMatrixIdentity(&g_matWorld);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &g_matWorld);

	// 뷰 행렬을 설정
	D3DXVECTOR3		vEyePt(0.0f, 100.0f, -(float)70.0f);
	D3DXVECTOR3		vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3		vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &g_matView);

	// 프로젝션 행렬 설정
	D3DXMatrixPerspectiveFovLH(&g_matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &g_matProj);

	// Frustum 컬링용 프로젝션 행렬
	D3DXMatrixPerspectiveFovLH(&g_matProj, D3DX_PI / 4, 1.0f, 1.0f, 200.0f);

	// 카메라 초기화
	g_pCamera->SetView(&vEyePt, &vLookatPt, &vUpVec);
}


/*===================================================================================*
 * 기하 정보 초기화
 *===================================================================================*/
HRESULT InitGeometry()
{
	InitMatrix();

	// 최초의 마우스 위치 보관
	POINT pt;
	GetCursorPos(&pt);
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;

	return S_OK;
}

/*===================================================================================*
 * 오브젝트 초기화
 *===================================================================================*/
HRESULT InitObjects()
{
	LPCWSTR tex[4] = { L"tile2.tga", L"", L"",L"" };
	D3DXVECTOR3 vScale;

	vScale.x = vScale.z = 1.0f;
	vScale.y = 0.1f;
	g_pLog = new ZFLog(ZF_LOG_TARGET_WINDOW);
	g_pCamera = new ZCamera;
	g_pFrustum = new ZFrustum;
	g_pTerrain = new ZTerrain;
	g_pTerrain->Create(g_pd3dDevice, &vScale, 0.1f, BMP_HEIGHTMAP, tex);

	return S_OK;
}

/*===================================================================================*
 * 오브젝트 삭제
 *===================================================================================*/
void DeleteObjects()
{
	// 등록된 클래스 소거
	DEL(g_pTerrain);
	DEL(g_pFrustum);
	DEL(g_pLog);
	DEL(g_pCamera);
}

/*===================================================================================*
 * 초기화 객체들 소거
 *===================================================================================*/
VOID Cleanup()
{
	if (g_pd3dDevice != NULL)
	{
		g_pd3dDevice->Release();
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
	}
}

/*===================================================================================*
 * 광원 설정
 *===================================================================================*/
VOID SetupLights()
{
	// 재질(material) 설정
	// 대질은 디바이스에 단 하나만 설정될 수 있습니다.
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
	D3DXVECTOR3 vecDir;						// 방향성 광원(directional light)이 향한 빛의 방향
	D3DLIGHT9 light;						// 광원 구조체
	ZeroMemory(&light, sizeof(D3DLIGHT9));	// 구조체를 초기화합니다.
	light.Type = D3DLIGHT_DIRECTIONAL;		// 광원의 종류를 설정합니다.(포인트 라이트, 다이렉션 라이트, 스포트 라이트)
	light.Diffuse.r = 1.0f;					// 광원의 색깔의 밝기를 지정합니다.
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	// 광원의 방향 설정
	vecDir = D3DXVECTOR3(1, 1, 1);							// 광원 고정
	vecDir = D3DXVECTOR3(cosf(GetTickCount() / 350.0f),		// 광원 회전
		1.0f,
		sinf(GetTickCount() / 350.0f));

	// 광원의 방향을 단위 벡터로 만듭니다.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f;								// 광원이 다다를 수 있는 최대거리
	g_pd3dDevice->SetLight(0, &light);					// 디바이스에 광원 0번을 설치
	g_pd3dDevice->LightEnable(0, TRUE);					// 광원 0번을 활성화 합니다.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);	// 광원 설정을 활성화 합니다.

	// 환경 광원(ambient light)의 값 설정
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00909090);
}

/*===================================================================================*
 * Status정보 출력
 *===================================================================================*/
void LogStatus(void)
{
	g_pLog->Log("Wireframe: %d", g_bWireframe);
	g_pLog->Log("HideFrustum: %d", g_bHideFrustum);
	g_pLog->Log("LockFrustum: %d", g_bLockFrustum);
}

/*===================================================================================*
 * FPS(Frame Per Second) 출력
 *===================================================================================*/
void LogFPS(void)
{
	static DWORD nTick = 0;
	static DWORD nFPS = 0;

	// 1초가 지났는가?
	if (GetTickCount() - nTick > 1000)
	{
		nTick = GetTickCount();
		// FPS값 출력
		g_pLog->Log("FPS: %d", nFPS);

		// 카메라의 위치값 출력
		//D3DXVECTOR3* pv;
		//pv = g_pCamera->GetEye();
		//g_pLog->Log("Eye: [%f, %f, %f]", pv->x, pv->y, pv->z);
		nFPS = 0;
		LogStatus();		// 상태정보를 여기서 출력합니다(1초에 한번)

		return;
	}

	nFPS++;
}

/*===================================================================================*
 * 마우스 입력 처리
 *===================================================================================*/
void ProcessMouse(void)
{
	POINT pt;
	float fDelta = 0.001f;		// 마우스의 민감도, 이 값이 커질수록 많이 움직입니다.

	GetCursorPos(&pt);
	int dx = pt.x - g_dwMouseX;	// 마우스의 변화값
	int dy = pt.y - g_dwMouseY; // 마우스의 변화값

	g_pCamera->RotateLocalX(dy * fDelta);	// 마우스의 Y축 회전값은 3D World의 X축 회전값
	g_pCamera->RotateLocalY(dx * fDelta);	// 마우스의 X축 회전값은 3D World의 Y축 회전값

	D3DXMATRIXA16* pmatView = g_pCamera->GetViewMatrix();	// 카메라 행렬을 얻습니다.
	g_pd3dDevice->SetTransform(D3DTS_VIEW, pmatView);		// 카메라 행렬 셋팅

	// 마우스를 윈도우의 중앙으로 초기화
	//SetCursor(NULL);	// 마우스를 나타나지 않게 합니다.
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	pt.x = (rc.right - rc.left) / 2;
	pt.y = (rc.bottom - rc.top) / 2;
	ClientToScreen(g_hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
	g_dwMouseX = pt.x;
	g_dwMouseY = pt.y;
}

/*===================================================================================*
 * 키보드 입력 처리
 *===================================================================================*/
void ProcessKey(void)
{
	// 카메라 전진
	if (GetAsyncKeyState('W'))
	{
		g_pCamera->MoveLocalZ(0.5f);
	}
	// 카메라 후진
	if (GetAsyncKeyState('S'))
	{
		g_pCamera->MoveLocalZ(-0.5f);
	}
	// 카메라를 왼쪽과 오른족으로 이동 시키기 위해서는 카메라가 바라보는 방향의
	// 오른쪽 방향벡터를 구해야합니다.
	// 카메라 우측 이동
	if (GetAsyncKeyState('D'))
	{
		g_pCamera->MoveLocalX(0.5f);
	}
	// 카메라 좌측 이동
	if (GetAsyncKeyState('A'))
	{
		g_pCamera->MoveLocalX(-0.5f);
	}

	if (GetAsyncKeyState('Q') | GetAsyncKeyState('E'))
	{
		// 카메라 우측 회전
		if (GetAsyncKeyState('E'))
		{
			g_pCamera->SetCurrentRotate(CURRENTROTATE_RIGHT);
			if (g_pCamera->GetAngle() > -1.0f)
			{
				g_pCamera->RotateLocalZ(-0.05f);
			}
		}

		// 카메라 좌측 회전
		if (GetAsyncKeyState('Q'))
		{
			g_pCamera->SetCurrentRotate(CURRENTROTATE_LEFT);
			if (g_pCamera->GetAngle() < 1.0f)
			{
				g_pCamera->RotateLocalZ(0.05f);
			}
		}
	}
	else
	{
		if (g_pCamera->GetCurrentRotate() != CURRENTROTATE_IDLE)
		{
			if (g_pCamera->GetCurrentRotate() == CURRENTROTATE_RIGHT)
			{
				g_pCamera->RotateLocalZ(0.05f);
			}
			else if (g_pCamera->GetCurrentRotate() == CURRENTROTATE_LEFT)
			{
				g_pCamera->RotateLocalZ(-0.05f);
			}

			if (g_pCamera->GetAngle() <= 0.01f && g_pCamera->GetAngle() >= -0.01f)
			{
				g_pCamera->SetCurrentRotate(CURRENTROTATE_IDLE);
			}
		}
	}

	// 종료
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostMessage(g_hWnd, WM_DESTROY, 0, 0L);
	}
}

/*===================================================================================*
 * 입력 처리
 *===================================================================================*/
void ProcessInputs(void)
{
	ProcessMouse();
	ProcessKey();
}

/*===================================================================================*
 * 애니메이션 설정
 *===================================================================================*/
VOID Animate()
{
	D3DXMatrixIdentity(&g_matAni);

	SetupLights();
	ProcessInputs();

	D3DXMATRIXA16 m;
	D3DXMATRIXA16 *pView;
	pView = g_pCamera->GetViewMatrix();		// 카메라 클래스로부터 행렬정보를 얻습니다.
	m = *pView * g_matProj;					// World 좌표를 얻기 위해서 View * Proj 행렬을 계산합니다.
	if (!g_bLockFrustum)
	{
		// View * Proj 행렬로 Frustum을 만듭니다.
		g_pFrustum->Make(&m);
	}

	LogFPS();
}

/*===================================================================================*
 * 화면 그리기
 *===================================================================================*/
VOID Render()
{
	// 후면버퍼와 Z버퍼를 포기화합니다.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(200, 200, 200), 1.0f, 0);
	g_pd3dDevice->SetRenderState(D3DRS_FILLMODE, g_bWireframe ? D3DFILL_WIREFRAME : D3DFILL_SOLID);

	// 애니메이션 행렬설정
	Animate();

	// 랜더링 시작
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		g_pTerrain->Draw(g_pFrustum);
		if (!g_bHideFrustum)
		{
			g_pFrustum->Draw(g_pd3dDevice);
		}

		// 랜더링 종료
		g_pd3dDevice->EndScene();
	}

	// 후면 버퍼를 보이는 화면으로
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*===================================================================================*
 * 윈도우 프로시져
 *===================================================================================*/
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
		case '1':
			g_bWireframe = !g_bWireframe;
			break;
		case '2':
			g_bLockFrustum = !g_bLockFrustum;
			g_bHideFrustum = !g_bLockFrustum;
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/*===================================================================================*
 * 프로그램 시작점
 *===================================================================================*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	//윈도우 클래스 등록
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
								GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
								L"BasicFrame", NULL };

	//winclass 레지스터에 등록
	RegisterClassEx(&wc);

	// 윈도우 생성
	HWND hWnd = CreateWindow(L"BasicFrame", WINDOW_TITLE,
											WS_OVERLAPPEDWINDOW, 100, 100, WINDOW_W, WINDOW_H,
											GetDesktopWindow(), NULL, wc.hInstance, NULL);

	g_hWnd = hWnd;

	// Direct3D 초기화
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		InitObjects();
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
				// 메시지큐에 메시지가 있으면 메시지 처리
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

	// 등록된 클래스 소거
	DeleteObjects();

	//등록된 레지스트 winclass 릴리즈.
	UnregisterClass(L"BasicFrame", wc.hInstance);
	return 0;
}