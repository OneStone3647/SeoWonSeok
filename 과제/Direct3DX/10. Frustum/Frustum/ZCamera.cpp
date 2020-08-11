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
 * ī�޶� ����� �����ϱ� ���� �⺻ ���Ͱ����� �����մϴ�.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::SetView(D3DXVECTOR3 * pvEye, D3DXVECTOR3 * pvLookat, D3DXVECTOR3 * pvUp)
{
	m_vEye = *pvEye;
	m_vLookat = *pvLookat;
	m_vUp = *pvUp;

	/*-----------------------------------------------------------------------------*
	 * �ٶ󺸴� ������ ���͸� ����ȭ�մϴ�.
	 *
	 * D3DXVECTOR3 *WINAPI D3DXVec3Normalize(
	 * D3DXVECTOR3 *pOut,
	 * CONST D3DXVECTOR3 *pV
	 * );
	 * 3D ������ ����ȭ�� ���͸� �����ݴϴ�.
	 * pOut: ���� ����� D3DXVECTOR3 ����ü�� ������
	 * pV: ����ȭ�� D3DVECTOR3 ����ü�� ������
	 *-----------------------------------------------------------------------------*/
	D3DXVec3Normalize(&m_vView, &(m_vLookat - m_vEye));

	/*-----------------------------------------------------------------------------*
	 * �� ������ ����(���� ����)�� ���մϴ�.
	 *
	 * D3DXVECTOR3 *D3DXVec3Cross(
	 * D3DXVECTOR3 *pOut,
	 * CONST D3DXVECTOR3 *pV1,
	 * CONST D3DXVECTOR3 *pV2
	 * );
	 * 3���� 3D ������ ������ ����մϴ�.
	 * pOut: ���� ����� D3DXVECTOR3 ����ü�� ������
	 * pV1, pV2: ������ ���� D3DVECTOR3 ����ü�� �����͵�
	 *-----------------------------------------------------------------------------*/
	D3DXVec3Cross(&m_vCross, &m_vUp, &m_vView);

	// �޼� ��ǥ�� �� ����� �����մϴ�.
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookat, &m_vUp);
	// ����� ������� ���մϴ�.
	D3DXMatrixInverse(&m_matBill, NULL, &m_matView);
	m_matBill._41 = 0.0f;
	m_matBill._42 = 0.0f;
	m_matBill._43 = 0.0f;

	return &m_matView;
}

/*===================================================================================*
 * ī�޶� ��ǥ���� X������ angle��Ů ȸ���մϴ�.
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
	 * (x, y, z, 1) ���Ϳ� 4x4����� ���Ͽ� (x, y, z)���͸� ���մϴ�.
	 * pOut: ���� ����� D3DXVECTOR3 ����ü�� ������
	 * pV: ó���� �⺻�� �Ǵ� D3DVECTOR3 ����ü�� ������
	 * pM: ó���� �⺻�� �Ǵ� D3DXMATRIX ����ü�� ������
	 *-----------------------------------------------------------------------------*/
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);	// view * rot�� ���ο� dst vector�� ���մϴ�.
	//D3DXVec3Cross(&vNewUp, &vNewDst, &m_vCross);			// cross( dst, x�� )���� up vector�� ���մϴ�.
	//D3DXVec3Normalize(&vNewUp, &vNewUp);					// up vector�� uint vector�� ��ȯ�մϴ�.
	vNewDst += m_vEye;													// ���� dst position = eye position + dst vector

	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

/*===================================================================================*
 * ī�޶� ��ǥ���� Y������ angle��ŭ ȸ���մϴ�.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::RotateLocalY(float angle)
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vUp, angle);

	D3DXVECTOR3 vNewDst;
	D3DXVec3TransformCoord(&vNewDst, &m_vView, &matRot);	// view * rot�� ���ο� dst vector�� ���մϴ�.
	vNewDst += m_vEye;													// ���� dst position = eye position + dst vector


	return SetView(&m_vEye, &vNewDst, &m_vUp);
}

/*===================================================================================*
 * ī�޶� ��ǥ���� Z������ angle��ŭ ȸ���մϴ�.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::RotateLocalZ(float angle)
{
	m_Angle += angle;

	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationAxis(&matRot, &m_vView, angle);

	D3DXVECTOR3 vNewUp;
	D3DXVec3TransformCoord(&vNewUp, &m_vUp, &matRot);	// view * rot�� ���ο� dst vector�� ���մϴ�.

	return SetView(&m_vEye, &m_vLookat, &vNewUp);
}

/*===================================================================================*
 * ������ǥ���� *pv���� ��ġ�� ī�޶� �̵��մϴ�.
 *===================================================================================*/
D3DXMATRIXA16 * ZCamera::MoveTo(D3DXVECTOR3 * pv)
{
	D3DXVECTOR3 dv = *pv - m_vEye;
	m_vEye = *pv;
	m_vLookat += dv;

	return SetView(&m_vEye, &m_vLookat, &m_vUp);
}

/*===================================================================================*
 * ī�޶� ��ǥ���� X�� �������� dist��ŭ �����մϴ�.(������ -dist�� ������ �˴ϴ�.)
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
 * ī�޶� ��ǥ���� Y�� �������� dist��ŭ �����մϴ�.(������ -dist�� ������ �˴ϴ�.)
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
 * ī�޶� ��ǥ���� Z�� �������� dist��ŭ �����մϴ�.(������ -dist�� ������ �˴ϴ�.)
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
