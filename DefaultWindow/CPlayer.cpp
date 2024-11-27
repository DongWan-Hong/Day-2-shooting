#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"

CPlayer::CPlayer() : m_pBullet(nullptr)
{
	ZeroMemory(&Bullet_Di, sizeof(Bullet_Di));
	m_ullLast_Fire = 0;

}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize() // 플레이어 이니셜라이즈 들어와서 플레이어 초기값 할당 하는곳
{
	m_tInfo  = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f }; // 플레이어의 중심좌표와 가로 세로 길이
	m_fSpeed = 10.f; // 플레이어의 속도
}
void CPlayer::Update()
{
	Update_Rect();
	Key_Input();
	// CObj::Update_Rect();
	
}
void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, 
		m_tRect.left, 
		m_tRect.top, 
		m_tRect.right, 
		m_tRect.bottom);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{

	if (m_ullLast_Fire + 100 > GetTickCount64())
	{
		return;
	}
	// GetKeyState
	// GetAsyncKeyState // 함수 호출 시 반환되는 값에 따른 키 값 처리 가능

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		Bullet_Di = Right;
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;  
		Bullet_Di = Left;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		Bullet_Di = Up;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		Bullet_Di = Down;
	}

	if (GetAsyncKeyState(VK_F1))
	{	
		Bullet_Di = first;
	}

	
	if (GetAsyncKeyState(VK_SPACE))
	{	
		
		m_ullLast_Fire = GetTickCount64();
		m_pBullet->push_back(Create_Bullet());
	}

}

CObj* CPlayer::Create_Bullet()
{
	CObj* pBullet = new CBullet;

	if (Bullet_Di == Up)
	{
		static_cast<CBullet*>(pBullet)->Up_Bullet();
	}

	else if (Bullet_Di == Down)
	{
		static_cast<CBullet*>(pBullet)->Down_Bullet();
	}
	else if (Bullet_Di == Right)
	{
		static_cast<CBullet*>(pBullet)->Right_Bullet();
	}
	else if (Bullet_Di == Left)
	{
		static_cast<CBullet*>(pBullet)->Left_Bullet();
	}
	else if (Bullet_Di == first)
	{
		static_cast<CBullet*>(pBullet)->First_Bullet();
	}
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);

	return pBullet;
}
