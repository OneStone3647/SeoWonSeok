#ifndef _ZTERRAIN_H_
#define _ZTEERAIN_H_

#include "define.h"
#include "ZQuadTree.h"
#define MAX_TERRAIN_TEX 4

/*===================================================================================*
 * ���� ���� Ŭ����
 *===================================================================================*/
class ZTerrain
{
private:
	int										m_cxDIB;								// DIB�� ���� �ȼ� ��
	int										m_czDIB;								// DIB�� ���� �ȼ� ��
	int										m_cyDIB;								// DIB�� �ִ� ���� ��(�� 0 ~ 255 ������ ��)
	D3DXVECTOR3						m_vfScale;							// x scale, y scale, z scale
	TERRAINVERTEX*					m_pvHeightMap;					// ���̸��� ���� �迭
	LPDIRECT3DDEVICE9				m_pd3dDevice;						// ��¿� D3D����̽�
	LPDIRECT3DTEXTURE9				m_pTex[MAX_TERRAIN_TEX];		// �ؽ�ó
	LPDIRECT3DVERTEXBUFFER9		m_pVB;								// ���� ��¿� ���� ����
	LPDIRECT3DINDEXBUFFER9		m_pIB;								// ���� ��¿� �ε��� ����
	int										m_nTriangles;						// ����� �ﰢ���� ����
	ZQuadTree*							m_pQuadTree;						// ���� Ʈ�� ��ü�� ������

public:
	// ������ ���õ� �Լ���
	ZTerrain();
	~ZTerrain();

public:
	// ������ ���õ� �Լ���
	/*===================================================================================*
	 * ���� ��ü�� �ʱ�ȭ�մϴ�.
	 * pDev: ��¿� D3D����̽�
	 * pvfScale: ���̸��� x, y, z ���� ���� ô�� ��(scale vector)
	 * lpBMPFilename: ���̸ʿ� BMP���ϸ�
	 * lpTexFilename: ��¿� D3D��ƺ�
	 *===================================================================================*/
	HRESULT Create(LPDIRECT3DDEVICE9 pDev, D3DXVECTOR3* pvfScale, const char* lpBmpFilename, LPCWSTR lpTexFilename[MAX_TERRAIN_TEX]);

private:
	// ZTerrain ���ο��� ���Ǵ� �Լ���

	// ���� ��ü�� �޸𸮿��� �Ұ��մϴ�.
	HRESULT	Destroy();

	// ������ü���� ����� �ؽ�ó�� �о���Դϴ�.
	HRESULT LoadTextures(LPCWSTR lpTexFilename[MAX_TERRAIN_TEX]);

	// BMP������ ��� ���̸��� �����մϴ�.
	HRESULT BuildHeightMap(const char* lpFilename);

	// BMP������ ũ�⿡ ���缭 ����Ʈ���� �����մϴ�.
	HRESULT BuildQuadTree();

	// ����, �ε��� ���۸� �����մϴ�.
	HRESULT CreateVIB();

	// ȭ�鿡 ������ ����մϴ�.
	HRESULT Render();

public:
	// x, z ��ġ�� ���� ���� ����ϴ�.
	TERRAINVERTEX* GetVertex(int x, int z)
	{
		return (m_pvHeightMap + x + z * m_cxDIB);
	}

	// x, z ��ġ�� ����(y) ���� ����ϴ�.
	float			GetHeight(int x, int z)
	{
		return (GetVertex(x, z))->p.y;
	}

	// ���̸� BMp������ ���� �ȼ� ��
	int				GetCXDIB()
	{
		return m_cxDIB;
	}

	// ���̸� BMP������ ���� �ȼ� ��
	int				GetCZDIB()
	{
		return m_czDIB;
	}

	// ���̸��� ���� x�� ��(column) ��
	float			GetCXTerrain()
	{
		return m_cxDIB * m_vfScale.x;
	}

	// ���̸��� ���� y�� ����(height) ��
	float			GetCVTerrain()
	{
		return m_cyDIB * m_vfScale.y;
	}

	// ���̸��� ���� z�� ����(row) ��
	float			GetCZTerrainm()
	{
		return m_czDIB * m_vfScale.z;
	}

	// ȭ�鿡 ������ ����մϴ�.
	HRESULT			Draw();
};

#endif // !_ZTERRAIN_H_
