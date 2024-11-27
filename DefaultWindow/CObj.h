#pragma once

#include "Define.h"


class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	INFO		Get_Info() { return m_tInfo; } // ������ �߽���ǥ�� ���� ������ ���� ��ȯ
	void		Set_Pos(float _fX, float _fY) // �߽���ǥ �� �Լ�
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	RECT* Get_Rec()
	{
		return& m_tRect;
	}

	
public:
	virtual void		Initialize()PURE; // �ڽ�Ŭ�������� ���� ���������Լ� ����
	virtual void		Update()PURE; // �ڽ�Ŭ�������� ���� ���������Լ� ����
	virtual void		Render(HDC hDC)PURE; // �׸� �׸����� ��� �׷����ϴ��� �˾ƾ� �ϹǷ� �Ű��� GDI ���� �־��ֱ�
	virtual void		Release()PURE; // �ڽ�Ŭ�������� ���� ���������Լ� ����

public:
	void		Update_Rect(); // ���� ������Ʈ �Լ�
protected:
	INFO		m_tInfo; // ������ �߽ɰ��� ���� ���� ���̸� ������ ����ü
	RECT		m_tRect; // ��� ���

	float		m_fSpeed;

};

