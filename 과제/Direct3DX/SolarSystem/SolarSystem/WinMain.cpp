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

D3DXMATRIXA16		g_matTMSun;			// �¾��� ��ȯ ���
D3DXMATRIXA16		g_matRSun;			// �¾��� ȸ�� ���
DWORD				g_SunColor = D3DCOLOR_XRGB(255, 0, 0);		// �¾��� ��

D3DXMATRIXA16		g_matSMercury;		// ������ ������ ���
D3DXMATRIXA16		g_matTMMercury;		// ������ ��ȯ ���
D3DXMATRIXA16		g_matRMercury;		// ������ ȸ�� ���
DWORD				g_MercuryColor = D3DCOLOR_XRGB(153, 102, 255);	// ������ ��

D3DXMATRIXA16		g_matSVenus;		// �ݼ��� ������ ���
D3DXMATRIXA16		g_matTMVenus;		// �ݼ��� ��ȯ ���
D3DXMATRIXA16		g_matRVenus;		// �ݼ��� ȸ�� ���
DWORD				g_VenusColor = D3DCOLOR_XRGB(255, 204, 0);	// �ݼ��� ��

D3DXMATRIXA16		g_matSEarth;		// ������ ������ ���
D3DXMATRIXA16		g_matTMEarth;		// ������ ��ȯ ���
D3DXMATRIXA16		g_matREarth;		// ������ ȸ�� ���
DWORD				g_EarthColor = D3DCOLOR_XRGB(51, 0, 255);	// ������ ��

D3DXMATRIXA16		g_matSMoon;			// ���� ������ ���
D3DXMATRIXA16		g_matTMMoon;		// ���� ��ȯ ���
D3DXMATRIXA16		g_matRMoon;			// ���� ȸ�� ���
DWORD				g_MoonColor = D3DCOLOR_XRGB(0, 102, 102);		// ���� ��

D3DXMATRIXA16		g_matSMars;			// ȭ���� ������ ���
D3DXMATRIXA16		g_matTMMars;		// ȭ���� ��ȯ ���
D3DXMATRIXA16		g_matRMars;			// ȭ���� ȸ�� ���
DWORD				g_MarsColor = D3DCOLOR_XRGB(204, 153, 51);		// ȭ���� ��

D3DXMATRIXA16		g_matSJupiter;		// ���� ������ ���
D3DXMATRIXA16		g_matTMJupiter;		// ���� ��ȯ ���
D3DXMATRIXA16		g_matRJupiter;		// ���� ȸ�� ���
DWORD				g_JupiterColor = D3DCOLOR_XRGB(51, 204, 204);	// ���� ��

D3DXMATRIXA16		g_matSSaturn;		// �伺�� ������ ���
D3DXMATRIXA16		g_matTMSaturn;		// �伺�� ��ȯ ���
D3DXMATRIXA16		g_matRSaturn;		// �伺�� ȸ�� ���
DWORD				g_SaturnColor = D3DCOLOR_XRGB(255, 204, 153);	// �伺�� ��

D3DXMATRIXA16		g_matSUranus;		// õ�ռ��� ������ ���
D3DXMATRIXA16		g_matTMUranus;		// õ�ռ��� ��ȯ ���
D3DXMATRIXA16		g_matRUranus;		// õ�ռ��� ȸ�� ���
DWORD				g_UranusColor = D3DCOLOR_XRGB(153, 255, 255);	// õ�ռ��� ��

D3DXMATRIXA16		g_matSNeptune;		// �ؿռ��� ������ ���
D3DXMATRIXA16		g_matTMNeptune;		// �ؿռ��� ��ȯ ���
D3DXMATRIXA16		g_matRNeptune;		// �ؿռ��� ȸ�� ���
DWORD				g_NeptuneColor = D3DCOLOR_XRGB(102, 51, 255);	// �ؿռ��� ��

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
 * ī�޶� ��� ����
 *=============================================================================*/
void SetupMatrices()
{
	D3DXMatrixIdentity(GM.GetmatWorld());	// ���� ����� ���� ��ķ� �����մϴ�.
	//D3DXMatrixRotationY(&matWorld, GetTickCount() / 500.0f); // Y���� ȸ�������� ȸ�� ����� �����Ѵ�.
	//D3DXMatrixTranslation(GM.GetmatWorld(), GM.GetSpeed(), 0.0f, 0.0f);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, GM.GetmatWorld());	// ������ ȸ�� ����� ���� ��ķ� ����̽��� �����մϴ�.

	// �� ���(ī�޶�)�� �����ϱ� ���ؼ��� 3���� ���� �ʿ��մϴ�.
	D3DXVECTOR3 vEyePt(0.0f, 10.0f, -25.0f);	// ���� ��ġ
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);	// ���� �ٶ󺸴� ��ġ(0.0f, 0.0f, 0.0f)
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);		// �� ������ ��Ÿ���� ��� ����(0.0f, 1.0f, 0.0f)

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
 * �ִϸ��̼� ��� ����
 *=============================================================================*/

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