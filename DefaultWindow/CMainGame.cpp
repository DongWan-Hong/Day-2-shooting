#include "pch.h"
#include "CMainGame.h"

CMainGame::CMainGame()
	: m_pPlayer(nullptr), m_dwTime(GetTickCount64()), m_iFPS(0)
{
	ZeroMemory(m_szFPS, sizeof(m_szFPS)); // ������API���� �����ϴ� �޸����� �Լ�

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

	dynamic_cast<CPlayer*>(m_pPlayer)->Set_Bullet(&m_BulletList);
}

void CMainGame::Update()
{
	m_pPlayer->Update(); // �÷��̾� ������Ʈ ���� ���� ��������

	for (auto& pBullet : m_BulletList)
		
		pBullet->Update();// ������ �̻��Ⱑ ������

}

void CMainGame::Render()
{
	++m_iFPS;//FPS�� ��½����ش�? ��?

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

	TCHAR		szBuf[32] = L""; // ���� �������ְ�
	// wsprintf(szBuf, L"Bullet : %d", m_BulletList.size());
	// wsprintf(szBuf, L"Bullet : %f", 3.141592f);	// �Ҽ��� �ڸ��� ����� �Ұ���
	int iBullet(0);
	iBullet = m_BulletList.size();
	swprintf_s(szBuf, L"Bullet : %d", m_BulletList.size());	// ��� ���� ���� ���� �Լ�
	TextOut(m_hDC, 50, 50, szBuf, lstrlen(szBuf)); // (DC����,��ǥ,��ǥ,�����º���,����)
	
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
