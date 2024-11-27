#include "pch.h"
#include "CMonster.h"


CMonster::CMonster()
{
	iRandom = 0;
	iCheck = 1;
	
}
CMonster::~CMonster()
{
	Release();
}
int CMonster::Shuffle() // ������
{
	srand(time(NULL));
	
	return (iRandom = rand() % 10);

}
void CMonster::Initialize() //���� �ʱⰪ ����
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f }; // �÷��̾��� �߽���ǥ�� ���� ���� ����
	m_fSpeed = 10.f; // �÷��̾��� �ӵ�
}
void CMonster::Update()
{
	Update_Rect();
}

void CMonster::Render(HDC hDC)
{

	Rectangle(hDC,
		m_tRect.left,
		m_tRect.top,
		m_tRect.right,
		m_tRect.bottom);
}
void CMonster::Release()
{


}

void CMonster::Moving(Check_INFO _type)
{
		
	if (_type == ob_Left)
	{
		m_tInfo.fX -= m_fSpeed; // ����
		
	}
	else if (_type == ob_Right)
	{
		m_tInfo.fX += m_fSpeed+1300; // ������
	}
	else
		return;
	
}


