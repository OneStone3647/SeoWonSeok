#ifndef _ZCAMERA_H_
#define _ZCAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>

/*=============================================================================*
 * ī�޶� ���� Ŭ����
 *=============================================================================*/
class ZCamera
{
private:
	D3DXVECTOR3		m_vEye;			// ī�޶��� ���� ��ġ
	D3DXVECTOR3		m_vLookat;		// ī�޶��� �ü� ��ġ
	D3DXVECTOR3		m_vUp;			// ī�޶��� ��溤��

	D3DXVECTOR3		m_vView;		// ī�޶� ���ϴ� �������⺤��
	D3DXVECTOR3		m_vCross;		// ī�޶��� ���� ���� cross( view, up )

	D3DXMATRIXA16	m_matView;		// ī�޶� ���
	D3DXMATRIXA16	m_matBill;		// ������ ���(ī�޶��� �����)
			
public:
	ZCamera();
	~ZCamera();

public:
	// ī�޶��� ����� ����ϴ�.
	D3DXMATRIXA16*	GetViewMatrix()
	{
		return &m_matView;
	}

	// ������ ����� ����ϴ�.
	D3DXMATRIXA16*	GetBillMatrix()
	{
		return &m_matBill;
	}

	// ī�޶��� ��ġ���� ����ϴ�.
	D3DXVECTOR3*	GetEye()
	{
		return &m_vEye;
	}
	// ī�޶��� ��ġ���� �����մϴ�.
	void			SetEye(D3DXVECTOR3* pv)
	{
		m_vEye = *pv;
	}

	// ī�޶��� �ü����� ����ϴ�.
	D3DXVECTOR3*	GetLookat()
	{
		return &m_vLookat;
	}
	// ī�޶��� �ü����� �����մϴ�.
	void			SetLookat(D3DXVECTOR3* pv)
	{
		m_vLookat = *pv;
	}

	// ī�޶��� ��溤�Ͱ��� ����ϴ�.
	D3DXVECTOR3*	GetUp()
	{
		return &m_vUp;
	}
	// ī�޶��� ��溤�Ͱ��� �����մϴ�.
	void			SetUp(D3DXVECTOR3* pv)
	{
		m_vUp = *pv;
	}

	// ���� �����մϴ�.
	void			Flush()
	{
		SetView(&m_vEye, &m_vLookat, &m_vUp);
	}

public:
	// ī�޶� ����� �����ϱ� ���� �⺻ ���Ͱ����� �����մϴ�.
	D3DXMATRIXA16* SetView(D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp);

	// ī�޶� ��ǥ���� X������ angle��ŭ ȸ���մϴ�.
	D3DXMATRIXA16* RotateLocalX(float angle);

	// ī�޶� ��ǥ���� Y������ angle��ŭ ȸ���մϴ�.
	D3DXMATRIXA16* RotateLocalY(float angle);

	// ī�޶� ��ǥ���� Z������ angle��ŭ ȸ���մϴ�.
	D3DXMATRIXA16* RotateLocalZ(float angle);

	// ���� ��ǥ���� *pv���� ��ġ�� �̵��մϴ�.
	D3DXMATRIXA16* MoveTo(D3DXVECTOR3* pv);

	// ī�޶� ��ǥ���� X�� �������� dist��Ů �����մϴ�.(������ -dist�� ������ �˴ϴ�.)
	D3DXMATRIXA16* MoveLocalX(float dist);

	// ī�޶� ��ǥ���� Y�� �������� dist��ŭ �����մϴ�.(������ -dist�� ������ �˴ϴ�.)
	D3DXMATRIXA16* MoveLocalY(float dist);

	// ī�޶� ��ǥ���� Z�� �������� dist��ŭ �����մϴ�.(������ -dist�� ������ �˴ϴ�.)
	D3DXMATRIXA16* MoveLocalZ(float dist);
};

#endif	// _ZCAMERA_H_

