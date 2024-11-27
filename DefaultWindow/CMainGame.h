#pragma once

#include "Define.h"
#include "CPlayer.h"
#include "CMonster.h"

class CMainGame
{


public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Render();
	void		Release();

private:

	HDC			m_hDC; // ȭ�� ����ϴ� ���� 

	CObj*		m_pPlayer; // ���� ������ �÷��̾�
	CObj* m_pMonster; // ���� ������ �÷��̾�
	list<CObj*>	m_BulletList; // �Ѿ� ������ ����

	DWORD		m_dwTime; // ��ƽī���� ������ ����
	int			m_iFPS;  // FPS ǥ�ÿ�
	TCHAR		m_szFPS[16]; // ������ â�� ��� ���ڿ�



};

// 1. W, A, S, D Ű�� ���� ��� �� ������ ���ϴ� �̻��� �߻��ϱ�
// 2. ��ü ȭ�麸�� ���� 100, ���� 100 ���� �簢���� �׸��� �� ������ ��� �̻��� �Ҹ��Ű��
// 3. ���� �簢�� �ȿ��� �·� �Ǵ� ��� ���ϴ� ���͸� �����ϱ�
// 4. �߻��� �Ѿ˰� ���Ͱ� �浹�� ��� �����ض�

// BOOL IntersectRect(�浹�� ��Ʈ�� ���� �߻��� ��Ʈ�� ������ ������ �ּ�, ��Ʈ �ּ�1, ��Ʈ �ּ�2)