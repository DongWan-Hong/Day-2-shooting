#include "pch.h"
#include "CPlayer.h"
#include "CBullet.h"

CPlayer::CPlayer() : m_pBullet(nullptr)
{
	
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize() // �÷��̾� �̴ϼȶ����� ���ͼ� �÷��̾� �ʱⰪ �Ҵ� �ϴ°�
{
	m_tInfo  = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f }; // �÷��̾��� �߽���ǥ�� ���� ���� ����
	m_fSpeed = 10.f; // �÷��̾��� �ӵ�
}

void CPlayer::Update()
{
	Key_Input();

	
	// CObj::Update_Rect();
	Update_Rect(); 

	
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
	// GetKeyState
	// GetAsyncKeyState // �Լ� ȣ�� �� ��ȯ�Ǵ� ���� ���� Ű �� ó�� ����

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
