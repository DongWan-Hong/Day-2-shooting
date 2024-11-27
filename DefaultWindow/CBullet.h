#pragma once

#include "CObj.h"

enum Check_Bullet { cUp, cDown, cRight, cLeft,cFirst,cSecond}; 

class CBullet : public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:

public:	
	virtual void Initialize()	 override;
	virtual void Update()		 override;
	virtual void Render(HDC hDC) override;
	virtual void Release()		 override;

	void Up_Bullet();
	void Down_Bullet();
	void Right_Bullet();
	void Left_Bullet();

	void First_Bullet();
	void Second_Bullet();

	Check_Bullet Check_Bul;
};

