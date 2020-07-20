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
void SetupCamera()
{
	// ���� ���
	D3DXMATRIXA16 matWorld;
	
	D3DXMatrixIdentity(&matWorld);		// ���� ����� ���� ��ķ� �����մϴ�.
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