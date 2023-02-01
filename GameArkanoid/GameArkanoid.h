
// GameArkanoid.h: основной файл заголовка для приложения GameArkanoid
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CGameArkanoidApp:
// Сведения о реализации этого класса: GameArkanoid.cpp
//

class CGameArkanoidApp : public CWinApp
{
public:
	CGameArkanoidApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGameArkanoidApp theApp;
