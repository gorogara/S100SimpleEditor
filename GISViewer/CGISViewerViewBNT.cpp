#include "stdafx.h"

#ifndef SHARED_HANDLERS  
#include "GISViewer.h"  
#endif  

#include "GISViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef BNT_MODULE

#include "DialogExBNTSetting.h"
#include "..\\Library\\BNT\LIB.VIEW.Draw_arrow.h"
#include "..\\GISLibrary\\GISLibrary.h"
//#include "..\\TideTables\\InterfaceTideTables.h"

double GetDegreeFromCartesian(double x, double y)
{
	return 0;
}

void CGISViewerView::DrawBNTCurrent(CDC* pDC, int offsetX, int offsetY)
{
	CRect viewRect;
	GetClientRect(viewRect);

	m_RenderTarget.BindDC(*pDC, viewRect);
	m_RenderTarget.BeginDraw();
	kv::VIEW_ARROW va;
	va.angle = (float)(acos(-1.0) / 4.0f);
	va.width = 5;
	va.fill = true;

	double arrowLength = 0;

	int data_count = theApp.data_count;

	for (auto i = 0; i < data_count; i++)
	{
		double x = theApp.view_data[i].x;
		double y = theApp.view_data[i].y;

		double u = theApp.view_data[i].u; //x
		double v = theApp.view_data[i].v; //y

		double speed = sqrt(u*u + v*v); // cm/s

		speed /= 100.0; // m/s
		speed *= 1.943844; // kn

		int step = 0;

		if (speed < 0.2)
		{
			step = 1;
		}
		else if (speed < 0.5)
		{
			step = 2;
		}
		else if (speed < 1)
		{
			step = 3;
		}
		else if (speed < 1.5)
		{
			step = 4;
		}
		else if (speed < 2)
		{
			step = 5;
		}
		else if (speed < 3)
		{
			step = 6;
		}
		else if (speed < 4)
		{
			step = 7;
		}
		else if (speed < 5)
		{
			step = 8;
		}
		else
		{
			step = 9;
		}

		int lod = theApp.nLod;
		

		double RAD2DEG = 180.0 / acos(-1.0);
		double DEG2RAD = acos(-1.0) / 180.0;

		double angle = atan2(v, u) * RAD2DEG;
		angle = 450 - angle;

		

		m_pGisLib->Projection(&x, &y);

		long lat = 0;
		long lon = 0;

		m_pGisLib->WorldToDevice(x, y, &lon, &lat);

		POINT p;
		p.x = lon;
		p.y = lat;
		if (viewRect.PtInRect(POINT(p)))
		{
			asc.Draw(m_RenderTarget, m_pBlackBrush, (int)lon + offsetX, (int)lat + offsetY, step, SATELLITE, angle * DEG2RAD);
		}
	}

	m_RenderTarget.EndDraw();
}

void CGISViewerView::BNTReload()
{
	CRect viewRect;
	GetClientRect(viewRect);

	double xmin = 0;
	double ymin = 0;
	double xmax = 0;
	double ymax = 0;

	m_pGisLib->DeviceToWorld(viewRect.left, viewRect.bottom, &xmin, &ymin);
	m_pGisLib->DeviceToWorld(viewRect.right, viewRect.top, &xmax, &ymax);
	m_pGisLib->InverseProjection(&xmin, &ymin);
	m_pGisLib->InverseProjection(&xmax, &ymax);

	MBR viewMBR;
	viewMBR.SetMBR(xmin, ymin, xmax, ymax);
	MBR bntMBR;
	bntMBR.SetMBR(theApp.metadata.x_lt, theApp.metadata.y_rb, theApp.metadata.x_rb, theApp.metadata.y_lt);

	if (MBR::IntersectMBR(viewMBR, bntMBR, BNTintersectMBR))
	{
		double scale = m_pGisLib->GetCurrentScale();
	}

	double scale = m_pGisLib->GetCurrentScale();

	if (scale <= 40000)
	{
		theApp.nLod = 7;
	}
	else if (scale <= 60000)
	{
		theApp.nLod = 6;
	}
	else if (scale <= 120000)
	{
		theApp.nLod = 5;
	}
	else if (scale <= 220000)
	{
		theApp.nLod = 4;
	}
	else if (scale <= 500000)
	{
		theApp.nLod = 3;
	}
	else if (scale <= 1600000)
	{
		theApp.nLod = 2;
	}
	else
	{
		theApp.nLod = 1;
	}

	if (!TCSMap_SetRegion(theApp.m_thDataHandle, BNTintersectMBR.xmin, BNTintersectMBR.ymax, BNTintersectMBR.xmax, BNTintersectMBR.ymin, theApp.nLod))
	{
		return;
	}

	if (!TCSMap_LockDataSync(theApp.m_thDataHandle, theApp.m_arrayFrameHandles, theApp.MAX_FRAME))
	{
		return;
	}

	theApp.view_data = NULL;
	theApp.data_count = 0;
	if (theApp.m_FrameCount > 0)
	{
		if (!TCSMap_GetFrameData(theApp.m_arrayFrameHandles[0], &(theApp.view_data), &(theApp.data_count)))
		{
			AfxMessageBox(_T("수치조류도 모델의 프레임 데이터를 얻는데 실패했습니다.!"));
			return;
		}
	}
}
#endif 

void CGISViewerView::OnButtonBntNow()
{
#ifdef BNT_MODULE
	SYSTEMTIME s;
	GetLocalTime(&s);

	theApp.m_Times.clear();
	theApp.Reset_Frame(s);
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
	slider->SetPos(0);
	
#ifndef TIDE_TABLES
	Invalidate();
#else
	MapRefresh();
#endif 
#endif
}
void CGISViewerView::OnButtonBntSetting()
{
#ifdef BNT_MODULE
	if (m_pDlgBNTSetting != nullptr)
	{
		m_pDlgBNTSetting->SetFocus();
	}
	else
	{
		m_pDlgBNTSetting = new CDialogExBNTSetting();
		m_pDlgBNTSetting->m_pView = this;
		if (m_pDlgBNTSetting->Create(IDD_DIALOG_BNT_SETTING))
		{
			m_pDlgBNTSetting->CenterWindow();
			m_pDlgBNTSetting->ShowWindow(SW_SHOW);
			m_pDlgBNTSetting->SetFocus();
		}
		else
		{
			OutputDebugString(_T("GISViewer : Can't create IDD_DIALOG_BNT_SETTING"));
		}
	}
#endif 
}

void CGISViewerView::OnButtonBntAtStart()
{
#ifdef BNT_MODULE
	try {
		theApp.Reset_Frame(theApp.m_Times.at(0));
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
		slider->SetPos(0);
		
#ifndef TIDE_TABLES
		Invalidate();
#else
		MapRefresh();
#endif 
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("GISViewer : out of range in CGISViewerViewBNT.cpp (263)"));
		return;
	}
#endif
}

void CGISViewerView::OnUpdateButtonBntAtStart(CCmdUI *pCmdUI)
{
#ifdef BNT_MODULE
	if (theApp.m_Times.size() == 0) pCmdUI->Enable(FALSE);
#endif#ifdef BNT_MODULE
}

void CGISViewerView::OnButtonBntToPrev()
{
#ifdef BNT_MODULE
	try {
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
		int pos = slider->GetPos();

		if (pos == 0)
		{
			return;
		}

		pos--;
		slider->SetPos(pos);
		theApp.Reset_Frame(theApp.m_Times.at(pos));
		
#ifndef TIDE_TABLES
		Invalidate();
#else
		MapRefresh();
#endif 
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("GISViewer : out of range in CGISViewerViewBNT.cpp (263)"));
		return;
	}
#endif#ifdef BNT_MODULE
}

void CGISViewerView::OnUpdateButtonBntToPrev(CCmdUI *pCmdUI)
{
#ifdef BNT_MODULE
	if (theApp.m_Times.size() == 0) pCmdUI->Enable(FALSE);
#endif#ifdef BNT_MODULE

}

void CGISViewerView::OnButtonBntPlay()
{
#ifdef BNT_MODULE
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonButton* button = (CMFCRibbonButton*)ribbon->FindByID(ID_BUTTON_BNT_PLAY);
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
	if (m_bPlay == false) // 정지중
	{
		int pos = slider->GetPos();

		if (pos == (theApp.m_Times.size() - 1)) return;

		button->SetImageIndex(85, TRUE);
		button->SetText(_T("일시정지"));
		button->Redraw();
		SetTimer(1021, 1000, NULL);
		m_bPlay = true;
	}
	else // 재생중
	{
		button->SetImageIndex(79, TRUE);
		button->SetText(_T("실행"));
		ribbon->Invalidate(0);
		KillTimer(1021);
		m_bPlay = false;
	}
	
#endif#ifdef BNT_MODULE
}

void CGISViewerView::OnUpdateButtonBntPlay(CCmdUI *pCmdUI)
{
#ifdef BNT_MODULE
	if (theApp.m_Times.size() == 0) pCmdUI->Enable(FALSE);
#endif#ifdef BNT_MODULE

}

void CGISViewerView::OnButtonBntStop()
{
#ifdef BNT_MODULE
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonButton* button = (CMFCRibbonButton*)ribbon->FindByID(ID_BUTTON_BNT_PLAY);
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
	button->SetImageIndex(79, TRUE);
	button->SetText(_T("실행"));
	ribbon->Invalidate(0);
	KillTimer(1021);
	m_bPlay = false;
#endif

#ifdef BNT_MODULE
	try {
		theApp.Reset_Frame(theApp.m_Times.at(0));
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
		slider->SetPos(0);

#ifndef TIDE_TABLES
		Invalidate();
#else
		MapRefresh();
#endif 
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("GISViewer : out of range in CGISViewerViewBNT.cpp (263)"));
		return;
	}
#endif
}

void CGISViewerView::OnUpdateButtonBntStop(CCmdUI *pCmdUI)
{
#ifdef BNT_MODULE
	if (theApp.m_Times.size() == 0) pCmdUI->Enable(FALSE);
#endif#ifdef BNT_MODULE

}

void CGISViewerView::OnButtonBntToNext()
{
#ifdef BNT_MODULE
	try {
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
		int pos = slider->GetPos();
		
		if (pos == (theApp.m_Times.size() - 1))
		{
			return;
		}
		
		pos++;

		if (pos == (theApp.m_Times.size() - 1))
		{
			CMFCRibbonButton* button = (CMFCRibbonButton*)ribbon->FindByID(ID_BUTTON_BNT_PLAY);
			button->SetImageIndex(79, TRUE);
			button->SetText(_T("실행"));
			ribbon->Invalidate(0);
			KillTimer(1021);
			m_bPlay = false;
		}
		
		slider->SetPos(pos);
		theApp.Reset_Frame(theApp.m_Times.at(pos));
		
#ifndef TIDE_TABLES
		Invalidate();
#else
		MapRefresh();
#endif 
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("GISViewer : out of range in CGISViewerViewBNT.cpp (263)"));
		return;
	}
#endif#ifdef BNT_MODULE
}

void CGISViewerView::OnUpdateButtonBntToNext(CCmdUI *pCmdUI)
{
#ifdef BNT_MODULE
	if (theApp.m_Times.size() == 0) pCmdUI->Enable(FALSE);
#endif#ifdef BNT_MODULE

}

void CGISViewerView::OnButtonBntToEnd()
{
#ifdef BNT_MODULE
	try {
		int lastIndex = theApp.m_Times.size() - 1;
		theApp.Reset_Frame(theApp.m_Times.at(lastIndex));
		CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
		CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
		slider->SetPos(theApp.m_Times.size() - 1);
		
#ifndef TIDE_TABLES
		Invalidate();
#else
		MapRefresh();
#endif 
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("GISViewer : out of range in CGISViewerViewBNT.cpp (263)"));
		return;
	}
#endif#ifdef BNT_MODULE
}

void CGISViewerView::OnUpdateButtonBntToEnd(CCmdUI *pCmdUI)
{
#ifdef BNT_MODULE
	if (theApp.m_Times.size() == 0) pCmdUI->Enable(FALSE);
#endif#ifdef BNT_MODULE

}

void CGISViewerView::OnButtonRibbonSliderBntSlider()
{
#ifdef BNT_MODULE
	CMFCRibbonBar* ribbon = (CMFCRibbonBar*)m_pMainFrame->GetRibbonBar();
	CMFCRibbonSlider* slider = (CMFCRibbonSlider*)ribbon->FindByID(ID_RIBBON_SLIDER_BNT_SLIDER);
	
	/*CURSORINFO p;
	p.cbSize = sizeof(p);
	GetCursorInfo(&p);
	if (p.flags & MK_LBUTTON)
	{
		OutputDebugString(_T("drag\n"));
		return;
	}
	OutputDebugString(_T("click!!!!!!!!!!!!!!!!"));*/
	try {
		int year = theApp.m_Times.at(slider->GetPos()).wYear;
		int month = theApp.m_Times.at(slider->GetPos()).wMonth;
		int day = theApp.m_Times.at(slider->GetPos()).wDay;
		int hour = theApp.m_Times.at(slider->GetPos()).wHour;
		int min = theApp.m_Times.at(slider->GetPos()).wMinute;

		m_pMainFrame->DisplayBNTTime(theApp.m_Times.at(slider->GetPos()));
		theApp.Reset_Frame(theApp.m_Times.at(slider->GetPos()));

#ifndef TIDE_TABLES
		Invalidate();
#else
		MapRefresh();
#endif 
	}
	catch (std::out_of_range) {
		OutputDebugString(_T("GISViewer : exception error in CGISViewerViewBNT.cpp (348)"));
		return;
	}
#endif#ifdef BNT_MODULE
}

void CGISViewerView::OnUpdateButtonRibbonSliderBntSlider(CCmdUI *pCmdUI)
{
#ifdef BNT_MODULE
	if (theApp.m_Times.size() == 0) pCmdUI->Enable(FALSE);
#endif#ifdef BNT_MODULE
}