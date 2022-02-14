// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface           
 
#include "stdafx.h"  
#ifndef SHARED_HANDLERS
#include "GISViewer.h"
#endif

#include "GISViewerDoc.h"
#include "GISViewerView.h" 

#include "ConfigrationDlg.h"
#include "CFCPCSettingDlg.h"

#include <propkey.h>
 
#ifdef _DEBUG  
#define new DEBUG_NEW
#endif 

IMPLEMENT_DYNCREATE(CGISViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CGISViewerDoc, CDocument)
	
#ifdef _NMEA_DATA
	ON_COMMAND(ID_BTN_GPS_ACTIVE, &CGISViewerDoc::OnBtnGpsActive)
	ON_UPDATE_COMMAND_UI(ID_BTN_GPS_ACTIVE, &CGISViewerDoc::OnUpdateBtnGpsActive)
	ON_COMMAND(ID_BTN_GPS_MY_LOC, &CGISViewerDoc::OnBtnGpsMyLoc)
#endif
	ON_COMMAND(ID_BUTTON_CONFIG, &CGISViewerDoc::OnButtonConfig)
	ON_COMMAND(ID_SERIAL_PORTS, &CGISViewerDoc::OnSerialPorts)    
	ON_COMMAND(ID_BUTTON_FCPCSETTING, &CGISViewerDoc::OnButtonFcpcsetting)
END_MESSAGE_MAP() 

CGISViewerDoc::CGISViewerDoc()
{               

}

CGISViewerDoc::~CGISViewerDoc()
{
}

BOOL CGISViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;  

#ifdef _NMEA_DATA
	SetSerialPorts();
#endif
	return TRUE;
} 

void CGISViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{ 
	}
	else
	{ 
	}
}

#ifdef SHARED_HANDLERS 
void CGISViewerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{ 
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
void CGISViewerDoc::InitializeSearchContent()
{
	CString strSearchContent;   
	SetSearchContent(strSearchContent);
}

void CGISViewerDoc::SetSearchContent(const CString& value)
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

#endif  

#ifdef _DEBUG
void CGISViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGISViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif     

#ifdef _NMEA_DATA

void CGISViewerDoc::SetSerialPorts()
{
	CString strComPort;
	HKEY h_CommKey;
	LONG Reg_Ret;
	DWORD Size = MAX_PATH;
	wchar_t i_str[MAX_PATH];  

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pFontComboBox = DYNAMIC_DOWNCAST( CMFCRibbonComboBox, pMain->GetRibbonBar()->FindByID(ID_SERIAL_PORTS));

	LPCWSTR lpwszSubKey = L"HARDWARE\\DEVICEMAP\\SERIALCOMM";

	Reg_Ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, lpwszSubKey, 0, KEY_ALL_ACCESS, &h_CommKey);                        
	if(Reg_Ret == ERROR_SUCCESS)
	{
		CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
		CMFCRibbonComboBox* pFontComboBox = DYNAMIC_DOWNCAST( CMFCRibbonComboBox, pMain->GetRibbonBar()->FindByID(ID_SERIAL_PORTS));
		if(Reg_Ret == ERROR_SUCCESS)
		{
			for(int i = 0; Reg_Ret == ERROR_SUCCESS; i++)
			{
				Reg_Ret = RegEnumValue(h_CommKey, i, i_str, &Size, NULL, NULL, NULL, NULL);
				if(Reg_Ret == ERROR_SUCCESS)
				{
					DWORD dwType, dwSize = MAX_PATH;
					wchar_t szBuffer[MAX_PATH];

					RegQueryValueEx(h_CommKey, i_str, 0, &dwType, (LPBYTE)szBuffer, &dwSize);

					pFontComboBox->AddItem(szBuffer);  
				}
				Size = MAX_PATH;
			}
		}
	}

	pFontComboBox->SelectItem(0);
	RegCloseKey(h_CommKey); 
}

CComm* CGISViewerDoc::GetComm()
{
	return &m_Comm;
}

TTYSTRUCT CGISViewerDoc::Int2TTY()
{  
	TTYSTRUCT tty;
	ZERO_MEMORY(tty);

	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonComboBox* pFontComboBox = DYNAMIC_DOWNCAST( CMFCRibbonComboBox, pMain->GetRibbonBar()->FindByID(ID_SERIAL_PORTS));

	CString port = pFontComboBox->GetItem(pFontComboBox->GetCurSel());

	CString number = port.Mid(3);

	tty.byCommPort = (BYTE)(_wtoi(number));
	tty.byXonXoff = FALSE;
	tty.byByteSize = (BYTE)_nDataValues[m_nDataBits];
	tty.byFlowCtrl = (BYTE)_nFlow[m_nFlowControl];
	tty.byParity = (BYTE)m_nParity;
	tty.byStopBits = (BYTE)_nStopBits[m_nStopBits];
	tty.dwBaudRate = (DWORD)CBR_4800;//_nBaudRates[m_nBaudRate];

	return tty;
}


void CGISViewerDoc::OnBtnGpsActive()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CGISViewerView* pView = (CGISViewerView*)pMain->GetActiveView();
	m_Comm.SetHwnd(pView->m_hWnd); 
	CMFCRibbonComboBox* pFontComboBox = DYNAMIC_DOWNCAST( CMFCRibbonComboBox, pMain->GetRibbonBar()->FindByID(ID_SERIAL_PORTS));

	m_nParity = 0; 
	m_nDataBits = 1; 
	m_nStopBits = 0; 
	m_nFlowControl = 0; 

	if (!GetComm()->fConnected)
	{ 
		if(GetComm()->OpenCommPort(&Int2TTY()) != TRUE)
		{ 
			CString str = L"SERIAL PORT OPEN ERROR"; 
			AfxMessageBox(str);

			GetComm()->fConnected = false;
			return;
		}   


	}
	else
	{ 
		GetComm()->CloseConnection();   
	}
}


void CGISViewerDoc::OnUpdateBtnGpsActive(CCmdUI *pCmdUI)
{
	if (GetComm()->fConnected)
	{
		pCmdUI->SetText(_T("Connected"));
	}
	else
	{
		pCmdUI->SetText(_T("Connect"));
	}
} 
#endif

void CGISViewerDoc::OnBtnGpsMyLoc()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CGISViewerView* pView = (CGISViewerView*)pMain->GetActiveView();

	pView->MoveMapToMyPosition();
}

void CGISViewerDoc::OnButtonConfig()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CGISViewerView* pView = (CGISViewerView*)pMain->GetActiveView();

	CConfigrationDlg dlg(pView); 
	auto itor = LayerManager::hash_FC->find(L"S-101");
	if (itor != LayerManager::hash_FC->end())
	{
		dlg.InitS101FeatureTypes(itor->second);
	}

	if (m_systemFontList.size() == 0)
	{ 
		HRESULT hr;
		IDWriteFactory* pDWriteFactory = pView->m_pGisLib->D2.pDWriteFactory;
		IDWriteFontCollection* pFontCollection = NULL;  
		{
			hr = pDWriteFactory->GetSystemFontCollection(&pFontCollection);
		}
		UINT32 familyCount = 0; 
		if (SUCCEEDED(hr))
		{
			familyCount = pFontCollection->GetFontFamilyCount();
		}
		for (UINT32 i = 0; i < familyCount; ++i)
		{
			IDWriteFontFamily* pFontFamily = NULL; 
			if (SUCCEEDED(hr))
			{
				hr = pFontCollection->GetFontFamily(i, &pFontFamily);
				IDWriteLocalizedStrings* pFamilyNames = NULL; 
				if (SUCCEEDED(hr))
				{
					hr = pFontFamily->GetFamilyNames(&pFamilyNames);
					UINT32 index = 0;
					BOOL exists = false;

					wchar_t localeName[LOCALE_NAME_MAX_LENGTH];

					if (SUCCEEDED(hr))
					{ 
						int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH); 
						if (defaultLocaleSuccess)
						{
							hr = pFamilyNames->FindLocaleName(localeName, &index, &exists);
						}
						if (SUCCEEDED(hr) && !exists) 
						{
							hr = pFamilyNames->FindLocaleName(L"en-us", &index, &exists);
						}

						UINT32 length = 0; 
						if (SUCCEEDED(hr))
						{
							hr = pFamilyNames->GetStringLength(index, &length);
						} 
						wchar_t* name = new wchar_t[length + 1];
						if (name == NULL)
						{
							hr = E_OUTOFMEMORY;
						} 
						if (SUCCEEDED(hr))
						{
							hr = pFamilyNames->GetString(index, name, length + 1);

							m_systemFontList.push_back(name);
						}

						delete name;
					} 
					if (!exists)
						index = 0;
				}

				SafeRelease(&pFamilyNames);
			}
		}
		SafeRelease(&pFontCollection);
	}
	dlg.GetConfigPage1()->SetFontList(m_systemFontList);
	dlg.DoModal();
}


void CGISViewerDoc::OnSerialPorts()
{

}


void CGISViewerDoc::OnButtonFcpcsetting()
{
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CGISViewerView* pView = (CGISViewerView*)pMain->GetActiveView();

	CFCPCSettingDlg dlg(pView);
	dlg.SettingPCFC(); 
	dlg.DoModal(); 
}
