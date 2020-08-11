#ifndef _ZTERRAIN_H_
#define _ZTEERAIN_H_

#include "define.h"
#include "ZQuadTree.h"
#define MAX_TERRAIN_TEX 4

/*===================================================================================*
 * 지형 관리 클래스
 *===================================================================================*/
class ZTerrain
{
private:
	int										m_cxDIB;								// DIB의 가로 픽셀 수
	int										m_czDIB;								// DIB의 세로 픽셀 수
	int										m_cyDIB;								// DIB의 최대 높이 값(즉 0 ~ 255 사이의 값)
	D3DXVECTOR3						m_vfScale;							// x scale, y scale, z scale
	TERRAINVERTEX*					m_pvHeightMap;					// 높이맵의 정점 배열
	LPDIRECT3DDEVICE9				m_pd3dDevice;						// 출력용 D3D디바이스
	LPDIRECT3DTEXTURE9				m_pTex[MAX_TERRAIN_TEX];		// 텍스처
	LPDIRECT3DVERTEXBUFFER9		m_pVB;								// 지형 출력용 정점 버퍼
	LPDIRECT3DINDEXBUFFER9		m_pIB;								// 지형 출력용 인덱스 버퍼
	int										m_nTriangles;						// 출력할 삼각형의 개수
	ZQuadTree*							m_pQuadTree;						// 쿼드 트리 객체의 포인터

public:
	// 생성과 관련된 함수들
	ZTerrain();
	~ZTerrain();

public:
	// 생성과 관련된 함수들
	/*===================================================================================*
	 * 지형 객체를 초기화합니다.
	 * pDev: 출력용 D3D디바이스
	 * pvfScale: 높이맵의 x, y, z 값에 곱할 척도 값(scale vector)
	 * lpBMPFilename: 높이맵용 BMP파일명
	 * lpTexFilename: 출력용 D3D디아비스
	 *===================================================================================*/
	HRESULT Create(LPDIRECT3DDEVICE9 pDev, D3DXVECTOR3* pvfScale, const char* lpBmpFilename, LPCWSTR lpTexFilename[MAX_TERRAIN_TEX]);

private:
	// ZTerrain 내부에서 사용되는 함수들

	// 지형 객체를 메모리에서 소거합니다.
	HRESULT	Destroy();

	// 지형객체에서 사용할 텍스처를 읽어들입니다.
	HRESULT LoadTextures(LPCWSTR lpTexFilename[MAX_TERRAIN_TEX]);

	// BMP파일을 열어서 높이맵을 생성합니다.
	HRESULT BuildHeightMap(const char* lpFilename);

	// BMP파일의 크기에 맞춰서 쿼드트리를 생성합니다.
	HRESULT BuildQuadTree();

	// 정점, 인덱스 버퍼를 생성합니다.
	HRESULT CreateVIB();

	// 화면에 지형을 출력합니다.
	HRESULT Render();

public:
	// x, z 위치의 정점 값을 얻습니다.
	TERRAINVERTEX* GetVertex(int x, int z)
	{
		return (m_pvHeightMap + x + z * m_cxDIB);
	}

	// x, z 위치의 높이(y) 값만 얻습니다.
	float			GetHeight(int x, int z)
	{
		return (GetVertex(x, z))->p.y;
	}

	// 높이맵 BMp파일의 가로 픽셀 수
	int				GetCXDIB()
	{
		return m_cxDIB;
	}

	// 높이맵 BMP파일의 세로 픽셀 수
	int				GetCZDIB()
	{
		return m_czDIB;
	}

	// 높이맵의 실제 x축 폭(column) 값
	float			GetCXTerrain()
	{
		return m_cxDIB * m_vfScale.x;
	}

	// 높이맵의 실제 y축 높이(height) 값
	float			GetCVTerrain()
	{
		return m_cyDIB * m_vfScale.y;
	}

	// 높이맵의 실제 z축 길이(row) 값
	float			GetCZTerrainm()
	{
		return m_czDIB * m_vfScale.z;
	}

	// 화면에 지형을 출력합니다.
	HRESULT			Draw();
};

#endif // !_ZTERRAIN_H_
