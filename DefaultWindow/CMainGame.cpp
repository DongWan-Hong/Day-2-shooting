#include "pch.h"
#include "CMainGame.h"



CMainGame::CMainGame()
    : m_pPlayer(nullptr), m_pMonster(nullptr), m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS)); // 윈도우API에서 제공하는 메모리제거 함수
    m_hDC = nullptr;
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
    if (!m_pMonster)
    {
        m_pMonster = new CMonster;
        m_pMonster->Initialize();
   }
   
	dynamic_cast<CPlayer*>(m_pPlayer)->Set_Bullet(&m_BulletList);
}

void CMainGame::Update()
{
	m_pPlayer->Update(); // 키 입력 및 총알 발사

	for (auto& pBullet : m_BulletList)
		
		pBullet->Update();// 총알 방향은 이색기가 조절함

    if (!m_pMonster)
    {
        return;
    }
    m_pMonster->Update();

  
}

void CMainGame::Render()
{
    ++m_iFPS;

    if (m_dwTime + 1000 < GetTickCount64())
    {
        swprintf_s(m_szFPS, L"FPS : %d", m_iFPS);
        SetWindowText(g_hWnd, m_szFPS);
        m_iFPS = 0;
        m_dwTime = GetTickCount64();
    }

    Rectangle(m_hDC, 100, 0, WINCX + 1000, WINCY + 400); // 큰틀
    Rectangle(m_hDC, 200, 100, WINCX + 800, WINCY + 300); // 작은틀

    m_pPlayer->Render(m_hDC); // 
    if (m_pMonster)
    {
        m_pMonster->Render(m_hDC);
    }
   
  
    for (auto& pBullet : m_BulletList)
        pBullet->Render(m_hDC);

    TCHAR szBuf[32] = L"";
    int iBullet = m_BulletList.size();
    swprintf_s(szBuf, L"Bullet : %d", iBullet);
    TextOut(m_hDC, 50, 50, szBuf, lstrlen(szBuf));

    for (auto iter = m_BulletList.begin(); iter != m_BulletList.end();)
    {
        const INFO& tInfo = (*iter)->Get_Info();

      
        if (tInfo.fX < 200 || tInfo.fX > WINCX + 800 ||
            tInfo.fY < 100 || tInfo.fY > WINCY + 300)
        {
            (*iter)->Release();
            iter = m_BulletList.erase(iter); 
        }
        else
        {
            ++iter; //계속증가
        }
    }

    if (m_pMonster)
    {
        for (auto iter = m_BulletList.begin(); iter != m_BulletList.end();)
        {
            RECT asd;
            RECT* pBullet = (*iter)->Get_Rec();
            RECT* pMonster = m_pMonster->Get_Rec();

            if (IntersectRect(&asd, pBullet, pMonster))
            {
                Safe_Delete(*iter);
                iter = m_BulletList.erase(iter);
                Safe_Delete(m_pMonster);
                break;
            }
            else
            {
                ++iter; //계속증가
            }
        }
    }

    if (m_pMonster)
    {
        static_cast<CMonster*>(m_pMonster)->Moving(ob_Left);

        if (m_pMonster->Get_Info().fX < 200) // 
        {

            static_cast<CMonster*>(m_pMonster)->Moving(ob_Right);
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


// 1. W, A, S, D 키를 누를 경우 각 방향을 향하는 미사일 발사하기
// 2. 전체 화면보다 가로 100, 세로 100 작은 사각형을 그리고 그 범위를 벗어난 미사일 소멸시키기
// 3. 작은 사각형 안에서 좌로 또는 우로 향하는 몬스터를 구현하기
// 4. 발사한 총알과 몬스터가 충돌할 경우 삭제해라

// BOOL IntersectRect(충돌한 렉트에 의해 발생한 렉트의 정보를 저장할 주소, 렉트 주소1, 렉트 주소2)

