#pragma once
#include "CObj.h"

enum Bullet_Direction{Up,Down,Right,Left,first,second};

class CPlayer :    public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    void        Set_Bullet(list<CObj*>* pBullet) { m_pBullet = pBullet; }
 
public:
    void Initialize() override;
    void Update();
    void Render(HDC hDC) override;
    void Release() override;

private:
    void     Key_Input();
    CObj* Create_Bullet();

private:
    list<CObj*>*        m_pBullet;
    unsigned long long m_ullLast_Fire;
    Bullet_Direction Bullet_Di;
};

