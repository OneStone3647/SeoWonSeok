/*=============================================================================
 * �������� ������ ����
 * �ﰢ�� �׸��⸦ �̿��ؼ� �簢�� �׸���
 *=============================================================================*/

// Direct3D9�� ����ϱ� ���� ����Դϴ�.
#include <d3d9.h>
#include <d3dx9.h>

/*=============================================================================
 * ���� ����
 *=============================================================================*/
LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;	// ������ ������ �����Դϴ�.
LPDIRECT3DVERTEXBUFFER9 g_pCustomVB = NULL;

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;		// ������ ��ȯ�� ��ǥ�Դϴ�.(rhw ���� ������ ��ȯ�� �Ϸ�� �����Դϴ�.)
	DWORD color;			// ������ ���Դϴ�.
};

CUSTOMVERTEX Vertices[] =
{
	// x, y, z, rhw, color
	{ 150.0f, 50.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },
	{ 250.0f, 150.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },
	{ 50.0f,  150.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },
	{ 250.0f, 300.0f, 0.5f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },
};

float Speed_X = 2.0f;

/*=============================================================================
 * ����� ���� ����ü�� ���� ������ ��Ÿ���� FVF���Դϴ�.
 * ����ü�� x, y, z, RHW ���� Diffuse �� ������ �̷���� �ֽ��ϴ�.
 * D3DFVF_DIFFUSE �ɼ����� �������� ������ �ִٴ°� �˷��ݴϴ�.
 *=============================================================================*/
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

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

	// ����̽��� �����ؼ� �����մϴ�.
	// ����Ʈ ����ī�带 ����ϰ�, HAL ����̽��� �����մϴ�.
	// ���� ó���� ��� ī�忡�� �����ϴ� SWó���� �����մϴ�.
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// ����̽� ���� ������ ó���� ��� ���⿡�� �մϴ�.
	
	return S_OK;
}

/*=============================================================================
 * ���� ���� �ʱ�ȭ
 *=============================================================================*/
HRESULT InitVB()
{
	// ���� ���۸� �����մϴ�.
	// ���� ����ü4���� ������ �޸𸮸� �Ҵ��մϴ�.
	// FVF�� �����Ͽ� ������ �������� ������ �����մϴ�.
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