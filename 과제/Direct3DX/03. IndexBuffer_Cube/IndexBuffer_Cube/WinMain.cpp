/*=============================================================================
 * 2�� �̻��� ����ü�� �ε����� �����ؼ� ����� ����
 * �� ����� ���� ����
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

float	g_X = 0.0f;
float	g_Y = 20.0f;
float	g_Z = -20.0f;

float	g_Speed = 0.5f;

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

	d3dpp.EnableAutoDepthStencil = TRUE;		// ���̰� �ִ� Z���۰� �ʿ��ϹǷ� �����մϴ�.
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
 * ��� ����
 * ��Ŀ��� 3������ ������, ���� ��, ��, ��������, ����Դϴ�.
 *=============================================================================*/
void SetupMatrices()
{
	D3DXMatrixIdentity(GM.GetmatWorld());	// ���� ����� ���� ��ķ� �����մϴ�.

	//D3DXMatrixRotationY(&matWorld, GetTickCount() / 500.0f); // Y���� ȸ�������� ȸ�� ����� �����Ѵ�.
	//D3DXMatrixTranslation(GM.GetmatWorld(), GM.GetSpeed(), 0.0f, 0.0f);

	g_pd3dDevice->SetTransform(D3DTS_WORLD, GM.GetmatWorld());	// ������ ȸ�� ����� ���� ��ķ� ����̽��� �����մϴ�.

	// �� ���(ī�޶�)�� �����ϱ� ���ؼ��� 3���� ���� �ʿ��մϴ�.
	D3DXVECTOR3 vEyePt(g_X, g_Y, g_Z);			// ���� ��ġ
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// ���� �ٶ󺸴� ��ġ(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);				// �� ������ ��Ÿ���� ��� ����(0.0f, 1.0f, 0.0f)

	// �� ���(ī�޶�)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);		// 3���� Point�� �̿��� �� ����� �����մϴ�.

	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);	// ������ �� ����� ����̽��� �����մϴ�.

	// �������� ����� �����ϱ� ���ؼ��� �þ߰�(FOV = Field Of View)�� ��Ⱦ��(aspect ratio), Ŭ���� ����� ���� �ʿ��մϴ�.
	D3DXMATRIXA16 matProj;

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);

	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// ������ �������� ����� ����̽��� �����մϴ�.
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
 * �Է�
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
 * ȭ�� �׸���
 *=============================================================================*/
void Render()
{
	if (NULL == g_pd3dDevice)
	{
		return;
	}

	// �ĸ� ���۸� �Ķ���(0, 0, 255)���� ����� Z���۸� ����ϱ� ���� �ʱ�ȭ�մϴ�.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//����, ��, �������� ����� �����Ѵ�.
	SetupMatrices();

	// ������ ����
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// ���� ������ ��� �ִ� ���� ���۸� ��� ��Ʈ������ �Ҵ��մϴ�.
		g_pd3dDevice->SetStreamSource(0, GM.GetVertex(0)->GetVB(), 0, sizeof(CUSTOMVERTEX));

		// D3D���� ���� ���̴� ������ �����մϴ�. ��κ��� ��쿡�� FVF�� �����մϴ�.
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		// �ε��� ���۸� �����մϴ�.
		g_pd3dDevice->SetIndices(GM.GetCube()->GetIB());

		// ���� ������ ����ϱ� ���� DrawIndexPrimitive() �Լ��� ȣ���մϴ�.
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
		 * Type: �׸����� �ϴ� �⺻ Ÿ��
		 * BaseVertexIndex: ���� ������Ʈ�� �ϳ��� ���� �� ������ �ѹ�
		 * MinIndex: ������ �ּ� �ε��� ��
		 * NumVertices: �̹� ȣ�⿡ ������ ���ؽ��� ��
		 * StartIndex: �ε��� ���� ������ �б⸦ ������ �ε��� ��ȣ
		 * PrimitiveCount: ������ �ϴ� �⺻ ������ ��
		 *=============================================================================*/
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

		g_pd3dDevice->SetStreamSource(0, GM.GetVertex(1)->GetVB(), 0, sizeof(CUSTOMVERTEX));
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

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
		L"D3D IndexBuffer", NULL };

	// winclass �������Ϳ� ����մϴ�.
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

	// ��ϵ� ������Ʈ winclass�� ������ �մϴ�.
	UnregisterClass(L"D3D IndexBuffer", wc.hInstance);
	return 0;
}