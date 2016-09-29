
// drawCurvesDoc.cpp : implementation of the CdrawCurvesDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "drawCurves.h"
#endif

#include "drawCurvesDoc.h"

#include <propkey.h>
#include "MyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CdrawCurvesDoc

IMPLEMENT_DYNCREATE(CdrawCurvesDoc, CDocument)

BEGIN_MESSAGE_MAP(CdrawCurvesDoc, CDocument)
END_MESSAGE_MAP()


// CdrawCurvesDoc construction/destruction

CdrawCurvesDoc::CdrawCurvesDoc()
{
	// TODO: add one-time construction code here


}

CdrawCurvesDoc::~CdrawCurvesDoc()
{
}

BOOL CdrawCurvesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
	CMyDialog D;
	D.DoModal();
	if (D.DoModal() == IDCANCEL) {
		for (int i = 0; i < nObjects; i++) {
		data[i].x = 0;
		data[i].y = 0;		
		}	
		D.ShowWindow(SW_HIDE);
	} else if (D.DoModal() == IDOK) {
		
	}
	nObjects = 0;
	closestCoords = 0;
	return TRUE;
}




// CdrawCurvesDoc serialization

void CdrawCurvesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{		
		
		ar.Write(&nObjects, sizeof(int));
		ar.Write(&data, sizeof(data));
	}
	else
	{		
		ar.Read(&nObjects, sizeof(int));
		ar.Read(&data, sizeof(data));
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CdrawCurvesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CdrawCurvesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CdrawCurvesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CdrawCurvesDoc diagnostics

#ifdef _DEBUG
void CdrawCurvesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CdrawCurvesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CdrawCurvesDoc commands
