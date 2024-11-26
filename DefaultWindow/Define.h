#pragma once

#define WINCX		800 // ����
#define WINCY		600 // ����

#define	PURE		= 0 // ���������Լ�
#define PI			3.141592f // ������

extern HWND		g_hWnd; // ����CPP�� �ִ� GDI������ ���� ���� �ͽ��� ����

typedef struct tagInfo // ��ġ���� ������ ���� ����ü ����
{
	float		fX, fY;  //��ü�� �߽� ��ǥ
	float		fCX, fCY;	// ����, ���� ����

}INFO;


template<typename T> // �޸������Լ�
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}