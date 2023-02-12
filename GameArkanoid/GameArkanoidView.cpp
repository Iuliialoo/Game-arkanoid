
// GameArkanoidView.cpp: реализация класса CGameArkanoidView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GameArkanoid.h"
#endif

#include "GameArkanoidDoc.h"
#include "GameArkanoidView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGameArkanoidView

IMPLEMENT_DYNCREATE(CGameArkanoidView, CView)

BEGIN_MESSAGE_MAP(CGameArkanoidView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CGameArkanoidView

CGameArkanoidView::CGameArkanoidView() noexcept
{
	// TODO: добавьте код создания

}

CGameArkanoidView::~CGameArkanoidView()
{
}

BOOL CGameArkanoidView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CGameArkanoidView

void CGameArkanoidView::OnDraw(CDC* pDC)
{
	CGameArkanoidDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	if (pDoc->myPlane.statusGame == (int)StatusGame::start) {
		pDoc->myPlane.draw(pDC);
		pDoc->myCircle.draw(pDC);
		pDoc->drawBlocks(pDC);
	}
	if (pDoc->myPlane.statusGame == (int)StatusGame::lose) {
		CString str;
		str.Format(L"YOU LOSE");
		pDC->TextOutW(rect.Width() / 2.0, rect.Height() / 2.0, str);
	}
	if (pDoc->myPlane.statusGame == (int)StatusGame::win) {
		CString str;
		str.Format(L"YOU WIN");
		pDC->TextOutW(rect.Width() / 2.0, rect.Height() / 2.0, str);
	}

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CGameArkanoidView

BOOL CGameArkanoidView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CGameArkanoidView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CGameArkanoidView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CGameArkanoidView

#ifdef _DEBUG
void CGameArkanoidView::AssertValid() const
{
	CView::AssertValid();
}

void CGameArkanoidView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGameArkanoidDoc* CGameArkanoidView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGameArkanoidDoc)));
	return (CGameArkanoidDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CGameArkanoidView


void CGameArkanoidView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	srand(time(NULL));

	CGameArkanoidDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	pDoc->myPlane.create(&rect);
	pDoc->myCircle.create(&rect, &pDoc->myPlane);

	pDoc->countBlocksX = 8;
	pDoc->countBlocksY = 5;

	createLevel(100, 30);

	SetTimer(0, 10, NULL);
}

void CGameArkanoidView::createLevel(int widthBlock, int heightBlock) {
	CGameArkanoidDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	pDoc->countBreakBlocks = 0;
	pDoc->myPlane.statusGame = 0;
	pDoc->myCircle.startMove = false;

	int a = rect.Width();
	int distanceBetweenBlocksX = (rect.Width() - pDoc->countBlocksX * widthBlock) / (pDoc->countBlocksX + 1);
	int distanceBetweenBlocksY = 30;

	pDoc->blocks.resize(pDoc->countBlocksX);
	for (int i = 0; i < pDoc->countBlocksX; i++)
		pDoc->blocks[i].resize(pDoc->countBlocksY);

	for (int i = 0; i < pDoc->countBlocksX; i++) {
		for (int j = 0; j < pDoc->countBlocksY; j++) {
			pDoc->blocks[i][j].create(distanceBetweenBlocksX * (i + 1) + widthBlock * i, distanceBetweenBlocksY * (j + 1) + heightBlock * j, distanceBetweenBlocksX * (i + 1) + widthBlock * (i + 1), distanceBetweenBlocksY * (j + 1) + heightBlock * (j + 1));
		}
	}
}

void CGameArkanoidView::OnTimer(UINT_PTR nIDEvent)
{
	CGameArkanoidDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(&rect);

	if (pDoc->myCircle.startMove)
		pDoc->myCircle.move();

	checkBreakBlock();

	Invalidate();
	CView::OnTimer(nIDEvent);
}

void CGameArkanoidView::checkBreakBlock() {
	CGameArkanoidDoc* pDoc = GetDocument();

	for (int i = 0; i < pDoc->blocks.size(); i++) {
		for (int j = 0; j < pDoc->blocks[i].size(); j++) {
			if (pDoc->blocks[i][j].checkCircle(&pDoc->myCircle)) {
				pDoc->blocks[i][j].x1 = 0;
				pDoc->blocks[i][j].y1 = 0;
				pDoc->blocks[i][j].x2 = 0;
				pDoc->blocks[i][j].y2 = 0;
				pDoc->countBreakBlocks++;
				TRACE("\n\ncount %d\n\n", pDoc->countBreakBlocks);
				if (pDoc->countBreakBlocks == pDoc->countBlocksX * pDoc->countBlocksY) {
					pDoc->myPlane.statusGame = 1;
					TRACE("\n\nall %d\n\n", pDoc->countBlocksX * pDoc->countBlocksY);
					break;
				}
				break;
			}
		}
	}
}


void CGameArkanoidView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CGameArkanoidDoc* pDoc = GetDocument();

	if (nChar == VK_LEFT) {
		pDoc->myPlane.xCenter -= 15;
		if (!pDoc->myCircle.startMove)
			pDoc->myCircle.x -= 15;
	}
	if (nChar == VK_RIGHT) {
		pDoc->myPlane.xCenter += 15;
		if (!pDoc->myCircle.startMove)
			pDoc->myCircle.x += 15;
	}
	if (nChar == VK_SPACE)
		pDoc->myCircle.startMove = true;

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
