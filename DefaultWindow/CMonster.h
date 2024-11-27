#pragma once

#include "CObj.h"

enum Check_INFO{ob_Right=1,ob_Left};

class CMonster : public CObj
{
public:
    CMonster();
    virtual ~CMonster();

public:

    int Shuffle();

public:
    void Initialize() override;
    void Update();
    void Render(HDC hDC) override;
    void Release() override;

    void Moving(Check_INFO _type);

    Check_INFO Get_Ob_Check() const
    {
        return m_Check_INFO;
    }

private:
    int iCheck;
    int iRandom;

    Check_INFO m_Check_INFO;

};

