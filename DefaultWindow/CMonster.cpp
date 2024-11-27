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
int CMonster::Shuffle() // 랜덤값
{
	srand(time(NULL));
	
	return (iRandom = rand() % 10);

}
void CMonster::Initialize() //몬스터 초기값 설정
{
	m_tInfo = { WINCX / 2.f, WINCY / 2.f, 100.f, 100.f }; // 플레이어의 중심좌표와 가로 세로 길이
	m_fSpeed = 10.f; // 플레이어의 속도
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
		m_tInfo.fX -= m_fSpeed; // 왼쪽
		
	}
	else if (_type == ob_Right)
	{
		m_tInfo.fX += m_fSpeed+1300; // 오른쪽
	}
	else
		return;
	
}


