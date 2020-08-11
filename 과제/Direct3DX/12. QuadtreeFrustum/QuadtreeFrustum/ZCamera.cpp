#include "ZCamera.h"



ZCamera::ZCamera()
{
	D3DXVECTOR3 eye(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 lookat(0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matBill);
	SetView(&eye, &lookat, &up);
}


ZCamera::~ZCamera()
{
}

/*===================================================================================*
 * 카메라 행렬을 생성하기 위한 기본 벡터값들을 설정합니다.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::SetView(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvLookat, D3DXVECTOR3 * pvUp)
{
	m_vEye = *pvEye;
	m_vLookat = *pvLookat;
	m_vUp = *pvUp;

	/*-----------------------------------------------------------------------------*
	 * 바라보는 방향의 벡터를 정규화합니다.
	 *
	 * D3DXVECTOR3 *WINAPI D3DXVec3Normalize(
	 * D3DXVECTOR3 *pOut,
	 * CONST D3DXVECTOR3 *pV
	 * );
	 * 3D 벡터의 정규화한 벡터를 돌려줍니다.
	 * pOut: 연산 결과인 D3DXVECTOR3 구조체의 포인터
	 * pV: 정규화할 D3DVECTOR3 구조체의 포인터
	 *-----------------------------------------------------------------------------*/
	D3DXVec3Normalize(&m_vView, &(m_vLookat - m_vEye));

	/*-----------------------------------------------------------------------------*
	 * 두 벡터의 외적(법선 벡터)을 구합니다.
	 *
	 * D3DXVECTOR3 *D3DXVec3Cross(
	 * D3DXVECTOR3 *pOut,
	 * CONST D3DXVECTOR3 *pV1,
	 * CONST D3DXVECTOR3 *pV2
	 * );
	 * 3개의 3D 벡터의 외적을 계산합니다.
	 * pOut: 연산 결과인 D3DXVECTOR3 구조체의 포인터
	 * pV1, pV2: 외적을 구할 D3DVECTOR3 구조체의 포인터들
	 *-----------------------------------------------------------------------------*/
	D3DXVec3Cross(&m_vCross, &m_vUp, &m_vView);

	// 왼손 좌표계 뷰 행렬을 생성합니다.
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookat, &m_vUp);
	// 행렬의 역행렬을 구합니다.
	D3DXMatrixInverse(&m_matBill, NULL, &m_matView);
	m_matBill._41 = 0.0f;
	m_matBill._42 = 0.0f;
	m_matBill._43 = 0.0f;

	return &m_matView;
}

/*===================================================================================*
 * 카메라 좌표계의 X축으로 angle만큽 회전합니다.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::RotateLocalX(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vCross, angle);

	D3DXVECTOR3 vNewDst;
	D3DXVECTOR3 vNewUp;
	/*-----------------------------------------------------------------------------*
	 * D3DXVECTOR3 *WINAPI D3DXVec3TransformCoord(
	 * D3DXVECTOR3 *pOut,
	 * CONST D3DXVECTOR3 *pV,
	 * CONST D3DXMATRIX *pM
	 * );
	 * (x, y, z, 1) 벡터와 4x4행렬을 곱하여 (x, y, z)벡터를 구합니다.
	 * pOut: 연산 결과인 D3DXVECTOR3 구조체의 포인터
	 * pV: 처리의 기본이 되는 D3DVECTOR3 구조체의 포인터
	 * pM: 처리의 기본이 되는 D3DXMATRIX 구조체의 포인터
	 *-----------------------------------------------------------------------------*/
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);	// view * rot로 새로운 dst vector를 구합니다.
	//D3DXVec3Cross(&vNewUp, &vNewDst, &m_vCross);			// cross( dst, x축 )으로 up vector를 구합니다.
	//D3DXVec3Normalize(&vNewUp, &vNewUp);					// up vector를 uint vector로 변환합니다.
	vNewDst += m_vEye;													// 실제 dst position = eye position + dst vector

	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

/*===================================================================================*
 * 카메라 좌표계의 Y축으로 angle만큼 회전합니다.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::RotateLocalY(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vUp, angle);

	D3DXVECTOR3 vNewDst;
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);	// view * rot로 새로운 dst vector를 구합니다.
	vNewDst += m_vEye;													// 실제 dst position = eye position + dst vector


	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

/*===================================================================================*
 * 카메라 좌표계의 Z축으로 angle만큼 회전합니다.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::RotateLocalZ(float angle)
{
	m_Angle += angle;

	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vView, angle);

	D3DXVECTOR3 vNewUp;
	D3DXVec3TransformCoord(&vNewUp, &m_vUp, &matRot);	// view * rot로 새로운 dst vector를 구합니다.

	return SetView(&m_vEye, &m_vLookat, &vNewUp);
}

/*===================================================================================*
 * 월드좌표계의 *pv값의 위치로 카메라를 이동합니다.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::MoveTo(D3DXVECTOR3 * pv)
{
	D3DXVECTOR3 dv = *pv - m_vEye;
	m_vEye = *pv;
	m_vLookat += dv;

	return SetView(&m_vEye, &m_vLookat, &m_vUp);
}

/*===================================================================================*
 * 카메라 좌표계의 X축 방향으로 dist만큼 전진합니다.(후진은 -dist를 넣으면 됩니다.)
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::MoveLocalX(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vCross);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}

/*===================================================================================*
 * 카메라 좌표계의 Y축 방향으로 dist만큼 전진합니다.(후진은 -dist를 넣으면 됩니다.)
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::MoveLocalY(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vUp);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}

/*===================================================================================*
 * 카메라 좌표계의 Z축 방향으로 dist만큼 전진합니다.(후진은 -dist를 넣으면 됩니다.)
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::MoveLocalZ(float dist)
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookat;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize(&vMove, &m_vView);
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView(&vNewEye, &vNewDst, &m_vUp);
}
