#pragma once

#define WINCX		800 // 가로
#define WINCY		600 // 세로

#define	PURE		= 0 // 순수가상함수
#define PI			3.141592f // 원주율

extern HWND		g_hWnd; // 메인CPP에 있는 GDI정보를 쓰기 위한 익스턴 선언

typedef struct tagInfo // 위치정보 저장을 위한 구조체 선언
{
	float		fX, fY;  //객체의 중심 좌표
	float		fCX, fCY;	// 가로, 세로 길이

}INFO;


template<typename T> // 메모리해제함수
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}