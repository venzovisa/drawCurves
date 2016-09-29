
// drawCurvesView.cpp : implementation of the CdrawCurvesView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "drawCurves.h"
#endif

#include "drawCurvesDoc.h"
#include "drawCurvesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <iostream>
using namespace std;
#include "MyDialog.h"


// CdrawCurvesView

IMPLEMENT_DYNCREATE(CdrawCurvesView, CView)

BEGIN_MESSAGE_MAP(CdrawCurvesView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CdrawCurvesView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()

//	ON_WM_CLOSE()
	ON_WM_EXITSIZEMOVE()
END_MESSAGE_MAP()

// CdrawCurvesView construction/destruction

CdrawCurvesView::CdrawCurvesView()
{
	// TODO: add construction code here

}

CdrawCurvesView::~CdrawCurvesView()
{
}

BOOL CdrawCurvesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CdrawCurvesView drawing

void CdrawCurvesView::OnDraw(CDC* pDC)
{
	CdrawCurvesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	for (int i = 1; i < pDoc->nObjects; i++){
		pDC->MoveTo(pDoc->data[i-1].x,pDoc->data[i-1].y);
		pDC->LineTo(pDoc->data[i].x, pDoc->data[i].y);	
	}		
}


// CdrawCurvesView printing


void CdrawCurvesView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CdrawCurvesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CdrawCurvesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CdrawCurvesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CdrawCurvesView::OnRButtonUp(UINT nFlags, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
	CdrawCurvesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->data[pDoc->closestCoords].x = point.x;
	pDoc->data[pDoc->closestCoords].y = point.y;
	//pDoc->closestCoords = 0;
	Invalidate();
}

void CdrawCurvesView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CdrawCurvesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < pDoc->nObjects; i++){
		if (abs(pDoc->data[i].x - point.x) <= 30) {
			pDoc->closestCoords = i;
		}
	}

	CView::OnRButtonDown(nFlags, point);
}

void CdrawCurvesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CdrawCurvesView diagnostics

#ifdef _DEBUG
void CdrawCurvesView::AssertValid() const
{
	CView::AssertValid();
}

void CdrawCurvesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdrawCurvesDoc* CdrawCurvesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdrawCurvesDoc)));
	return (CdrawCurvesDoc*)m_pDocument;
}
#endif //_DEBUG


// CdrawCurvesView message handlers


void CdrawCurvesView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CdrawCurvesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	/*if (pDoc->nClicks % 2 == 0) { // start point of line
		pDoc->x[pDoc->nObjects] = point.x;
		pDoc->y[pDoc->nObjects] = point.y;
	} else { // end point of line
		pDoc->lengthX[pDoc->nObjects] = point.x - pDoc->x[pDoc->nObjects];
		pDoc->lengthY[pDoc->nObjects] = point.y - pDoc->y[pDoc->nObjects];
		
		pDoc->currentXCounter++;
		pDoc->currentYCounter++;
		pDoc->nObjects++;
		Invalidate();
	}

	pDoc->nClicks++;*/
	pDoc->data[pDoc->nObjects].x=point.x;
	pDoc->data[pDoc->nObjects].y=point.y;
	pDoc->nObjects++;
	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void CdrawCurvesView::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
}


//void CdrawCurvesView::OnClose()
//{
//	// TODO: Add your message handler code here and/or call default
//	CMyDialog D;
//	D.DoModal();
//
//	CView::OnClose();
//}


void CdrawCurvesView::OnExitSizeMove()
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnExitSizeMove();
}
