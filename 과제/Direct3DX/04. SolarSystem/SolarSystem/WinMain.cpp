/*=============================================================================
 * �¾��
 *=============================================================================*/
#pragma once
#include "GameManager.h"

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768

/*=============================================================================
 * ���� ����
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

D3DXMATRIXA16		g_matTMSun;		// �¾��� ��ȯ ���
D3DXMATRIXA16		g_matRSun;			// �¾��� ȸ�� ���
DWORD					g_SunColor = D3DCOLOR_XRGB(255, 0, 0);				// �¾��� ��

D3DXMATRIXA16		g_matSMercury;		// ������ ������ ���
D3DXMATRIXA16		g_matTMMercury;	// ������ ��ȯ ���
D3DXMATRIXA16		g_matRMercury;		// ������ ȸ�� ���
D3DXMATRIXA16		g_matRevMercury;	// ������ ���� ���
DWORD					g_MercuryColor = D3DCOLOR_XRGB(153, 102, 255);	// ������ ��

D3DXMATRIXA16		g_matSVenus;		// �ݼ��� ������ ���
D3DXMATRIXA16		g_matTMVenus;		// �ݼ��� ��ȯ ���
D3DXMATRIXA16		g_matRVenus;		// �ݼ��� ȸ�� ���
D3DXMATRIXA16		g_matRevVenus;		// �ݼ��� ���� ���
DWORD					g_VenusColor = D3DCOLOR_XRGB(255, 204, 0);		// �ݼ��� ��

D3DXMATRIXA16		g_matSEarth;			// ������ ������ ���
D3DXMATRIXA16		g_matTMEarth;		// ������ ��ȯ ���
D3DXMATRIXA16		g_matREarth;			// ������ ȸ�� ���
D3DXMATRIXA16		g_matRevEarth;		// ������ ���� ���
DWORD					g_EarthColor = D3DCOLOR_XRGB(51, 0, 255);			// ������ ��

D3DXMATRIXA16		g_matSMoon;		// ���� ������ ���
D3DXMATRIXA16		g_matTMMoon;		// ���� ��ȯ ���
D3DXMATRIXA16		g_matRMoon;		// ���� ȸ�� ���
D3DXMATRIXA16		g_matRevMoon;		// ���� ���� ���
DWORD					g_MoonColor = D3DCOLOR_XRGB(0, 102, 102);		// ���� ��

D3DXMATRIXA16		g_matSMars;			// ȭ���� ������ ���
D3DXMATRIXA16		g_matTMMars;		// ȭ���� ��ȯ ���
D3DXMATRIXA16		g_matRMars;			// ȭ���� ȸ�� ���
D3DXMATRIXA16		g_matRevMars;		// ȭ���� ���� ���
DWORD					g_MarsColor = D3DCOLOR_XRGB(204, 153, 51);		// ȭ���� ��

D3DXMATRIXA16		g_matSJupiter;		// ���� ������ ���
D3DXMATRIXA16		g_matTMJupiter;		// ���� ��ȯ ���
D3DXMATRIXA16		g_matRJupiter;		// ���� ȸ�� ���
D3DXMATRIXA16		g_matRevJupiter;	// ���� ���� ���
DWORD					g_JupiterColor = D3DCOLOR_XRGB(51, 204, 204);		// ���� ��

D3DXMATRIXA16		g_matSSaturn;		// �伺�� ������ ���
D3DXMATRIXA16		g_matTMSaturn;		// �伺�� ��ȯ ���
D3DXMATRIXA16		g_matRSaturn;		// �伺�� ȸ�� ���
D3DXMATRIXA16		g_matRevSaturn;		// �伺�� ���� ���
DWORD					g_SaturnColor = D3DCOLOR_XRGB(255, 204, 153);	// �伺�� ��

D3DXMATRIXA16		g_matSUranus;		// õ�ռ��� ������ ���
D3DXMATRIXA16		g_matTMUranus;	// õ�ռ��� ��ȯ ���
D3DXMATRIXA16		g_matRUranus;		// õ�ռ��� ȸ�� ���
D3DXMATRIXA16		g_matRevUranus;	// õ�ռ��� ���� ���
DWORD					g_UranusColor = D3DCOLOR_XRGB(102, 153, 255);	// õ�ռ��� ��

D3DXMATRIXA16		g_matSNeptune;		// �ؿռ��� ������ ���
D3DXMATRIXA16		g_matTMNeptune;	// �ؿռ��� ��ȯ ���
D3DXMATRIXA16		g_matRNeptune;		// �ؿռ��� ȸ�� ���
D3DXMATRIXA16		g_matRevNeptune;	// �ؿռ��� ���� ���
DWORD					g_NeptuneColor = D3DCOLOR_XRGB(153, 255, 0);	// �ؿռ��� ��

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

	d3dpp.Windowed = TRUE;								// â ���� �����մϴ�.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// ���� ȿ������ SWAP ȿ���Դϴ�.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	// ���� ����ȭ�� ��忡 ���缭 �ĸ� ���۸� �����մϴ�.
	d3dpp.EnableAutoDepthStencil = TRUE;				// ���̰� �ִ� Z���۰� �ʿ��ϹǷ� �����մϴ�.
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	// 16��Ʈ�� ���� ���� �������� �����մϴ�.

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
 * ī�޶� ��� ����
 *=============================================================================*/
void SetupCamera()
{
	D3DXMatrixIdentity(GM.GetmatWorld());		// ���� ����� ���� ��ķ� �����մϴ�.
	g_pd3dDevice->SetTransform(D3DTS_WORLD, GM.GetmatWorld());	// ������ ���� ����� ���� ��ķ� ����̽��� �����մϴ�.

	// �� ���(ī�޶�)�� �����ϱ� ���ؼ��� 3���� ���� �ʿ��մϴ�.
	D3DXVECTOR3 vEyePt(80.0f, 50.0f, -25.0f);		// ���� ��ġ
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// ���� �ٶ󺸴� ��ġ(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		// �� ������ ��Ÿ���� ��� ����(0.0f, 1.0f, 0.0f)

	// �� ���(ī�޶�)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);		// 3���� Point�� �̿��� �� ����� �����մϴ�.
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);					// ������ �� ����� ����̽��� �����մϴ�.

	// �������� ����� �����ϱ� ���ؼ��� �þ߰�(FOV = Field Of View)�� ��Ⱦ��(aspect ratio), Ŭ���� ����� ���� �ʿ��մϴ�.
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 500.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// ������ �������� ����� ����̽��� �����մϴ�.
}

/*=============================================================================
 * �ִϸ��̼� ��� ����
 *=============================================================================*/
void Animate()
{
	// Sun�� �޽ô� ������ �����Ƿ� TMSun�� ���� ����Դϴ�.
	D3DXMatrixIdentity(&g_matTMSun);
	// Sun �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matTMSun, GetTickCount() / 5000.0f);

	// Mercury �޽ô� Sun���� ���� (10, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMMercury, 10, 0, 0);
	// Mercury�� ������ ����
	D3DXMatrixScaling(&g_matSMercury, 0.4f, 0.4f, 0.4f);
	// Mercury �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matRMercury, GetTickCount() / 7000.0f);

	// Venus �޽ô� Sun���� ���� (10, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMVenus, 10, 0, 0);
	// Venus�� ������ ����
	D3DXMatrixScaling(&g_matSVenus, 0.5f, 0.5f, 0.5f);
	// Venus �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matRVenus, GetTickCount() / 3000.0f);

	// Earth �޽ô� Sun���� ���� (12, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMEarth, 12, 0, 0);
	// Earth�� ������ ����
	D3DXMatrixScaling(&g_matSEarth, 0.7f, 0.7f, 0.7f);
	// Earth �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matREarth, GetTickCount() / 6000.0f);

	// Moon �޽ô� Earth���� ���� (8, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMMoon, 8, 0, 0);
	// Moon�� ������ ����
	D3DXMatrixScaling(&g_matSMoon, 0.3f, 0.3f, 0.3f);
	// Moon �޽��� Z�� ȸ�� ���
	D3DXMatrixRotationZ(&g_matRMoon, GetTickCount() / 2000.0f);
	// Moon �޽��� X�� ȸ�� ���
	//D3DXMatrixRotationX(&g_matRevMoon, GetTickCount() / 2000.0f);

	// Mars �޽ô� Sun���� ���� (12, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMMars, 12, 0, 0);
	// Mars�� ������ ����
	D3DXMatrixScaling(&g_matSMars, 1.2f, 1.2f, 1.2f);
	// Mars �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matRMars, GetTickCount() / 2000.0f);

	// Jupiter �޽ô� Sun���� ���� (20, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMJupiter, 20, 0, 0);
	// Jupiter�� ������ ����
	D3DXMatrixScaling(&g_matSJupiter, 0.9f, 0.9f, 0.9f);
	// Jupiter �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matRJupiter, GetTickCount() / 5000.0f);

	// Saturn �޽ô� Sun���� ���� (15, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMSaturn, 15, 0, 0);
	// Saturn�� ������ ����
	D3DXMatrixScaling(&g_matSSaturn, 0.7f, 0.7f, 0.7f);
	// Saturn �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matRSaturn, GetTickCount() / 4000.0f);

	// Uranus �޽ô� Sun���� ���� (50, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMUranus, 50, 0, 0);
	// Uranus�� ������ ����
	D3DXMatrixScaling(&g_matSUranus, 0.4f, 0.4f, 0.4f);
	// Uranus �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matRUranus, GetTickCount() / 3000.0f);

	// Neptune �޽ô� Sun���� ���� (12, 0, 0)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMNeptune, 55, 0, 0);
	// Neptune�� ������ ����
	D3DXMatrixScaling(&g_matSNeptune, 0.4f, 0.4f, 0.4f);
	// Neptune �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&g_matRNeptune, GetTickCount() / 1000.0f);
}

/*=============================================================================
 * �ʱ�ȭ ��ü�� Release
 *=============================================================================*/
void Release()
{
	GM.Release();

	// ���� ������ �߿��մϴ�.
	// �������̽� ������ �������� �����մϴ�.
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
 * �޽� �׸���
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
 * ȭ�� �׸���
 *=============================================================================*/
void Render()
{
	D3DXMATRIXA16 matWorld;

	// �ĸ� ���۸� �Ķ���(0, 0, 255)���� ����� Z���۸� ����ϱ� ���� �ʱ�ȭ�մϴ�.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	Animate();

	// ������ ����
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		matWorld = g_matTMSun;		
		// Sun�� �׸��ϴ�.
		DrawMesh(&matWorld, PLANETNUM_SUN);

		// Mercury�� ��ȯ�� ����ϴ�.
		matWorld = g_matTMMercury * g_matSMercury * g_matRMercury * matWorld;
		DrawMesh(&matWorld, PLANETNUM_MERCURY);

		// Venus�� ��ȯ�� ����ϴ�.
		matWorld = g_matTMVenus * g_matSVenus * g_matRVenus * g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_VENUS);

		// Earth�� ��ȯ�� ����ϴ�.
		matWorld = g_matTMEarth* g_matSEarth * g_matREarth* g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_EARTH);

		// Moon�� ��ȯ�� ����ϴ�.
		matWorld = g_matTMMoon * g_matSMoon * g_matRMoon * matWorld;
		DrawMesh(&matWorld, PLANETNUM_MOON);

		// Mars�� ��ȯ�� ����ϴ�.
		matWorld = g_matTMMars * g_matSMars * g_matRMars * g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_MARS);

		// Jupiter�� ��ȯ�� ����ϴ�.
		matWorld = g_matTMJupiter * g_matSJupiter * g_matRJupiter * g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_JUPITER);

		// Saturn�� ��ȯ�� ����ϴ�.
		matWorld = g_matTMSaturn * g_matSSaturn* g_matRSaturn* g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_SATURN);

		// Uranus�� ��ȯ�� ����ϴ�.
		matWorld = g_matTMUranus * g_matSUranus* g_matRUranus* g_matTMSun;
		DrawMesh(&matWorld, PLANETNUM_URANUS);

		// Neptune�� ��ȯ�� ����ϴ�.
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
 * Window ����
 *=============================================================================*/
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	// ������ Ŭ������ ����մϴ�.
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D SolarSystem", NULL };

	// winclass �������Ϳ� ����մϴ�.
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

	// ��ϵ� ������Ʈ winclass�� ������ �մϴ�.
	UnregisterClass(L"D3D SolarSystem", wc.hInstance);
	return 0;
}