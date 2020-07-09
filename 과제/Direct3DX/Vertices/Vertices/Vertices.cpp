/*=============================================================================
 * 정점들의 정보를 변경
 * 삼각형 그리기를 이용해서 사각형 그리기
 *=============================================================================*/

// Direct3D9을 사용하기 위한 헤더입니다.
#include <d3d9.h>
#include <d3dx9.h>

/*=============================================================================
 * 전역 변수
 *=============================================================================*/
LPDIRECT3D9			g_pD3D = NULL;
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;	// 정점을 보관할 버퍼입니다.
LPDIRECT3DVERTEXBUFFER9 g_pCustomVB = NULL;

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;		// 정점의 변환된 좌표입니다.(rhw 값이 있으면 변환이 완료된 정점입니다.)
	DWORD color;			// 정점의 색입니다.
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
 * 사용자 정점 구조체에 관한 정보를 나타내는 FVF값입니다.
 * 구조체는 x, y, z, RHW 값과 Diffuse 색 값으로 이루어져 있습니다.
 * D3DFVF_DIFFUSE 옵션으로 꼭지점이 정해져 있다는걸 알려줍니다.
 *=============================================================================*/
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

 /*=============================================================================
  * Direct3D 초기화
  *=============================================================================*/
HRESULT InitD3D(HWND hWnd)
{
	// 디바이스를 생성하기 위한 D3D 객체를 생성합니다.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;				// 디바이스 생성을 위한 구조체입니다.
	ZeroMemory(&d3dpp, sizeof(d3dpp));			// 반드시 ZeroMemory() 함수로 미리 구조체를 깨끗이 지워야 합니다.

	d3dpp.Windowed = TRUE;						// 창 모드로 생성합니다.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	// 가장 효율적인 SWAP 효과입니다.
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	// 현재 바탕화면 모드에 맞춰서 후면 버퍼를 생성합니다.

	// 디바이스를 설정해서 생성합니다.
	// 디폴트 비디오카드를 사용하고, HAL 디바이스를 생성합니다.
	// 정점 처리는 모든 카드에서 지원하는 SW처리로 생성합니다.
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// 디바이스 상태 정보를 처리할 경우 여기에서 합니다.
	
	return S_OK;
}

/*=============================================================================
 * 정점 버퍼 초기화
 *=============================================================================*/
HRESULT InitVB()
{
	// 정점 버퍼를 생성합니다.
	// 정점 구조체4개를 저장할 메모리를 할당합니다.
	// FVF를 지정하여 보관할 데이터의 형식을 지정합니다.
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

	// 정점의 버퍼를 값으로 채웁니다.
	// 정점 버퍼의 Lock() 함수를 호출하여 포인터를 얻어옵니다.
	void* pVertices;

	if (FAILED(g_pVB->Lock(0, sizeof(Vertices), (void**)&pVertices, 0)))
	{
		return E_FAIL;
	}

	// Vertices를 pVertices로 복사합니다.
	memcpy(pVertices, Vertices, sizeof(Vertices));

	g_pVB->Unlock();

	return S_OK;
}

/*=============================================================================
 * 초기화 객체를 Release
 *=============================================================================*/