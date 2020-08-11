#include "ZFLog.h"
#include "ZTerrain.h"
#include "Dib.h"

// ������
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

// �Ҹ���
ZTerrain::~ZTerrain()
{
	Destroy();
}

/*===================================================================================*
 * ���� ��ü�� �ʱ�ȭ�մϴ�.
 * pDev: ��¿� D3D����̽�
 * pvfScale: ���̸��� x, y, z ���� ���� ô�� ��(scale vector)
 * fLODRatio: LODó�� �ÿ� ���� ��
 * lpBMPFilename: ���̸ʿ� BMP���ϸ�
 * lpTexFilename: ��¿� D3D��ƺ�
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

// ���� ��ü�� �޸𸮿��� �Ұ��մϴ�.
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

// ������ü���� ����� �ؽ�ó�� �о���Դϴ�.
HRESULT ZTerrain::LoadTextures(LPCWSTR lpTexFilename[MAX_TERRAIN_TEX])
{
	for (int i = 0; i < 4; i++)
	{
		D3DXCreateTextureFromFile(m_pd3dDevice, lpTexFilename[i], &m_pTex[i]);
	}

	return S_OK;
}

// BMP������ ��� ���̸��� �����մϴ�.
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

	// m_cxDIB�� m_czDIB�� (2^n+1)�� �ƴ� ��� E_FAIL�� ��ȯ
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

// BMP������ ũ�⿡ ���缭 ����Ʈ���� �����մϴ�.
HRESULT ZTerrain::BuildQuadTree()
{
	m_pQuadTree->Build(m_pvHeightMap);

	return S_OK;
}

// ����, �ε��� ���۸� �����մϴ�.
HRESULT ZTerrain::CreateVIB()
{
	// VB����
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
	// IB ����
	if (FAILED(m_pd3dDevice->CreateIndexBuffer((m_cxDIB - 1) * (m_czDIB - 1) * 2 * sizeof(TRIINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
		Destroy();
		return E_FAIL;
	}
	g_pLog->Log("Using 16bit index buffer...");
#else
	// IB ����
	if (FAILED(m_pd3dDevice->CreateIndexBuffer((m_cxDIB - 1) * (m_czDIB - 1) * 2 * sizeof(TRIINDEX), 0, D3DFMT_INDEX32, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
		Destroy();
		return E_FAIL;
	}
	g_pLog->Log("Using 32bit index buffer...");
#endif // _USE_INDEX16

	return S_OK;
}

// ȭ�鿡 ������ ����մϴ�.
HRESULT ZTerrain::Render()
{
	m_pd3dDevice->SetTexture(0, m_pTex[0]);												// 0�� �ؽ�ó ���������� �ؽ�ó ����(�����)
	m_pd3dDevice->SetTexture(1, m_pTex[1]);												// 1�� �ؽ�ó ���������� �ؽ�ó ����(������)
	m_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 0�� �ؽ�ó ���������� Ȯ�� ����
	m_pd3dDevice->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// 1�� �ؽ�ó ���������� Ȯ�� ����
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);			// 0�� �ؽ�ó: 0�� �ؽ�ó �ε��� ���
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);			// 1�� �ؽ�ó: 0�� �ؽ�ó �ε��� ���

	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);		// MODULATE�� �����ϴ�.
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);		// �ؽ�ó
	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);		// ������
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);	// MODULATE2�� �����ϴ�.
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);		// �ؽ�ó
	m_pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);		// ������
	m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(TERRAINVERTEX));
	m_pd3dDevice->SetFVF(TERRAINVERTEX::FVF);
	m_pd3dDevice->SetIndices(m_pIB);
	m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_cxDIB * m_czDIB, 0, m_nTriangles);

	return S_OK;
}

// ȭ�鿡 ������ ����մϴ�.
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
