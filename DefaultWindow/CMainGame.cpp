#include "pch.h"
#include "CMainGame.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS)); // 윈도우API에서 제공하는 메모리제거 함수

}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd); // 겟디씨로 메인에 있는 GDI정보 가져와주고

	if (!m_pPlayer) // 플레이어의 값이 없다면 
	{
		m_pPlayer = new CPlayer; // 업캐스팅 동적할당 싸악 조져주고
		m_pPlayer->Initialize(); // 플레이어 이니셜라이즈 초기화 들어가주고
	}

	dynamic_cast<CPlayer*>(m_pPlayer)->Set_Bullet(&m_BulletList);
}

void CMainGame::Update()
{
	m_pPlayer->Update(); // 플레이어 업데이트 들어가서 방향 리턴하자

	for (auto& pBullet : m_BulletList)
		
		pBullet->Update();// 방향은 이색기가 조절함

}

void CMainGame::Render()
{
	++m_iFPS;//FPS를 상승시켜준다? 왜?

	if (m_dwTime + 1000 < GetTickCount64()) 
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);

		SetWindowText(g_hWnd, m_szFPS);

		m_iFPS = 0;
		m_dwTime = GetTickCount64();
	}


	Rectangle(m_hDC, 100, 0, WINCX+1000, WINCY+400);

	Rectangle(m_hDC, 200, 100, WINCX+800, WINCY+300);
	m_pPlayer->Render(m_hDC);

	for (auto& pBullet : m_BulletList)
		pBullet->Render(m_hDC);

	////////////////////////////////////////////////////

	TCHAR		szBuf[32] = L""; // 문자 선언해주고
	// wsprintf(szBuf, L"Bullet : %d", m_BulletList.size());
	// wsprintf(szBuf, L"Bullet : %f", 3.141592f);	// 소수점 자릿수 출력이 불가능
	int iBullet(0);
	iBullet = m_BulletList.size();
	swprintf_s(szBuf, L"Bullet : %d", m_BulletList.size());	// 모든 서식 문자 지원 함수
	TextOut(m_hDC, 50, 50, szBuf, lstrlen(szBuf)); // (DC변수,좌표,좌표,쓰려는변수,길이)
	
	// RECT	rcRect{ 100, 100, 200, 200 };	
	// DrawText(m_hDC, szBuf, lstrlen(szBuf), &rcRect, DT_CENTER);
	
	for (auto iter = m_BulletList.begin(); iter != m_BulletList.end();)
	{
		const INFO& tSave = (*iter)->Get_Info();

		if (tSave.fX < 200 || tSave.fX > WINCX - 200 ||
			tSave.fY < 200 || tSave.fY > WINCY - 200)
		{
			(*iter)->Release();
			iter = m_BulletList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CMainGame::Release()
{
	Safe_Delete<CObj*>(m_pPlayer);

	for_each(m_BulletList.begin(), m_BulletList.end(), Safe_Delete<CObj*>);
	m_BulletList.clear();

	ReleaseDC(g_hWnd, m_hDC);
}
