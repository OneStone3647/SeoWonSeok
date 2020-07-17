/*=============================================================================
 * KeyFrameAnimation
 * ���� ������ �̿��� �ִϸ��̼� ó��
 * �θ�, �ڽ��� ȸ��, �̵� Ű�� ���� ���� ����
 *=============================================================================*/
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <cmath>

#include "GameManager.h"

#define WINDOWWIDTH 1024
#define WINDOWHEIGHT 768


/*=============================================================================
 * ���� ����
 *=============================================================================*/
LPDIRECT3D9			g_pD3D		 = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

GameManager	GM;

D3DXMATRIXA16		g_matTMParent;	// �θ��� �⺻ ���
D3DXMATRIXA16		g_matRParent;	// �θ��� ȸ�� ���

D3DXMATRIXA16		g_matTMChild;	// �ڽ��� �⺻ ���
D3DXMATRIXA16		g_matRChild;	// �ڽ��� ȸ�� ���

LPD3DXFONT			g_Font;
RECT				g_Rect;

float				g_fRot = 0.0f;
float				g_fRevRot = 0.0f;
float				g_X = 0.0f;
float				g_Y = 0.0f;

bool				g_bStart = true;

#define ROT_DELTA 0.1f;

D3DXVECTOR3		g_aniPos[2];
D3DXQUATERNION	g_aniRot[2];

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
 * �ִϸ��̼� �ʱ�ȭ
 *=============================================================================*/
void InitAnimation()
{
	// ��ġ ��ȭ�� ����� ���� ��
	g_aniPos[0] = D3DXVECTOR3(0, 0, 0);		
	g_aniPos[1] = D3DXVECTOR3(5, 5, 5);

	FLOAT Yaw = D3DX_PI * 90.0f / 180.0f;	// Y�� 90�� ȸ��
	FLOAT Pitch = 0;
	FLOAT Roll = 0;

	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[0], Yaw, Pitch, Roll);	// �����(Y�� 90��)

	Yaw = 0;
	Pitch = D3DX_PI * 90.0f / 180.0f;	// X�� 90�� ȸ��
	Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[1], Yaw, Pitch + g_fRot, Roll);	// �����(X�� 90��)
}

/*=============================================================================
 * ���� ���� �ʱ�ȭ
 *=============================================================================*/
HRESULT InitGeometry()
{
	if (FAILED(GM.GetVertex()->InitVB(g_pd3dDevice)))
	{
		return E_FAIL;
	}

	if (FAILED(GM.GetCube()->InitIB(g_pd3dDevice)))
	{
		return E_FAIL;
	}

	SetRect(&g_Rect, 100, 430, 0, 0);

	// ��Ʈ ��ü�� �����մϴ�.
	D3DXCreateFont(g_pd3dDevice, 20, 0, FW_NORMAL, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &g_Font);

	InitAnimation();

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
	D3DXVECTOR3 vEyePt(0.0f, 10.0f, -20.0f);		// ���� ��ġ
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// ���� �ٶ󺸴� ��ġ(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		// �� ������ ��Ÿ���� ��� ����(0.0f, 1.0f, 0.0f)

	// �� ���(ī�޶�)
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);		// 3���� Point�� �̿��� �� ����� �����մϴ�.
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);					// ������ �� ����� ����̽��� �����մϴ�.

	// �������� ����� �����ϱ� ���ؼ��� �þ߰�(FOV = Field Of View)�� ��Ⱦ��(aspect ratio), Ŭ���� ����� ���� �ʿ��մϴ�.
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);		// ������ �������� ����� ����̽��� �����մϴ�.
}

/*=============================================================================
 * �ִϸ��̼� ��� ����
 *=============================================================================*/
void Animate()
{
	static float t = 0;
	static float add = 0.005;
	float x, y, z;
	D3DXQUATERNION quat;

	FLOAT Yaw = D3DX_PI * 90.0f / 180.0f;	// Y�� 90�� ȸ��
	FLOAT Pitch = 0;
	FLOAT Roll = 0;

	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[0], Yaw + g_fRevRot, Pitch + g_fRot, Roll);	// �����(Y�� 90��)

	Yaw = 0;
	Pitch = D3DX_PI * 90.0f / 180.0f;	// X�� 90�� ȸ��
	Roll = 0;
	D3DXQuaternionRotationYawPitchRoll(&g_aniRot[1], Yaw + g_fRevRot, Pitch + g_fRot, Roll);	// �����(X�� 90��)

	D3DXVECTOR3 v;
	/*=============================================================================
	 * �̵����� ���� ����
	 * D3DVECTOR3* D3DXVec3Lerp(D3DVECTOR3* pOut,
	 * D3DVECTOR3* v1,
	 * D3DVECTOR3* v2,
	 * FLOAT t);
	 * v1�� v2 ������ ���� ������ t ũ�⸸ŭ ����� pOut�� �����Ѵ�.
	 *=============================================================================*/
	D3DXVec3Lerp(&v, &g_aniPos[0], &g_aniPos[1], t);
	// �̵� ��İ����� ��ȯ
	D3DXMatrixTranslation(&g_matTMParent, v.x + g_X, v.y + g_Y, v.z);

	/*=============================================================================
	 * ȸ������ ���� ���� ����
	 * D3DXQUATERNION* D3DXQuaternionSlerp
	 * (D3DXQUATERNION *pOut,
	 * CONST D3DXQUATERNION *pQ1,
	 * CONST D3DXQUATERNION *pQ2);
	 * Q1�� Q2 ������ ���� ���� ������ t ũ�⸸ŭ ����� pOut�� �����Ѵ�.
	 *=============================================================================*/
	D3DXQuaternionSlerp(&quat, &g_aniRot[0], &g_aniRot[1], t);
	// ������� ȸ�� ��İ����� ��ȯ
	D3DXMatrixRotationQuaternion(&g_matRParent, &quat);

	if (g_bStart == true)
	{
		// �ݴ� �������� ��ȯ
		if (t<0.0f || t>1.0f)
		{
			add *= -1;
		}

		t += add;
	}

	// �ڽ� �޽��� Z�� ȸ�� ���
	D3DXMatrixRotationZ(&g_matRChild, GetTickCount() / 500.0f);

	// Ư�� vector�� ������ �ϴ� ���
	//D3DXMatrixRotationAxis(&g_matRChild, nomalVec, Angle);

	// �ڽ� �޽ô� �������κ��� (3, 3, 3)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&g_matTMChild, 3, 3, 3);
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
void DrawMesh(D3DXMATRIXA16* pMat)
{
	g_pd3dDevice->SetTransform(D3DTS_WORLD, pMat);
	g_pd3dDevice->SetStreamSource(0, GM.GetVertex()->GetVB(), 0, sizeof(CUSTOMVERTEX));
	g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	g_pd3dDevice->SetIndices(GM.GetCube()->GetIB());
	g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

/*=============================================================================
 * ȭ�� �׸���
 *=============================================================================*/
void Render()
{
	D3DXMATRIXA16 matWorld;

	// �ĸ� ���۸� �Ķ���(0, 0, 255)���� ����� Z���۸� ����ϱ� ���� �ʱ�ȭ�մϴ�.
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// ��Ʈ �׸���
	if (g_bStart == true)
	{
		g_Font->DrawText(NULL, "START", -1, &g_Rect, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	else
	{
		g_Font->DrawText(NULL, "NOT START", -1, &g_Rect, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	Animate();

	// ������ ����
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// �׸��� ������ �ƴ� ��� ���� ������ �߿��մϴ�.
		
		// �θ��� ��ȯ�� ����ϴ�.
		// ȸ�� * �⺻ ��ȯ
		matWorld = g_matRParent * g_matTMParent;
		// ����� ��ȯ�� ������� �θ� ��ü�� �׸��ϴ�.	
		DrawMesh(&matWorld);

		// �ڽ��� ��ȯ�� ����ϴ�.
		// �ڽ��� ȸ�� * �ڽ��� �⺻ ��ȯ * �θ��� ȸ�� * �θ��� �⺻ ��ȯ
		matWorld = g_matRChild * g_matTMChild * g_matRParent * g_matTMParent;
		// ����� ��ȯ�� ������� �θ� ��ü�� �׸��ϴ�
		DrawMesh(&matWorld);

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
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			g_X -= ROT_DELTA;
		}

		if (wParam == VK_RIGHT)
		{
			g_X += ROT_DELTA;
		}

		if (wParam == VK_UP)
		{
			g_Y += ROT_DELTA;
		}

		if (wParam == VK_DOWN)
		{
			g_Y -= ROT_DELTA;
		}

		if (wParam == VK_SHIFT)
		{
			g_fRot += ROT_DELTA;
		}

		if (wParam == VK_RETURN)
		{
			g_fRevRot += ROT_DELTA;
		}

		if (wParam == VK_SPACE)
		{
			if (g_bStart == false)
			{
				g_bStart = true;
			}
			else
			{
				g_bStart = false;
			}

		}

		break;
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
		"D3D Animation", NULL };

	// winclass �������Ϳ� ����մϴ�.
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow("D3D Animation", "D3D Animation", WS_OVERLAPPEDWINDOW, 100, 100, WINDOWWIDTH, WINDOWHEIGHT,
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
	UnregisterClass("D3D Animation", wc.hInstance);
	return 0;
}