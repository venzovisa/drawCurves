
// drawCurvesView.h : interface of the CdrawCurvesView class
//

#pragma once


class CdrawCurvesView : public CView
{
protected: // create from serialization only
	CdrawCurvesView();
	DECLARE_DYNCREATE(CdrawCurvesView)

// Attributes
public:
	CdrawCurvesDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CdrawCurvesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnClose();
	afx_msg void OnExitSizeMove();
};

#ifndef _DEBUG  // debug version in drawCurvesView.cpp
inline CdrawCurvesDoc* CdrawCurvesView::GetDocument() const
   { return reinterpret_cast<CdrawCurvesDoc*>(m_pDocument); }
#endif

