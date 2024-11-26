#include "pch.h"
#include "CBullet.h"
#include "CPlayer.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
}

void CBullet::Update()
{
	if (Check_Bul == cUp)
	{
		m_tInfo.fY -= m_fSpeed;
	}
	else if (Check_Bul == cDown)
	{
		m_tInfo.fY += m_fSpeed;
	}
	else if (Check_Bul == cRight)
	{
		m_tInfo.fX += m_fSpeed;
	}
	else if (Check_Bul == cLeft)
	{
		m_tInfo.fX -= m_fSpeed;
	}
	else if (Check_Bul == cLeft)
	{
		m_tInfo.fCY -= m_fSpeed;
	}

	__super::Update_Rect();
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}

void CBullet::Release()
{
}

void CBullet::Up_Bullet()
{
	m_tInfo.fCX = 30.f;  
	m_tInfo.fCY = 30.f;

	m_fSpeed = 20.f;
	Check_Bul = cUp;
}

void CBullet::Down_Bullet()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 20.f;
	Check_Bul = cDown;
}

void CBullet::Right_Bullet()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 20.f;
	Check_Bul = cRight;
}

void CBullet::Left_Bullet()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 20.f;
	Check_Bul = cLeft;
}

void CBullet::First_Bullet()
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;
	Check_Bul = cFirst;
}

void CBullet::Second_Bullet()
{
	
}
