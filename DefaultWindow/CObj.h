#pragma once

#include "Define.h"


class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	INFO		Get_Info() { return m_tInfo; } // 도형의 중심좌표와 가로 세로의 길이 반환
	void		Set_Pos(float _fX, float _fY) // 중심좌표 셋 함수
	{
		m_tInfo.fX = _fX;
		m_tInfo.fY = _fY;
	}
	RECT* Get_Rec()
	{
		return& m_tRect;
	}

	
public:
	virtual void		Initialize()PURE; // 자식클래스들을 위한 순수가상함수 선언
	virtual void		Update()PURE; // 자식클래스들을 위한 순수가상함수 선언
	virtual void		Render(HDC hDC)PURE; // 그림 그리려면 어디에 그려야하는지 알아야 하므로 매개로 GDI 정보 넣어주기
	virtual void		Release()PURE; // 자식클래스들을 위한 순수가상함수 선언

public:
	void		Update_Rect(); // 도형 업데이트 함수
protected:
	INFO		m_tInfo; // 도형의 중심값과 가로 세로 길이를 저장할 구조체
	RECT		m_tRect; // 잠시 대기

	float		m_fSpeed;

};

