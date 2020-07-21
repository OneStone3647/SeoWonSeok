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
  * ���� ����
  *=============================================================================*/
LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

Vertex				VT;

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

	// Z���� ����� ���� ����
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
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// ���� ����� �մϴ�.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

/*=============================================================================
 * ���� ���� �ʱ�ȭ
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
 * �ʱ�ȭ ��ü�� Release
 *=============================================================================*/
void Release()
{
	if (VT.GetVB() != NULL)
	{
		VT.GetVB()->Release();
	}

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
 * ��� ����: ��Ŀ��� 3������ ������, ���� ����, ��, �������� ����Դϴ�.
 *=============================================================================*/
void SetupMatrices()
{
	// ���� ���
	D3DXMATRIXA16 matWorld;
	
	D3DXMatrixIdentity(&matWorld);		// ���� ����� ���� ��ķ� �����մϴ�.
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);	// ������ ���� ����� ���� ��ķ� ����̽��� �����մϴ�.

	// �� ���(ī�޶�)�� �����ϱ� ���ؼ��� 3���� ���� �ʿ��մϴ�.
	D3DXVECTOR3 vEyePt(0.0f, 10.0f, -20.0f);		// ���� ��ġ
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// ���� �ٶ󺸴� ��ġ(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		// �� ������ ��Ÿ���� ��� ����(0.0f, 1.0f, 0.0f)

	// �� ���(ī�޶�)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);		// 3���� Point�� �̿��� �� ����� �����մϴ�.
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);					// ������ �� ����� ����̽��� �����մϴ�.

	// �������� ����� �����ϱ� ���ؼ��� �þ߰�(FOV = Field Of View)�� ��Ⱦ��(aspect ratio), Ŭ���� ����� ���� �ʿ��մϴ�.
	D3DXMATRIXA16 matProj;
	// ù ��° : ������ ���
	// �� ��° : �þ߰�
	// �� ��° : ��Ⱦ��
	// �� ��° : ���� Ŭ����
	// �ټ� ��° : ���Ÿ� Ŭ����
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// ������ �������� ����� ����̽��� �����մϴ�.
}

/*=============================================================================
 * ���� ����
 *=============================================================================*/
void SetupLights()
{
	// ���� ����
	// ������ ����̽��� �� �ϳ��� ������ �� �ֽ��ϴ�.
	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
	g_pd3dDevice->SetMaterial(&mtrl);

	// ���� ����
	D3DXVECTOR3 vecDir;
	// ���⼺ ����(directional light)�� ���� ���� ����
	// ���� ����ü
	D3DLIGHT9 light;
	D3DLIGHT9 spotlight;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	// ������ Ȯ�걤 ������ ��⸦ �����մϴ�.
	// ������ ������ �����Ѵ�(����Ʈ ����Ʈ, ���̷��� ����Ʈ, ����Ʈ ����Ʈ)
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	spotlight.Type = D3DLIGHT_DIRECTIONAL;
	spotlight.Diffuse.r = 1.0f;
	spotlight.Diffuse.g = 1.0f;
	spotlight.Diffuse.b = 1.0f;
	spotlight.Direction = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	//������ ���� ����
	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 350.0f), 1.0f, sinf(timeGetTime() / 350.0f));

	//������ ������ ���� ���ͷ� ����ϴ�.
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f; // ������ �ٴٸ� �� �ִ� �ִ�Ÿ�
	g_pd3dDevice->SetLight(0, &light); // ����̽��� ���� 0���� ��ġ
	g_pd3dDevice->LightEnable(0, TRUE); // ���� 0���� Ȱ��ȭ �մϴ�.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);// ���� ������ Ȱ��ȭ �մϴ�.

	//ȯ�� ������ �� ����
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0x00202020);
}

/*=============================================================================
 * ȭ�� �׸���
 *=============================================================================*/
void Render()
{
	D3DXMATRIXA16 matWorld;

	// �ĸ� ���۸� �Ķ���(0, 0, 255)���� ����� Z���۸� ����ϱ� ���� �ʱ�ȭ�մϴ�.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	SetupLights();

	SetupMatrices();

	// ������ ����
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// ���� ������ ��� �ִ� ���� ���۸� ��� ��Ʈ������ �Ҵ��մϴ�.
		g_pd3dDevice->SetStreamSource(0, VT.GetVB(), 0, sizeof(CUSTOMVERTEX));

		// D3D���� ���� ���̴� ������ �����մϴ�.
		// ��κ� FCF�� �����մϴ�.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// ���� ������ ����ϱ� ���� DrawPrimitive() �Լ��� ȣ���մϴ�.
		g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2 * 50 - 2);

		// ������ ����
		g_pd3dDevice->EndScene();
	}

	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

/*=============================================================================
 * ������ ���ν���
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
	// ������ Ŭ������ ����մϴ�.
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"D3D Light", NULL };

	// winclass �������Ϳ� ����մϴ�.
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

	// ��ϵ� ������Ʈ winclass�� ������ �մϴ�.
	UnregisterClass(L"D3D Light", wc.hInstance);
	return 0;
}