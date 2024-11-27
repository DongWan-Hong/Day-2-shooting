#include "pch.h"
#include "CMainGame.h"



CMainGame::CMainGame()
    : m_pPlayer(nullptr), m_pMonster(nullptr), m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS)); // ������API���� �����ϴ� �޸����� �Լ�
    m_hDC = nullptr;
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd); // �ٵ𾾷� ���ο� �ִ� GDI���� �������ְ�

	if (!m_pPlayer) // �÷��̾��� ���� ���ٸ� 
	{
		m_pPlayer = new CPlayer; // ��ĳ���� �����Ҵ� �ξ� �����ְ�
		m_pPlayer->Initialize(); // �÷��̾� �̴ϼȶ����� �ʱ�ȭ ���ְ�
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
	m_pPlayer->Update(); // Ű �Է� �� �Ѿ� �߻�

	for (auto& pBullet : m_BulletList)
		
		pBullet->Update();// �Ѿ� ������ �̻��Ⱑ ������

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

    Rectangle(m_hDC, 100, 0, WINCX + 1000, WINCY + 400); // ūƲ
    Rectangle(m_hDC, 200, 100, WINCX + 800, WINCY + 300); // ����Ʋ

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
            ++iter; //�������
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
                ++iter; //�������
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


// 1. W, A, S, D Ű�� ���� ��� �� ������ ���ϴ� �̻��� �߻��ϱ�
// 2. ��ü ȭ�麸�� ���� 100, ���� 100 ���� �簢���� �׸��� �� ������ ��� �̻��� �Ҹ��Ű��
// 3. ���� �簢�� �ȿ��� �·� �Ǵ� ��� ���ϴ� ���͸� �����ϱ�
// 4. �߻��� �Ѿ˰� ���Ͱ� �浹�� ��� �����ض�

// BOOL IntersectRect(�浹�� ��Ʈ�� ���� �߻��� ��Ʈ�� ������ ������ �ּ�, ��Ʈ �ּ�1, ��Ʈ �ּ�2)

