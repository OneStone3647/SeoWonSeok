/*=============================================================================
 * Texture
 * �޽��� �ؽ�ó ������
 *=============================================================================*/
#include <Windows.h>
#include <mmsystem.h>
#include "Vertex.h"

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768

 /*=============================================================================
  * ���� ����
  *=============================================================================*/
LPDIRECT3D9			g_pD3D			= NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice	= NULL;
LPDIRECT3DTEXTURE9	g_pTexture		= NULL;	// �ؽ�ó �������̽� ����

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
	/*-----------------------------------------------------------------------------------
	* �ɼ� �÷���
	* D3DCULL_NONE: �ĸ� �߷����⸦ ������ ���ϴ�.
	* D3DCULL_CW: �ð� ���� �θ��⸦ ���� �ﰢ���� �߷����ϴ�.
	* D3DCULL_CCW: �ð� �ݴ� ���� �θ��⸦ ���� �ﰢ���� �߷����ϴ�. ����Ʈ �����Դϴ�.
	*-----------------------------------------------------------------------------------*/
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// ���� ����� ���ϴ�.
	g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	// ���� ����� �մϴ�.
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

/*=============================================================================
 * ���� ���� �ʱ�ȭ
 * ���� ���ۿ� �ؽ�ó ����
 *=============================================================================*/
HRESULT InitGeometry()
{
	// D3DX �迭 �Լ��� ����Ͽ� ���Ϸκ��� �ؽ�ó ����
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"nateon.jpg", &g_pTexture)))
	{
		// ���� ������ ������ ������ ���� ���� �˻�
		if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"..\\nayeon.jpg", &g_pTexture)))
		{
			MessageBox(NULL, L"Could not find nayeon.jpg", L"Texture.exe", MB_OK);

			return E_FAIL;
		}
	}

	if (FAILED(VT.InitVB(g_pd3dDevice)))
	{
		return E_FAIL;
	}

	return S_OK;
}

/*=============================================================================
 * �ʱ�ȭ ��ü�� Release
 * ���� ������ �߿� �������̽� ������ �������� �����ؾ� �մϴ�.
 *=============================================================================*/
void Release()
{
	if (g_pTexture != NULL)
	{
		g_pTexture->Release();
	}

	if (VT.GetVB() != NULL)
	{
		VT.GetVB()->Release();
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
 * ��� ����: ��Ŀ��� 3������ ������, ���� ����, ��, �������� ����Դϴ�.
 *=============================================================================*/
void SetupMatrices()
{
	// ���� ���
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);								// ���� ����� ���� ��ķ� �����մϴ�.
	D3DXMatrixRotationX(&matWorld, timeGetTime() / 1000.0f);	// X������ ȸ���մϴ�.
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);			// ������ ���� ����� ���� ��ķ� ����̽��� �����մϴ�.

	// �� ���(ī�޶�)�� �����ϱ� ���ؼ��� 3���� ���� �ʿ��մϴ�.
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);		// ���� ��ġ
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// ���� �ٶ󺸴� ��ġ(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		// �� ������ ��Ÿ���� ��� ����(0.0f, 1.0f, 0.0f)

	// �� ���(ī�޶�)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);		// 3���� Point�� �̿��� �� ����� �����մϴ�.
	
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);				// ������ �� ����� ����̽��� �����մϴ�.

	// �������� ����� �����ϱ� ���ؼ��� �þ߰�(FOV = Field Of View)�� ��Ⱦ��(aspect ratio), Ŭ���� ����� ���� �ʿ��մϴ�.
	D3DXMATRIXA16 matProj;
	/*-----------------------------------------------------------------------------------
	 * ù ��° : ������ ���
	 * �� ��° : �þ߰�
	 * �� ��° : ��Ⱦ��
	 * �� ��° : ���� Ŭ����
	 * �ټ� ��° : ���Ÿ� Ŭ����
	 *-----------------------------------------------------------------------------------*/
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// ������ �������� ����� ����̽��� �����մϴ�.
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

	// �ĸ� ���۸� �Ķ���(0,0,255)���� ����ϴ�.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	SetupMatrices();

	// ������ ����
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		/*-----------------------------------------------------------------------------------
		 * ������ �ؽ�ó�� 0�� �ؽ�ó ���������� �ø��ϴ�.
		 * �ؽ��� ���������� ���� ���� �ؽ�ó�� ���� ������ ��� ����� �� ����մϴ�.
		 * ���⼭�� �ױ�ó�� ����� ������ ���� ������ modulate �������� ��� ����մϴ�.
		 * D3DTOP_MODULATE: �μ��� ������ �����մϴ�.
		 *-----------------------------------------------------------------------------------*/
		g_pd3dDevice->SetTexture(0, g_pTexture);								// 0�� �ؽ�ó ���������� �ؽ�ó�� �����մϴ�.
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE); // MODULATE �������� ������ ����
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);	// ù ��° ���� ���� �ؽ�ó�� ��
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE); // �� ��° ���� ���� ������ ��
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);	// alpha ������ ������� �������� ����

#ifndef SHOW_HOW_TO_USE_TCI
		/*-----------------------------------------------------------------------------------
		 * D3D�� �ؽ�ó ��ǥ ���� ����� ����մϴ�.
		 * ī�޶� ��ǥ�迡���� ���� ������ ����Ͽ� �ؽ�ó ��ǥ�� �����մϴ�.
		 * 4*4 ũ���� �ؽ�ó ��ȯ ����� �ؽ�ó ��ǥ �ε���(TCI = Texture Coord Index) ���� ���ڸ�
		 * ����Ͽ� x, y, z TCI ��ǥ�� u, v �ؽ�ó ��ǥ�� ��ȯ�մϴ�.
		 * ����� ���� �ܼ��� (-1.0 ~ +1.0) ���� (0.0 ~ 1.0) ������ ������ ��ȯ�ϴ� ����Դϴ�.
		 * ����, ��, �������� ��ȯ�� ��ģ ������ (-1.0 ~ +1.0) ������ ���� ���� �˴ϴ�.
		 *-----------------------------------------------------------------------------------*/
		D3DXMATRIXA16 mat;
		mat._11 = 0.25f; mat._12 = 0.00f; mat._13 = 0.00f; mat._14 = 0.00f;
		mat._21 = 0.25f; mat._22 = 0.00f; mat._23 = 0.00f; mat._24 = 0.00f;
		mat._31 = 0.25f; mat._32 = 0.00f; mat._33 = 0.00f; mat._34 = 0.00f;
		mat._41 = 0.25f; mat._42 = 0.00f; mat._43 = 0.00f; mat._44 = 0.00f;

		// �ؽ�ó ��ȯ ���
		g_pd3dDevice->SetTransform(D3DTS_TEXTURE0, &mat);
		// 2���� �ؽ�ó ���
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);
		// ī�޶� ��ǥ�� ��ȯ
		g_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION);
#endif

		// ���� ������ ��� �ִ� ���� ���۸� ��� ��Ʈ������ �Ҵ��մϴ�.
		g_pd3dDevice->SetStreamSource(0, VT.GetVB(), 0, sizeof(CUSTOMVERTEX));
		// D3D���� ���� ���̴� ������ �����մϴ�.
		// ��κ� FVF�� �����մϴ�.
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
		L"D3D Texture", NULL };

	// winclass �������Ϳ� ����մϴ�.
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(L"D3D Texture", L"D3D Texture", WS_OVERLAPPEDWINDOW, 100, 100, WINDOWWIDTH, WINDOWHEIGHT,
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
	UnregisterClass(L"D3D Texture", wc.hInstance);
	return 0;
}