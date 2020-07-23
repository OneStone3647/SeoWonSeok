/*=============================================================================*
 * HeightMap(���̸�)
 * HeightMAp���� - Triangle List
 *=============================================================================*/
#define MAINBODY

#include <d3d9.h>
#include <d3dx9.h>
#include "ZFLog.h"

#define WINDOW_W		500
#define WINDOW_H		500
#define WINDOW_TITLE	L"HeightMap_TList"
#define BMP_HEIGHTMAP	L"map128.bmp"

/*=============================================================================*
 * ���� ����
 *=============================================================================*/
HWND					g_hWnd;

LPDIRECT3D9				g_pD3D			= NULL;
LPDIRECT3DDEVICE9		g_pd3dDevice	= NULL;
LPDIRECT3DVERTEXBUFFER9	g_pVB			= NULL;
LPDIRECT3DINDEXBUFFER9	g_pIB			= NULL;

LPDIRECT3DTEXTURE9		g_pTexHeight	= NULL;	// Texture ���̸�
LPDIRECT3DTEXTURE9		g_pTextDiffuse	= NULL;	// Texture �����
D3DXMATRIXA16			g_matAni;

DWORD					g_cxHeight = 0;
DWORD					g_czHeight = 0;

struct CUSTOMVERTEX
{
	D3DXVECTOR3		p;
	D3DXVECTOR3		n;
	D3DXVECTOR3		t;
};

// ����� ���� ����ü�� ���� ������ ��Ÿ���� FVF��
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct MYINDEX
{
	WORD	_0, _1, _2;
};

/*=============================================================================*
 * Direct3D �ʱ�ȭ
 *=============================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return S_OK;
}

/*=============================================================================*
 * �ؽ�ó �ʱ�ȭ
 *=============================================================================*/
HRESULT InitTexture()
{
	// ���̸� �ؽ�ó
	// D3DFMT_X8R8G8B8��  D3DPOOL_MANAGED�� �ֱ� ���ؼ� �� �Լ��� ����Ͽ����ϴ�.
	if (FAILED(D3DXCreateTextureFromFileEx(g_pd3dDevice, BMP_HEIGHTMAP,
		D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, 0,
		D3DFMT_X8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0,
		NULL, NULL, &g_pTexHeight)))
	{
		return E_FAIL;
	}

	// �����
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, L"tile2.tga", &g_pTextDiffuse)))
	{
		return E_FAIL;
	}

	return S_OK;
}

/*=============================================================================*
 * �������۸� �����ϰ� �������� ä�� �ֽ��ϴ�.
 *=============================================================================*/
HRESULT InitVB()
{
	D3DSURFACE_DESC		ddsd;
	D3DLOCKED_RECT		d3drc;

	g_pTexHeight->GetLevelDesc(0, &ddsd);	// �ؽ�ó�� ����
	g_cxHeight = ddsd.Width;				// �ؽ�ó�� ���� ũ��
	g_czHeight = ddsd.Height;				// �ؽ�ó�� ���� ũ��

	g_pLog->Log("Texture Size: [%d, %d]", g_cxHeight, g_czHeight);
	if (FAILED(g_pd3dDevice->CreateVertexBuffer(ddsd.Width * ddsd.Height * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL)))
	{
		return E_FAIL;
	}

	// �ؽ�ó �޸� ��
	g_pTexHeight->LockRect(0, &d3drc, NULL, D3DLOCK_READONLY);
	VOID* pVertices;
	// �������� ��
	if (FAILED(g_pVB->Lock(0, g_cxHeight*g_czHeight * sizeof(CUSTOMVERTEX), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	CUSTOMVERTEX v;
	CUSTOMVERTEX* pV = (CUSTOMVERTEX*)pVertices;

	for (DWORD z = 0; z < g_czHeight; z++)
	{
		for (DWORD x = 0; x < g_czHeight; x++)
		{
			v.p.x = (float)x - g_czHeight / 2.0f;		// ������ x��ǥ(�޽ø� ������ ����)
			v.p.z = -((float)z - g_czHeight / 2.0f);	// ������ z��ǥ(�޽ø� ������ ����), z���� ����� �����̹Ƿ� -�� ���Ѵ�.
			v.p.y = ((float)(*((LPDWORD)d3drc.pBits + x + z * (d3drc.Pitch / 4)) & 0x000000ff)) / 10.0f;	// DWORD�̹Ƿ� pitch/4
			v.n.x = v.p.x;
			v.n.y = v.p.y;
			v.n.z = v.p.z;
			/*-----------------------------------------------------------------------------*
			 * D3DXVECTOR3 *WINAPI D3DXVec3Normalize(
			 * D3DXVECTOR3 *pOut,
			 * CONST D3DXVECTOR3 *pV
			 * );
			 * 3D ������ ����ȭ�� ���͸� �����ش�.
			 * pOut: ���� ����� D3DXVECTOR3 ����ü�� ������
			 * pV: ����ȭ�� D3DVECTOR3 ����ü�� ������
			 *-----------------------------------------------------------------------------*/
			D3DXVec3Normalize(&v.n, &v.n);
			v.t.x = (float)x / (g_cxHeight - 1);
			v.t.y = (float)z / (g_czHeight - 1);
			*pV++ = v;
			//g_pLog->Log( "[%f, %f, %f]", v.x, v.y, v.z);
		}
	}

	g_pVB->Unlock();
	g_pTexHeight->UnlockRect(0);

	return S_OK;
}

/*=============================================================================*
 * �ε��� ���� �ʱ�ȭ
 *=============================================================================*/
HRESULT InitIB()
{
	if (FAILED(g_pd3dDevice->CreateIndexBuffer((g_czHeight - 1)*(g_czHeight - 1) * 2 * sizeof(MYINDEX),
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL)))
	{
		return E_FAIL;
	}

	MYINDEX		i;
	MYINDEX*	pI;
	if (FAILED(g_pIB->Lock(0, (g_cxHeight - 1) * (g_czHeight - 1) * 2 * sizeof(MYINDEX), (void**)&pI, 0)))
	{
		return E_FAIL;
	}

	for (DWORD z = 0; z < g_czHeight - 1; z++)
	{
		for (DWORD x = 0; x < g_cxHeight - 1; x++)
		{
			i._0 = (z*g_cxHeight + x);
			i._1 = (z + g_cxHeight + x + 1);
			i._2 = ((z + 1)*g_cxHeight + x);

			*pI++ = i;

			i._0 = ((z + 1)*g_cxHeight + x);
			i._1 = (z*g_cxHeight + x + 1);
			i._2 = ((z + 1)*g_cxHeight + x + 1);

			*pI++ = i;
		}
	}

	g_pIB->Unlock();

	return S_OK;
}

/*=============================================================================*
 * ���� ���� �ʱ�ȭ
 *=============================================================================*/
HRESULT InitGeometry()
{
	if (FAILED(InitTexture()))
	{
		return E_FAIL;
	}

	if (FAILED(InitVB()))
	{
		return E_FAIL;
	}

	if (FAILED(InitIB()))
	{
		return E_FAIL;
	}

	return S_OK;
}

/*=============================================================================*
 * ī�޶� ��� ����
 *=============================================================================*/
void SetupCamera()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3		vEyePt(0.0f, 100.0f, -(float)g_czHeight);
	D3DXVECTOR3		vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3		vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16	matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
}