// DialogSVGView.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogSVGView.h"
#include "afxdialogex.h"

#include "GISLibrary\\GISLibrary.h" 

IMPLEMENT_DYNAMIC(CDialogSVGView, CDialogEx)

CDialogSVGView::CDialogSVGView(CWnd* pParent )
	: CDialogEx(CDialogSVGView::IDD, pParent)
{

}

CDialogSVGView::~CDialogSVGView()
{
}

void CDialogSVGView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}  

BEGIN_MESSAGE_MAP(CDialogSVGView, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP() 


void CDialogSVGView::OnPaint()
{
	CPaintDC dc(this); 
	
	ENCGeometry::typeOfDrawing = 2;
	ENCGeometry::InitTextRect();
	ENCGeometry::InitSoundingTextRect();
	ENCGeometry::InitIsobathTextRect();

	CRect rect;
	GetClientRect(&rect);

	CDC* pDC = (CDC*)&dc;

	if (!mem_dc.GetSafeHdc())
	{
		if (mem_dc.CreateCompatibleDC(pDC))
		{
			if (memBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				CBitmap* pOldBitmap = mem_dc.SelectObject(&memBitmap);
				if (pOldBitmap != NULL) 
				{
					pOldBitmap->DeleteObject();
				}
			}
			mem_dc.SetBkMode(TRANSPARENT);
		}
		if (transDC.CreateCompatibleDC(pDC))
		{
			if (transBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				CBitmap* pOldBitmap = transDC.SelectObject(&transBitmap);
				if (pOldBitmap != NULL)
				{

					pOldBitmap->DeleteObject();
				}
			}
			transDC.SetBkMode(TRANSPARENT);
		}
		if (map_dc.CreateCompatibleDC(pDC))
		{
			if (mapBitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height()))
			{
				CBitmap* pOldBitmap = map_dc.SelectObject(&mapBitmap);
				if (pOldBitmap != NULL)
					pOldBitmap->DeleteObject();
			}
			map_dc.SetBkMode(TRANSPARENT);
		}
	}
	{
		map_dc.FillSolidRect(&rect, RGB(255, 255, 255));
		HDC hdc = map_dc.GetSafeHdc();

		HRGN rgn = CreateRectRgn(0, 0, rect.Width(), rect.Height());
		::SelectClipRgn(hdc, rgn);

		m_pGisLib->SetViewMBR(rect);
		BeginWaitCursor();
		m_pGisLib->Draw(hdc);
		EndWaitCursor();

		::DeleteObject(rgn);

		mem_dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &map_dc, 0, 0, SRCCOPY);
		pDC->BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &mem_dc, 0, 0, SRCCOPY);
	}
}

void CDialogSVGView::DeleteDCs()
{
	mem_dc.DeleteDC();
	memBitmap.DeleteObject();
	transDC.DeleteDC();
	transBitmap.DeleteObject();
	map_dc.DeleteDC();
	mapBitmap.DeleteObject();
}