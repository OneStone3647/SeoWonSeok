#include "ZFLog.h"
#include "ZTerrain.h"
#include "Dib.h"

// 생성자
ZTerrain::ZTerrain()
{
	m_cxDIB = 0;
	m_czDIB = 0;
	m_cyDIB = 0;
	m_vfScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_pvHeightMap = NULL;
	m_pd3dDevice = NULL;

	for (int i = 0; i < MAX_TERRAIN_TEX; i++)
	{
		m_pTex[i] = NULL;
	}

	m_pVB = NULL;
	m_pIB = NULL;
	m_nTriangles = 0;
	m_pQuadTree = NULL;
}

// 소멸자
ZTerrain::~ZTerrain()
{
	Destroy();
}

/*===================================================================================*
 * 지형 객체를 초기화합니다.
 * pDev: 출력용 D3D디바이스
 * pvfScale: 높이맵의 x, y, z 값에 곱할 척도 값(scale vector)
 * fLODRatio: LOD처리 시에 사용될 값
 * lpBMPFilename: 높이맵용 BMP파일명
 * lpTexFilename: 출력용 D3D디아비스
 *===================================================================================*/
HRESULT ZTerrain::Create(LPDIRECT3DDEVICE9 pDev, D3DXVECTOR3 * pvfScale, float fLODRatio, const char * lpBmpFilename, LPCWSTR lpTexFilename[MAX_TERRAIN_TEX])
{
	m_pd3dDevice = pDev;
	m_vfScale = *pvfScale;
	m_fLODRatio = fLODRatio;

	if (FAILED(BuildHeightMap(lpBmpFilename)))
	{
		Destroy();
		return E_FAIL;
	}
	if (FAILED(LoadTextures(lpTexFilename)))
	{
		Destroy();
		return E_FAIL;
	}
	if (FAILED(CreateVIB()))
	{
		Destroy();
		return E_FAIL;
	}

	m_pQuadTree = new ZQuadTree(m_cxDIB, m_czDIB);

	if (FAILED(BuildQuadTree()))
	{
		Destroy();
		return E_FAIL;
	}

	return S_OK;
}

// 지형 객체를 메모리에서 소거합니다.
HRESULT ZTerrain::Destroy()
{
	DEL(m_pQuadTree);
	DELS(m_pvHeightMap);
	REL(m_pVB);
	REL(m_pIB);

	for (int i = 0; i < 4; i++)
	{
		REL(m_pTex[i]);
	}

	return S_OK;
}

// 지형객체에서 사용할 텍스처를 읽어들입니다.
HRESULT ZTerrain::LoadTextures(LPCWSTR lpTexFilename[MAX_TERRAIN_TEX])
{
	for (int i = 0; i < 4; i++)
	{
		D3DXCreateTextureFromFile(m_pd3dDevice, lpTexFilename[i], &m_pTex[i]);
	}

	return S_OK;
}

// BMP파일을 열어서 높이맵을 생성합니다.
HRESULT ZTerrain::BuildHeightMap(const char * lpFilename)
{
	int n;
	LPBYTE pDIB = DibLoadHandle(lpFilename);
	if (!pDIB)
	{
		return E_FAIL;
	}

	m_cxDIB = DIB_CX(pDIB);
	m_czDIB = DIB_CY(pDIB);

	// m_cxDIB나 m_czDIB가 (2^n+1)이 아닌 경우 E_FAIL을 반환
	n = Log2(m_cxDIB);
	if ((Pow2(n) + 1) != m_cxDIB)
	{
		return E_FAIL;
	}
	n = Log2(m_czDIB);
	if ((Pow2(n) + 1) != m_czDIB)
	{
		return E_FAIL;
	}

	m_pvHeightMap = new TERRAINVERTEX[m_cxDIB * m_czDIB];

	TERRAINVERTEX v;

	for (int z = 0; z < m_czDIB; z++)
	{
		for (int x = 0; x < m_cxDIB; x++)
		{
			v.p.x = (float)((x - m_cxDIB / 2)*m_vfScale.x);
			v.p.z = -(float)((z - m_czDIB / 2)*m_vfScale.z);
			v.p.y = (float)(*(DIB_DATAXY_INV(pDIB, x, z))) * m_vfScale.y;
			D3DXVec3Normalize(&v.n, &v.p);
			v.t.x = (float)x / (float)(m_cxDIB - 1);
			v.t.y = (float)z / (float)(m_czDIB - 1);
			m_pvHeightMap[x + z * m_czDIB] = v;
		}
	}

	DibDeleteHandle(pDIB);

	return S_OK;
}

// BMP파일의 크기에 맞춰서 쿼드트리를 생성합니다.
HRESULT ZTerrain::BuildQuadTree()
{
	m_pQuadTree->Build(m_pvHeightMap);

	return S_OK;
}

// 정점, 인덱스 버퍼를 생성합니다.
HRESULT ZTerrain::CreateVIB()
{
	// VB생성
	if (FAILED(m_pd3dDevice->CreateVertexBuffer(m_cxDIB * m_czDIB * sizeof(TERRAINVERTEX),
		0, TERRAINVERTEX::FVF, D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		Destroy();
		return E_FAIL;
	}

	VOID* pVertices;
	if (FAILED(m_pVB->Lock(0, m_cxDIB * m_czDIB * sizeof(TERRAINVERTEX), (void**)&pVertices, 0)))
	{
		Destroy();
		return E_FAIL;
	}

	memcpy(pVertices, m_pvHeightMap, m_cxDIB * m_czDIB * sizeof(TERRAINVERTEX));
	m_pVB->Unlock();

#ifdef _USE_INDEX16
	// IB 생성
	if (FAILED(m_pd3dDevice->CreateIndexBuffer((m_cxDIB - 1) * (m_czDIB - 1) * 2 * sizeof(TRIINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
		Destroy();
		return E_FAIL;
	}
	g_pLog->Log("Using 16bit index buffer...");
#else
	// IB 생성
	if (FAILED(m_pd3dDevice->CreateIndexBuffer((m_cxDIB - 1) * (m_czDIB - 1) * 2 * sizeof(TRIINDEX), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
		Destroy();
		return E_FAIL;
	}
	g_pLog->Log("Using 32bit index buffer...");
#endif // _USE_INDEX16

	return S_OK;
}

// 화면에 지형을 출력합니다.
HRESULT ZTerrain::Render()
{
	m_pd3dDevice->SetTexture(0, m_pTex[0]);												// 0번 텍스처 스테이지에 텍스처 고정(색깔맵)
	m_pd3dDevice->SetTexture(1, m_pTex[1]);												// 1번 텍스처 스테이지에 텍스처 고정(음영맵)
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 0번 텍스처 스테이지의 확대 필터
	m_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 1번 텍스처 스테이지의 확대 필터
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);			// 0번 텍스처: 0번 텍스처 인덱스 사용
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);			// 1번 텍스처: 0번 텍스처 인덱스 사용

	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);		// MODULATE로 섞습니다.
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);		// 텍스처
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);		// 정점색
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);	// MODULATE2로 섞습니다.
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);		// 텍스처
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);		// 정점색
	m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(TERRAINVERTEX));
	m_pd3dDevice->SetFVF(TERRAINVERTEX::FVF);
	m_pd3dDevice->SetIndices(m_pIB);
	m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_cxDIB * m_czDIB, 0, m_nTriangles);

	return S_OK;
}

// 화면에 지형을 출력합니다.
HRESULT ZTerrain::Draw(ZFrustum * pFrustum)
{
	LPDWORD		pI;
	if (FAILED(m_pIB->Lock(0, (m_czDIB - 1) * (m_czDIB - 1) * 2 * sizeof(TRIINDEX), (void**)&pI, 0)))
	{
		return E_FAIL;
	}

	m_nTriangles = m_pQuadTree->GenerateIndex(pI, m_pvHeightMap, pFrustum, m_fLODRatio);
	m_pIB->Unlock();
	//g_pLog->Log("Triangles=%d", m_nTriangles);
	Render();

	return S_OK;
}
