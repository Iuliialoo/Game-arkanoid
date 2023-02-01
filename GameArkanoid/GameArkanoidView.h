
// GameArkanoidView.h: интерфейс класса CGameArkanoidView
//

#pragma once
#include "StatusGame.h"


class CGameArkanoidView : public CView
{
protected: // создать только из сериализации
	CGameArkanoidView() noexcept;
	DECLARE_DYNCREATE(CGameArkanoidView)

// Атрибуты
public:
	CGameArkanoidDoc* GetDocument() const;


// Операции
public:
	void createLevel(int, int);
	void checkBreakBlock();

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CGameArkanoidView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // версия отладки в GameArkanoidView.cpp
inline CGameArkanoidDoc* CGameArkanoidView::GetDocument() const
   { return reinterpret_cast<CGameArkanoidDoc*>(m_pDocument); }
#endif

