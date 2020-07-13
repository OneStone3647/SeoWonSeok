/*=============================================================================
 * �������� ������ ����
 * �ﰢ�� �׸��⸦ �̿��ؼ� �簢�� �׸���
 *=============================================================================*/

 // Direct3D9�� ����ϱ� ���� ����Դϴ�.
#include <d3d9.h>
#include <d3dx9.h>

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768

/*=============================================================================
 * ���� ����
 *=============================================================================*/
LPDIRECT3D9				g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;	// ������ ������ �����Դϴ�.

LPDIRECT3DINDEXBUFFER9	g_pIB = NULL;	// �ε����� ������ �ε��� �����Դϴ�.

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;		// ������ ��ȯ�� ��ǥ�Դϴ�.(rhw ���� ������ ��ȯ�� �Ϸ�� �����Դϴ�.)
	DWORD color;			// ������ ���Դϴ�.
};

CUSTOMVERTEX Vertices[] =
{
	// �ð� �������� �׸��ϴ�.
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

float Speed_X = 2.0f;		// �̵� �ӵ��Դϴ�.

/*=============================================================================
 * ����� ���� ����ü�� ���� ������ ��Ÿ���� FVF���Դϴ�.
 * ����ü�� x, y, z, RHW ���� Diffuse �� ������ �̷���� �ֽ��ϴ�.
 * D3DFVF_DIFFUSE �ɼ����� �������� ������ �ִٴ°� �˷��ݴϴ�.
 *=============================================================================*/
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

struct MYINDEX
{
	WORD _0, _1, _2;		// �Ϲ������� �ε����� 16��Ʈ�� ũ�⸦ �����ϴ�.
};

 /*=============================================================================
  * Direct3D �ʱ�ȭ
  *=============================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	// ����̽��� �����ϱ� ���� D3D ��ü�� �����մϴ�.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;				// ����̽� ������ ���� ����ü�Դϴ�.
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// �ݵ�� ZeroMemory() �Լ��� �̸� ����ü�� ������ ������ �մϴ�.

	d3dpp.Windowed = TRUE;						// â ���� �����մϴ�.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// ���� ȿ������ SWAP ȿ���Դϴ�.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	// ���� ����ȭ�� ��忡 ���缭 �ĸ� ���۸� �����մϴ�.

	d3dpp.EnableAutoDepthStencil = TRUE;		// ���̰� �ִ� z���۰� �ʿ��ϹǷ� �����մϴ�.
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// ����̽��� �����ؼ� �����մϴ�.
	// ����Ʈ ����ī�带 ����ϰ�, HAL ����̽��� �����մϴ�.
	// ���� ó���� ��� ī�忡�� �����ϴ� SWó���� �����մϴ�.
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// �ø��� �����մϴ�.
	/*==================================================================================
	* �ɼ� �÷���
	* D3DCULL_NONE: �ĸ� �߷����⸦ ������ ���ϴ�.
	* D3DCULL_CW: �ð� ���� �θ��⸦ ���� �ﰢ���� �߷����ϴ�.
	* D3DCULL_CCW: �ð� �ݴ� ���� �θ��⸦ ���� �ﰢ���� �߷����ϴ�. ����Ʈ �����Դϴ�.
	*===================================================================================*/
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// ���� ����� �մϴ�.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// ���� ����� ���ϴ�.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

/*=============================================================================
 * ���� ���� �ʱ�ȭ
 * ���� ����: �⺻������ ���� ������ ���� �ִ� �޸� ���
 *
 * ���� ���۸� �����ϰ� �������� ä�� �ֽ��ϴ�.
 * ���� ���۸������� �������� �ݵ�� Lock()�� Unlock()���� �����͸� ����
 * ���� ������ ���� ���ۿ� ��־�� �մϴ�.
 * ���� D3D�� �ε������۵� ��� �����ϴٴ� ���� ����մϴ�.
 * ���� ���۳� �ε��� ���۴� �⺻ �ý��� �޸� �ܿ� ����̽� �޸�(����ī�� �޸�)��
 * �����ɼ� �ִµ�, ��κ��� ����ī�忡���� �̷��� �� ��� ��û�� �ӵ� ����� ���� �� �ֽ��ϴ�.
 *=============================================================================*/
HRESULT InitVB()
{
	MYINDEX indices[] = 
	{
		{0, 1, 2},
		{0, 2, 3},
		{0, 3, 5},
	};

	// �ε��� ���� ����
	// D3DFMT_INDEX16�� �ε����� ������ 16��Ʈ��� ���� ��Ÿ���ϴ�.
	// MYINDEX ����ü���� WORD������ ���������Ƿ� D3DFMT_INDEX16�� ����մϴ�.
	// DWORD���� ��� D3DFMT_INDEX32�� ����մϴ�.
	if (FAILED(g_pd3dDevice->CreateIndexBuffer(3 * sizeof(MYINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}

	// ������ ���۸� ������ ä��ϴ�.
	// ���� ������ Lock() �Լ��� ȣ���Ͽ� �����͸� ���ɴϴ�.
	void* pVertices;

	if (FAILED(g_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	// Vertices�� pVertices�� �����մϴ�.
	memcpy(pVertices, Vertices, sizeof(Vertices));

	g_pVB->Unlock();

	return S_OK;
}

/*=============================================================================
 * �ʱ�ȭ ��ü�� Release
 *=============================================================================*/
void Release()
{
	// ���� ������ �߿��մϴ�.
	// �������̽� ������ �������� �����մϴ�.
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
 * �Է�
 *=============================================================================*/
void Input()
{
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		for (int i = 0; i < 4; i++)
		{
			Vertices[i].x += Speed_X;

			// ������ �����ʿ� ��ġ�� ���
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
		// ������ ���۸� ������ ä��ϴ�.
		// ���� ������ Lock() �Լ��� ȣ���Ͽ� �����͸� ���ɴϴ�.
		void* pVertices;

		g_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0);

		// Vertices�� pVertices�� �����մϴ�.
		memcpy(pVertices, Vertices, sizeof(Vertices));

		g_pVB->Unlock();
	}

	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		for (int i = 0; i < 4; i++)
		{
			Vertices[i].x -= Speed_X;

			// ������ ���ʿ� ��ġ�� ���
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
		// ������ ���۸� ������ ä��ϴ�.
		// ���� ������ Lock() �Լ��� ȣ���Ͽ� �����͸� ���ɴϴ�.
		void* pVertices;

		g_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0);

		// Vertices�� pVertices�� �����մϴ�.
		memcpy(pVertices, Vertices, sizeof(Vertices));

		g_pVB->Unlock();
	}
}

/*=============================================================================
 * ȭ�� �׸���
 *=============================================================================*/
void Render()
{
	if (NULL == g_pd3dDevice)
	{
		return;
	}

	// �ĸ� ���۸� �Ķ���(0, 0, 255)���� ����ϴ�.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// ������ ����
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// ���� ������ �ﰢ���� �׸��ϴ�.
		g_pd3dDevice->SetStreamSource(0, g_pCustomVB, 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		/*=============================================================================
		 * HRESULT DrawPrimitive
		 * (
		 *   D3DPRIMITIVETYPE PrimitiveType,
		 *   UINT StartVertex,
		 *	 UINT PrimitiveCount
		 * );
		 * PrimitiveType: �������ϴ� �⺻ ������ ������ ����մϴ�.
		 * StartVertex: �ε��ϴ� ������ ������ �ε����Դϴ�.
		 * PrimitiveCount: ������ �ϴ� �⺻ ������ ���Դϴ�.
		 *=============================================================================*/
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// ���� ������ ��� �ִ� ���� ���۸� ��� ��Ʈ������ �Ҵ��մϴ�.
		g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));

		// D3D���� ���� ���̴� ������ �����մϴ�. ��κ��� ��쿡�� FVF�� �����մϴ�.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// ���� ������ ����ϱ� ���� DrawPrimitive() �Լ��� ȣ���մϴ�.
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		// ������ ����
		g_pd3dDevice->EndScene();
	}

	// �ĸ� ���۸� ���̴� ȭ������ ��ȯ�մϴ�.
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
 * Window ����
 *=============================================================================*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	// ������ Ŭ������ ����մϴ�.
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Vertices", NULL };

	// winclass �������Ϳ� ����մϴ�.
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

	// ��ϵ� ������Ʈ winclass�� ������ �մϴ�.
	UnregisterClass(L"D3D Vertices", wc.hInstance);
	return 0;
}