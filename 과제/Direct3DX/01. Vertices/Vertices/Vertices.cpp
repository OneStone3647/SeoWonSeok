/*=============================================================================
 * 정점들의 정보를 변경
 * 삼각형 그리기를 이용해서 사각형 그리기
 *=============================================================================*/

 // Direct3D9을 사용하기 위한 헤더입니다.
#include <d3d9.h>
#include <d3dx9.h>

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768

/*=============================================================================
 * 전역 변수
 *=============================================================================*/
LPDIRECT3D9				g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;	// 정점을 보관할 버퍼입니다.
LPDIRECT3DVERTEXBUFFER9 g_pCustomVB = NULL;

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;		// 정점의 변환된 좌표입니다.(rhw 값이 있으면 변환이 완료된 정점입니다.)
	DWORD color;			// 정점의 색입니다.
};

CUSTOMVERTEX Vertices[] =
{
	// 시계 방향으로 그립니다.
	// x, y, z, rhw, color
	{ 150.0f, 50.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },
	{ 250.0f, 50.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },
	{ 150.0f, 150.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },
	{ 250.0f, 150.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },

	//{ 50.0f,  50.0f, 0.5f, 1.0f, 0xffff0000, }, // x, y, z, rhw, color
	//{ 250.0f, 50.0f, 0.5f, 1.0f, 0xff00ff00, },
	//{ 50.0f, 250.0f, 0.5f, 1.0f, 0xff00ffff, },
	//{ 250.0f, 450.0f, 0.5f, 1.0f, 0x40531041, },
};

float Speed_X = 2.0f;		// 이동 속도입니다.

/*=============================================================================
 * 사용자 정점 구조체에 관한 정보를 나타내는 FVF값입니다.
 * 구조체는 x, y, z, RHW 값과 Diffuse 색 값으로 이루어져 있습니다.
 * D3DFVF_DIFFUSE 옵션으로 꼭지점이 정해져 있다는걸 알려줍니다.
 *=============================================================================*/
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

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

	// 디바이스를 설정해서 생성합니다.
	// 디폴트 비디오카드를 사용하고, HAL 디바이스를 생성합니다.
	// 정점 처리는 모든 카드에서 지원하는 SW처리로 생성합니다.
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// 디바이스 상태 정보를 처리할 경우 여기에서 합니다.

	return S_OK;
}

/*=============================================================================
 * 정점 버퍼 초기화
 * 정점 버퍼: 기본적으로 정점 정보를 갖고 있는 메모리 블록
 *
 * 정점 버퍼를 생성하고 정점값을 채워 넣습니다.
 * 정점 버퍼를생성한 다음에는 반드시 Lock()과 Unlock()으로 포인터를 얻어내서
 * 정점 정보를 정점 버퍼에 써넣어야 합니다.
 * 또한 D3D는 인덱스버퍼도 사용 가능하다는 것을 명심합니다.
 * 정점 버퍼나 인덱스 버퍼는 기본 시스템 메모리 외에 디바이스 메모리(비디오카드 메모리)에
 * 생성될수 있는데, 대부분의 비디오카드에서는 이렇게 할 경우 엄청난 속도 향상을 얻을 수 있습니다.
 *=============================================================================*/
HRESULT InitVB()
{
	// 정점 버퍼를 생성합니다.
	// 정점 구조체4개를 저장할 메모리를 할당합니다.
	// FVF를 지정하여 보관할 데이터의 형식을 지정합니다.
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pCustomVB, NULL)))
	{
		return E_FAIL;
	}

	// 정점의 버퍼를 값으로 채웁니다.
	// 정점 버퍼의 Lock() 함수를 호출하여 포인터를 얻어옵니다.
	void* pVertices;

	if (FAILED(g_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	// Vertices를 pVertices로 복사합니다.
	memcpy(pVertices, Vertices, sizeof(Vertices));

	g_pVB->Unlock();

	return S_OK;
}

/*=============================================================================
 * 초기화 객체를 Release
 *=============================================================================*/
void Release()
{
	// 해제 순서가 중요합니다.
	// 인터페이스 생성의 역순으로 해제합니다.
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

/*=============================================================================
 * 입력
 *=============================================================================*/
void Input()
{
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		for (int i = 0; i < 4; i++)
		{
			Vertices[i].x += Speed_X;

			// 도형이 오른쪽에 위치할 경우
			if (Vertices[i].x >= WINDOWWIDTH / 2)
			{
				for (int i = 0; i < 4; i++)
				{
					Vertices[i].color = D3DCOLOR_XRGB(255, 0, 0);
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					Vertices[i].color = D3DCOLOR_XRGB(255, 255, 0);
				}
			}
		}
		// 정점의 버퍼를 값으로 채웁니다.
		// 정점 버퍼의 Lock() 함수를 호출하여 포인터를 얻어옵니다.
		void* pVertices;

		g_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0);

		// Vertices를 pVertices로 복사합니다.
		memcpy(pVertices, Vertices, sizeof(Vertices));

		g_pVB->Unlock();
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		for (int i = 0; i < 4; i++)
		{
			Vertices[i].x -= Speed_X;

			// 도형이 왼쪽에 위치할 경우
			if (Vertices[i].x <= WINDOWWIDTH / 2)
			{
				for (int i = 0; i < 4; i++)
				{
					Vertices[i].color = D3DCOLOR_XRGB(255, 255, 0);
				}
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					Vertices[i].color = D3DCOLOR_XRGB(255, 0, 0);
				}
			}
		}
		// 정점의 버퍼를 값으로 채웁니다.
		// 정점 버퍼의 Lock() 함수를 호출하여 포인터를 얻어옵니다.
		void* pVertices;

		g_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0);

		// Vertices를 pVertices로 복사합니다.
		memcpy(pVertices, Vertices, sizeof(Vertices));

		g_pVB->Unlock();
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

	// 후면 버퍼를 파란색(0, 0, 255)으로 지웁니다.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// 랜더링 시작
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// 정점 버퍼의 삼각형을 그립니다.
		g_pd3dDevice->SetStreamSource(0, g_pCustomVB, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		/*=============================================================================
		 * HRESULT DrawPrimitive
		 * (
		 *   D3DPRIMITIVETYPE PrimitiveType,
		 *   UINT StartVertex,
		 *	 UINT PrimitiveCount
		 * );
		 * PrimitiveType: 랜더링하는 기본 도형의 종류를 기술합니다.
		 * StartVertex: 로드하는 최초의 정점의 인덱스입니다.
		 * PrimitiveCount: 랜더링 하는 기본 도형의 수입니다.
		 *=============================================================================*/
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// 정점 정보가 담겨 있는 정점 버퍼를 출력 스트림으로 할당합니다.
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));

		// D3D에게 정점 셰이더 정보를 지정합니다. 대부분의 경우에는 FVF만 지정합니다.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// 기하 정보를 출력하기 위한 DrawPrimitive() 함수를 호출합니다.
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

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
		L"D3D Vertices", NULL };

	// winclass 레지스터에 등록합니다.
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D Vertices", L"D3D Vertices", WS_OVERLAPPEDWINDOW, 100, 100, WINDOWWIDTH, WINDOWHEIGHT,
		GetDesktopWindow(), NULL, NULL, wc.hInstance, NULL);

	if (SUCCEEDED(InitD3D(hWnd)))
	{
		if (SUCCEEDED(InitVB()))
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
					Input();
					Render();
				}
			}
		}
	}

	// 등록된 레지시트 winclass를 릴리즈 합니다.
	UnregisterClass(L"D3D Vertices", wc.hInstance);
	return 0;
}