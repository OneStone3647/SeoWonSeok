#include "GlobalFunc.h"

// 2�� ������ �ϴ� ���� n�� �α� ���� ���մϴ�.
int Log2(int n)
{
	for (int i = 1; i < 64; i++)
	{
		// >> ��Ʈ������
		n = n >> 1;
		if (n == 1)
		{
			return i;
		}
	}

	return 1;
}

// 2^n���� ���մϴ�
int Pow2(int n)
{
	int val = 1;
	val = val << n;

	return val;
}

// pt�� rc �ȿ� ���ԵǴ��� �˻��մϴ�.(PtInRect()��� API�Լ��� ����(-)�� ó���� ���Ѵ�.)
BOOL IsInRect(RECT * rc, POINT pt)
{
	if ((rc->left < pt.x) && (pt.x < rc->right) &&
		(rc->bottom <= pt.y) && (pt.y <= rc->top))
	{
		return TRUE;
	}

	return FALSE;
}
