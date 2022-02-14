// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface           

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GISViewer.h"
#include "MainFrm.h"
#include "GISViewerDoc.h"
#include "GISViewerView.h"
#include "DialogDockLayerManager.h"
#include "DialogTDSDataset.h"
#include "DialogExCatalogSelect.h"


#include "S100_SVG_D2D1_DLL\\SVGManager.h"
#include "S100_SVG_D2D1_DLL\\S100_SVG_D2D1_DLL.h"
#include "S100_SVG_D2D1_DLL\\UnitOfCSS.h"
#include "S100_SVG_D2D1_DLL\\Declaration.h"
#include "S100_SVG_D2D1_DLL\\CSSStyle.h"
#include "S100_SVG_D2D1_DLL\\SVG.h"
#include "S100_SVG_D2D1_DLL\\CSS.h"
#include "S100_SVG_D2D1_DLL\\S100_Pattern.h"
#include "S100_SVG_D2D1_DLL\\S100_Text.h"
#include "S100_SVG_D2D1_DLL\\RealSymbol.h"

#include "PLLibrary\\GeoObject.h" 
#include "PLLibrary\SymbolManager.h"

#include "..\\DLL_MessageProcess\\DLL_MessageProcess.h"

#include "..\\LibMFCUtil\\LibMFCUtil.h"
#include "..\\LibMFCUtil\\StringTokenizer.h"

#include "S100Geometry\\SGeometry.h"

#include "..\\FeatureCatalog\FeatureCatalogue.h"

#include "S101Portrayal\\PortrayalCatalogue.h"

#include <crtdbg.h>
#include <locale>
#include <codecvt>
#include <vector>


#ifdef _USE_USER_WRECKS_OPEN
#include "DialogExUserWrecks.h"
#endif   

#ifdef TIDE_TABLES
#include "..\\TideTables\\InterfaceTideTables.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include <direct.h>
#include <fstream>         

BEGIN_MESSAGE_MAP(CGISViewerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CGISViewerApp::OnAppAbout) 
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew) 
	ON_COMMAND(ID_BUTTON_DELETE_MEASUREMENT, &CGISViewerApp::OnButtonDeleteMeasurement)
	ON_COMMAND(ID_BTN_TDS_DLG, &CGISViewerApp::OnBtnTdsDlg) 
	ON_UPDATE_COMMAND_UI(ID_USERMODE_BUTTON, &CGISViewerApp::OnUpdateUsermodeButton)
	ON_COMMAND(ID_USERMODE_BUTTON, &CGISViewerApp::OnUsermodeButton) 
END_MESSAGE_MAP() 

CGISViewerApp::CGISViewerApp()
{
	string str = "..\\TEMP"; 
    int mkFlag = _mkdir(str.c_str());   
	SetAppID(_T("S-100 Simple Editor.AppID.NoVersion"));  
	pView = nullptr;

#ifdef _SEA_TRIAL 
	m_strSeaTrialIPAddress = _T("175.117.210.37");
	m_nPort = 21000;
	isConnected = false;
	clientType = 0;
	isTracking = false;
#endif 

#ifdef BNT_MODULE
	nLod = 1;
#endif

	
}

CGISViewerApp::~CGISViewerApp()
{ 
} 
CGISViewerApp theApp; 

BOOL CGISViewerApp::InitInstance()
{
	AfxInitRichEdit();

	CWinAppEx::InitInstance(); 
	GdiplusStartupInput GdiplusStartupInput;
	if (::GdiplusStartup(&gdiplusToken, &GdiplusStartupInput, NULL) != Ok)
	{
		AfxMessageBox(_T("Error : Failed to initialize GDI+ library!"));
		return FALSE;
	} 
	if (!AfxOleInit())
	{
		return FALSE;
	}

	EnableTaskbarInteraction(FALSE);       
	SetRegistryKey(_T("S-100 Simple Editor")); 
	CleanState();

	LoadStdProfileSettings(4); 

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);  
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGISViewerDoc),
		RUNTIME_CLASS(CMainFrame), 
		RUNTIME_CLASS(CGISViewerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate); 
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);  
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNew;
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;  
	SetRibbonMenu();
	m_pMainWnd->UpdateWindow(); 
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	CGISViewerView* pView = (CGISViewerView*)pMain->GetActiveView();   
	LoadSettings();

	PC_FCPathSetting();
	BasicFileSetting();

	InitCatalogSelectionDialog(); 
#ifdef _USEINIT_WORLDMAP_OPEN
	pView->OpenWorldMap();
#endif
	InitDocument();

	InitStartingLocation();


#ifdef EXECUTE_FILE_WITH_ARGUMENT_OF_DATASET
	InitStartingDatasetLoading(cmdInfo.m_strFileName);
#endif

	return true;
}

void CGISViewerApp::DatasetOpen(CString _product, CString _path)
{
	Catalog* fc;
	PortrayalCatalogue* pc;


	std::wstring wproduct = _product.GetBuffer();
	fc = LayerManager::GetFC(wproduct);
	pc = LayerManager::GetPC(wproduct);
	_product.ReleaseBuffer();

	if (fc == nullptr || pc == nullptr)
	{
		return;
	}

	pView->m_pGisLib->AddLayer(_path, fc, pc);
}


class PathBasedProduct
{
private: 
	CString path;
	CString product;

public:
	PathBasedProduct(CString _product, CString _path)
	{
		product = _product;
		path = _path;
	}

	CString GetProduct()
	{
		return product;
	}

	CString GetPath()
	{
		return path;
	}
};

void CGISViewerApp::InitStartingDatasetLoading(CString argument)
{
	if (argument.GetLength() < 7)
	{
		OutputDebugString(L"Occured ARGUMENT ERROR");
		return;
	}
	CString pathType = argument.Left(1);

	int ipathType = _ttoi(pathType);

	CString full_path = argument.Right(argument.GetLength() - 2);

	std::vector<PathBasedProduct> pathesBasedProducts;


	int tokenCount = 0;

	CString token;
	int pos = 0;

	while ((token = full_path.Tokenize(L"|", pos)) != "")
	{
		tokenCount++;
	}

	if (tokenCount % 2 != 0)
	{
		OutputDebugString(L"Occured ARGUMENT ERROR");
		return;
	}

	pos = 0; 

	while ((token = full_path.Tokenize(L"|", pos)) != "")
	{
		CString product = token;

		token = full_path.Tokenize(L"|", pos);

		CString path = token;

		PathBasedProduct pathesBasedProduct(product, path);

		pathesBasedProducts.push_back(pathesBasedProduct);
	}

	CFileFind  finder;
	BOOL bWorking;
	CString product;
	CString path;
	CString findPath;
	for (auto i = pathesBasedProducts.begin(); i != pathesBasedProducts.end(); i++)
	{
		PathBasedProduct* pbp = &(*i);
		switch (ipathType)
		{
		case 1: 
			findPath.Format(L"%s\\*.*", pbp->GetPath());
			bWorking = finder.FindFile(findPath);
			while (bWorking)
			{
				bWorking = finder.FindNextFile();
				if (!finder.IsDots() && !finder.IsDirectory())
				{
					CString filepath = finder.GetFilePath();

					DatasetOpen(pbp->GetProduct(), filepath);
				}
			}
			break;

		case 2: 
			DatasetOpen(pbp->GetProduct(), pbp->GetPath());
			break;
		default:
			break;
		}
	}
}

void CGISViewerApp::InitDocument()
{  
	AfxSocketInit();    

	return;
} 

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg(); 
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP() 
void CGISViewerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
} 

void CGISViewerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CGISViewerApp::LoadCustomState()
{
	return;
}

void CGISViewerApp::SaveCustomState()
{

	return;
}

int CGISViewerApp::ExitInstance()
{
	::GdiplusShutdown(gdiplusToken); 

	if (SGeometry::viewPoints)
		delete SGeometry::viewPoints;

	return CWinAppEx::ExitInstance();
}

void CGISViewerApp::LoadSettings()
{ 
	ENCCommon::objectDisplaySettings.clear(); 
	for (int i = 1; i < 99999; i++)
	{
		CGeoObject* obj = ENCGeometry::pObject->GetObjectFromCode(i);
		if (obj)
		{
			if (obj->Code == 81)
				ENCCommon::objectDisplaySettings.insert(
					std::unordered_map<int, bool>::value_type(obj->Code, false)
				);
			else
				ENCCommon::objectDisplaySettings.insert(
					std::unordered_map<int, bool>::value_type(obj->Code, true)
				);
		}
	} 

	ifstream ifs;
	ifs.open(L"..\\ProgramData\\data\\settings.txt", std::ios::in);

	if (!ifs.is_open())
	{
		AfxMessageBox(_T("설정파일(settings.txt)을 로드하지 못했습니다!"));
		return;
	}

	string strTrue = "true";
	string strFalse = "false";
	string strLine;

	while (getline(ifs, strLine))
	{
		string opt = strLine.substr(0, 1);
		if (opt.compare("*") == 0)
			continue;

		StringTokenizer *pstringTokenizer = new StringTokenizer(strLine, " \t");
		strLine.clear();

		if (pstringTokenizer->hasMoreTokens())
		{
			string token = pstringTokenizer->nextToken();

			if (token.compare("APPLY_SCALE_MIN") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::APPLY_SCALE_MIN = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::APPLY_SCALE_MIN = false;
					}
				}
			}
			else if (token.compare("CONTOUR_LABELS") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::CONTOUR_LABELS = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::CONTOUR_LABELS = false;
					}
				}
			}
			else if (token.compare("DEEP_CONTOUR") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::DEEP_CONTOUR = atof(token.c_str());
				}
			}
			else if (token.compare("DISTANCE_TAGS") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::DISTANCE_TAGS = atoi(token.c_str());
				}
			}
			else if (token.compare("DISPLAY_MODE") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::DISPLAY_MODE = static_cast<ENCCommon::DisplayModeTable>(atoi(token.c_str()));
				}
			}
			else if (token.compare("DrawingType") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::DrawingType = atoi(token.c_str());
				}
			}
			else if (token.compare("LIGHTS") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::LIGHTS = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::LIGHTS = false;
					}
				}
			}
			else if (token.compare("OVER_GROUP") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::OVER_GROUP = _atoi64(token.c_str());
				}
			}
			else if (token.compare("SAFETY_DEPTH") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::SAFETY_DEPTH = atof(token.c_str());
				}
			}
			else if (token.compare("SAFETY_CONTOUR") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::SAFETY_CONTOUR = atof(token.c_str());
				}
			}
			else if (token.compare("DISPLAY_FONT_NAME") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();		
					auto fontName = LibMFCUtil::ConvertCtoWC((char*)token.c_str());
					ENCCommon::DISPLAY_FONT_NAME = fontName;
					pView->m_pGisLib->ChangeDisplayFont();
					delete[] fontName;
				}
			}
			else if (token.compare("DISPLAY_FONT_SIZE") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::DISPLAY_FONT_SIZE = atoi(token.c_str());
					pView->m_pGisLib->ChangeDisplayFont();
				}
			}
			else if (token.compare("SHALLOW_CONTOUR") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::SHALLOW_CONTOUR = atof(token.c_str());
				}
			}
			else if (token.compare("SHALLOW_PATTERN") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SHALLOW_PATTERN = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SHALLOW_PATTERN = false;
					}
				}
			}
			else if (token.compare("SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER = false;
					}
				}
			}
			else if (token.compare("FULL_SECTORS") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::FULL_SECTORS = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::FULL_SECTORS = false;
					}
				}
			}
			else if (token.compare("SHOW_NOBJNM") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SHOW_NOBJNM = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SHOW_NOBJNM = false;
					}
				}
			}
			else if (token.compare("AVOID_CLUTTER") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::AVOID_CLUTTER = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::AVOID_CLUTTER = false;
					}
				}
			} 
			else if (token.compare("SHOW_LIST_ABBREVIATION") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SHOW_LIST_ABBREVIATION = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SHOW_LIST_ABBREVIATION = false;
					}
				}
			}
			else if (token.compare("WGS84_TEXT_TYPE") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::WGS84_TEXT_TYPE = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::WGS84_TEXT_TYPE = false;
					}
				}
			}
			else if (token.compare("SOUNDING") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SOUNDING = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SOUNDING = false;
					}
				}
			}
			else if (token.compare("SymbolizedAreaBoundary") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SymbolizedAreaBoundary = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SymbolizedAreaBoundary = false;
					}
				}
			}
			else if (token.compare("SeabedType") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SeabedAreaType = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SeabedAreaType = false;
					}
				}
			}
			else if (token.compare("TEXTOUT") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::TEXTOUT = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::TEXTOUT = false;
					}
				}
			}
			else if (token.compare("TWO_SHADES") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::TWO_SHADES = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::TWO_SHADES = false;
					}
				}
			}
			else if (token.compare("USE_SPATIAL_QUERY") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::USE_SPATIAL_QUERY = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::USE_SPATIAL_QUERY = false;
					}
				}
			}
			else if (token.compare("SHOW_USER_COAST_AREA") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SHOW_USER_COAST_AREA = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SHOW_USER_COAST_AREA = false;
					}
				}
			}
			else if (token.compare("SHOW_USER_COAST_AREA_DETAIL") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					if (token.compare(strTrue) == 0)
					{
						ENCCommon::SHOW_USER_COAST_AREA_DETAIL = true;
					}
					else if (token.compare(strFalse) == 0)
					{
						ENCCommon::SHOW_USER_COAST_AREA_DETAIL = false;
					}
				}
			} 
			else if (token.compare("m_eColorTable") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::m_eColorTable = static_cast<ENCCommon::ColorTable>(atoi(token.c_str()));

					if (ENCCommon::m_eColorTable == ENCCommon::Day)
					{
						ENCCommon::m_eColorTable = ENCCommon::Day;
						pView->m_pGisLib->SetColorTable(_T("..\\ProgramData\\dic\\day_bright.dic"));
						pView->m_pSymbolManager->ReOpenColor(_T("..\\ProgramData\\dic\\day_bright.dic")); 
					}
					else if (ENCCommon::m_eColorTable == ENCCommon::Dusk)
					{
						ENCCommon::m_eColorTable = ENCCommon::Dusk;
						pView->m_pGisLib->SetColorTable(_T("..\\ProgramData\\dic\\dusk_blackback.dic"));
						pView->m_pSymbolManager->ReOpenColor(_T("..\\ProgramData\\dic\\dusk_blackback.dic")); 
					}
					else if (ENCCommon::m_eColorTable == ENCCommon::Night)
					{
						ENCCommon::m_eColorTable = ENCCommon::Night;
						pView->m_pGisLib->SetColorTable(_T("..\\ProgramData\\dic\\night.dic"));
						pView->m_pSymbolManager->ReOpenColor(_T("..\\ProgramData\\dic\\night.dic")); 
					}
				}
			}
			else if (token.compare("UNIT_DISTANCE") == 0)
			{
				if (pstringTokenizer->hasMoreTokens())
				{
					token = pstringTokenizer->nextToken();
					ENCCommon::UNIT_DISTANCE = static_cast<ENCCommon::UnitDistance>(atoi(token.c_str()));
				}
			}
			else if (token.compare("OBJECT_SHOW_SETTING_BEGIN") == 0)
			{
				getline(ifs, strLine);
				while (strLine.compare("OBJECT_SHOW_SETTING_END") != 0)
				{
					int objectCode = 0;
					bool objectValue = 0;

					StringTokenizer *pstringTokenizerObjSettings = new StringTokenizer(strLine, " \t");

					if (pstringTokenizerObjSettings->hasMoreTokens())
					{
						token = pstringTokenizerObjSettings->nextToken();

						objectCode = atoi(token.c_str());
						if (pstringTokenizerObjSettings->hasMoreTokens())
						{
							token = pstringTokenizerObjSettings->nextToken();

							int value = atoi(token.c_str());

							value ? objectValue = true : objectValue = false;
						}
					}

					delete pstringTokenizerObjSettings;

					if (objectCode > 0)
					{
						std::unordered_map<int, bool>::iterator ositor;

						ositor = ENCCommon::objectDisplaySettings.find(objectCode);
						if (ositor != ENCCommon::objectDisplaySettings.end())
						{
							ositor->second = objectValue;

						}
					}
					getline(ifs, strLine);
				}
			}
		}
		delete pstringTokenizer;
	}
} 
void CGISViewerApp::SaveSettings()
{
	std::locale::global(std::locale("Korean"));
	ofstream ofs;
	ofs.open(L"..\\ProgramData\\data\\settings.txt", std::ios::out | ios::trunc | ios::binary);

	string strTrue = "true";
	string strFalse = "false";

	string t = "*This is comment which is not effective on settings.\n";
	ofs.write(t.c_str(), t.size());

	t = "APPLY_SCALE_MIN\t";
	ENCCommon::APPLY_SCALE_MIN ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "CONTOUR_LABELS\t";
	ENCCommon::CONTOUR_LABELS ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "DEEP_CONTOUR\t";
	t.append(_bstr_t(ENCCommon::DEEP_CONTOUR));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "DISTANCE_TAGS\t";
	t.append(_bstr_t(ENCCommon::DISTANCE_TAGS));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "DISPLAY_MODE\t";
	t.append(_bstr_t(ENCCommon::DISPLAY_MODE));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "DrawingType\t";
	t.append(_bstr_t(ENCCommon::DrawingType));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "LIGHTS\t";
	ENCCommon::LIGHTS ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "OVER_GROUP\t";
	t.append(_bstr_t(ENCCommon::OVER_GROUP));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SAFETY_DEPTH\t";
	t.append(_bstr_t(ENCCommon::SAFETY_DEPTH));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SAFETY_CONTOUR\t";
	t.append(_bstr_t(ENCCommon::SAFETY_CONTOUR));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SHALLOW_CONTOUR\t";
	t.append(_bstr_t(ENCCommon::SHALLOW_CONTOUR));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "DISPLAY_FONT_NAME\t";

	char* path = LibMFCUtil::ConvertWCtoC((wchar_t*)std::wstring(ENCCommon::DISPLAY_FONT_NAME).c_str());
	t.append(path);
	delete path;
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "DISPLAY_FONT_SIZE\t";
	t.append(_bstr_t(ENCCommon::DISPLAY_FONT_SIZE));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SHALLOW_PATTERN\t";
	ENCCommon::SHALLOW_PATTERN ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER\t";
	ENCCommon::SHOW_ISOLATED_DANGER_IN_SHALLOW_WATER ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "FULL_SECTORS\t";
	ENCCommon::FULL_SECTORS ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SHOW_NOBJNM\t";
	ENCCommon::SHOW_NOBJNM ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "AVOID_CLUTTER\t";
	ENCCommon::AVOID_CLUTTER ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size()); 

	t = "SHOW_LIST_ABBREVIATION\t";
	ENCCommon::SHOW_LIST_ABBREVIATION ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "WGS84_TEXT_TYPE\t";
	ENCCommon::WGS84_TEXT_TYPE ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SOUNDING\t";
	ENCCommon::SOUNDING ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SymbolizedAreaBoundary\t";
	ENCCommon::SymbolizedAreaBoundary ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SeabedType\t";
	ENCCommon::SeabedAreaType ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "TEXTOUT\t";
	ENCCommon::TEXTOUT ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "TWO_SHADES\t";
	ENCCommon::TWO_SHADES ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "USE_SPATIAL_QUERY\t";
	ENCCommon::USE_SPATIAL_QUERY ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SHOW_USER_COAST_AREA\t";
	ENCCommon::SHOW_USER_COAST_AREA ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	t = "SHOW_USER_COAST_AREA_DETAIL\t";
	ENCCommon::SHOW_USER_COAST_AREA_DETAIL ? t.append(strTrue) : t.append(strFalse);
	t.append("\n");
	ofs.write(t.c_str(), t.size()); 
	t = "m_eColorTable\t";
	t.append(_bstr_t((int)ENCCommon::m_eColorTable));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	int i = 0;

	t = "UNIT_DISTANCE\t";
	t.append(_bstr_t((int)ENCCommon::UNIT_DISTANCE));
	t.append("\n");
	ofs.write(t.c_str(), t.size());

	std::unordered_map<int, bool>::iterator oitor;

	t = "OBJECT_SHOW_SETTING_BEGIN\n";
	ofs.write(t.c_str(), t.size());

	for (oitor = ENCCommon::objectDisplaySettings.begin(); oitor != ENCCommon::objectDisplaySettings.end(); oitor++)
	{
		t = "\t";
		t.append(_bstr_t((*oitor).first));
		t.append("\t");
		(*oitor).second ? t.append("1\n") : t.append("0\n");
		ofs.write(t.c_str(), t.size());
	}

	t = "OBJECT_SHOW_SETTING_END\n";
	ofs.write(t.c_str(), t.size());

	t = "OBJECT_SHOW_SETTING_S101_BEGIN\n";
	ofs.write(t.c_str(), t.size());

	t = "OBJECT_SHOW_SETTING_S101_END\n";
	ofs.write(t.c_str(), t.size());

	ofs.close();
}

void CGISViewerApp::MapRefresh()
{
	if (pView)
	{
		pView->MapRefresh();
	}
}

void CGISViewerApp::OnButtonDeleteMeasurement()
{
	pView->m_vecCurMeasureArea.clear( );
	pView->m_vectorCurrentDistance.clear();
	pView->m_vecMeasureArea.clear();
	pView->m_vectorDistance.clear();

	pView->Invalidate();
}

void CGISViewerApp::SetRibbonMenu()
{
	CMFCRibbonBar* pRibbonBar = ((CMainFrame*)m_pMainWnd)->GetRibbonBar();
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
}

void CGISViewerApp::OnBtnTdsDlg()
{
	CDialogTDSDataset dlg(*pView->m_pGisLib->GetLayerManager()->pPortrayalCatalogues->begin());
	dlg.m_pView = pView;
	dlg.DoModal();
}

void CGISViewerApp::SettingFcPcSvg()
{

} 
void CGISViewerApp::OnUpdateUsermodeButton(CCmdUI *pCmdUI)
{
	if (userMode) 
	{
		pCmdUI->SetCheck(1);
		pCmdUI->SetText(L"Developer Mode"); 
	}
	else
	{
		pCmdUI->SetCheck(0);
		pCmdUI->SetText(L"User Mode"); 
	}

}

void CGISViewerApp::OnUsermodeButton()
{
	if (userMode)
	{
		userMode = false;
		ENCCommon::m_UserMode = ENCCommon::User_Mode;
	}
	else
	{
		userMode = true;
		ENCCommon::m_UserMode = ENCCommon::Developer_Mode;
	}


	if (CGISViewerView::LogList.size() != 0)
	{
		CDialogDockLogger::m_ListLogger.ShowWindow(FALSE);
		CDialogDockLogger::m_ListLogger.DeleteAllItems();  
		CString comboBox;
		int nIndex;

		nIndex = CDialogDockLogger::m_ComboLogType.GetCurSel();
		CDialogDockLogger::m_ComboLogType.GetLBText(nIndex, comboBox); 


		for (unsigned i = 0; i < CGISViewerView::LogList.size(); i++)
		{
			ENCCommon::UserMode Mode = CGISViewerView::LogList[i].userMode;

			if (Mode == ENCCommon::m_UserMode || Mode == ENCCommon::User_Developer_Mode) 
			{
				if (comboBox == "ALL")
				{
					theApp.m_DockablePaneLogger.AppendList(CGISViewerView::LogList[i].LogContent); 
				}
				else if (comboBox == "INFO"&&CGISViewerView::LogList[i].LogType == KRS_MSG_INFO)
				{
					theApp.m_DockablePaneLogger.AppendList(CGISViewerView::LogList[i].LogContent); 
				}
				else if (comboBox == "ERROR"&&CGISViewerView::LogList[i].LogType == KRS_MSG_ERROR)
				{
					theApp.m_DockablePaneLogger.AppendList(CGISViewerView::LogList[i].LogContent); 
				}
				else if (comboBox == "WARNING"&&CGISViewerView::LogList[i].LogType == KRS_MSG_WARNING)
				{
					theApp.m_DockablePaneLogger.AppendList(CGISViewerView::LogList[i].LogContent); 
				}
			}
			else
			{

			}
		}

		CDialogDockLogger::m_ListLogger.ShowWindow(TRUE);
	}
	else
	{
		return;
	}

}

CDockablePaneAttributeList& CGISViewerApp::GetDockFeatureInformationList()
{
	return m_DockablePaneAttributeList;
}

bool CGISViewerApp::IsViewerMode()
{
	return viewerMode == true;
}

bool CGISViewerApp::IsEditingMode()
{
	return viewerMode == false;
}

void CGISViewerApp::InitStartingLocation()
{
	CRect rect;
	pView->GetClientRect(rect);

	CString strScale = L"10000000";
	CString strMox = L"126.5";
	CString strMoy = L"36.5";

	CStdioFile file;
	if (file.Open(_T("..\\ProgramData\\data\\init.txt"), CFile::modeRead))
	{
		file.ReadString(strScale);
		file.ReadString(strMox);
		file.ReadString(strMoy);
		file.Close();
	}

	double scale = _wtof(strScale);
	if (scale < 1000)
	{
		scale = 1000;
	}

	double mox = _wtof(strMox);
	double moy = _wtof(strMoy);

	pView->m_pGisLib->SetScale((int)scale);
	pView->m_pGisLib->Projection(&mox, &moy);
	pView->m_pGisLib->MoveMap(rect.Width() / 2, rect.Height() / 2, mox, moy);
	pView->m_pGisLib->AdjustScreenMap();
}

void CGISViewerApp::PC_FCPathSetting() 
{
	CStdioFile file; 
	if (file.Open(_T("..\\ProgramData\\data\\BasicFilePath.txt"), CFile::modeRead))
	{
		CString FCstart;
		file.ReadString(FCstart);
		std::vector<CString> content;
		try
		{
			if (FCstart.Compare(L"PC/FC") == 0)
			{
				CString value;
				while (file.ReadString(value))
				{
					content.push_back(value);
				}

				for (unsigned i = 0; i < content.size(); i++)
				{
					if (i % 2 == 0)
					{
						BasicFile  basicfilepath;
						basicfilepath.Set_BasicFile(content[i], content[i + 1]);
						BasicFilePath.push_back(basicfilepath);
					}
				}
			}
			file.Close();
		}
		catch (exception e)
		{
			AfxMessageBox(L"오류발생");
		}
	}
	else 
	{
		BasicFile S_101;
		S_101.Set_BasicFile(L"..\\ProgramData\\xml\\S-101_FC.xml"
			, L"..\\ProgramData\\S101_Portrayal\\");
		BasicFilePath.push_back(S_101); 

		BasicFile S_102;
		S_102.Set_BasicFile(L"..\\ProgramData\\xml\\S-102 FC.xml"
			, L"..\\ProgramData\\S102_Portrayal\\");
		BasicFilePath.push_back(S_102); 

		BasicFile S_111;
		S_111.Set_BasicFile(L"..\\ProgramData\\xml\\S-111 FC.xml"
			, L"..\\ProgramData\\S111_Portrayal\\");
		BasicFilePath.push_back(S_111); 

		BasicFile S_122;
		S_122.Set_BasicFile(L"..\\ProgramData\\xml\\S-122_FC.xml"
			, L"..\\ProgramData\\S122_Portrayal\\");
		BasicFilePath.push_back(S_122); 

		BasicFile S_123;
		S_123.Set_BasicFile(L"..\\ProgramData\\xml\\S-123_FC.xml"
			, L"..\\ProgramData\\S123_Portrayal\\");
		BasicFilePath.push_back(S_123); 

		BasicFile S_124;
		S_124.Set_BasicFile(L"..\\ProgramData\\xml\\S-124_FC.xml"
			, L"..\\ProgramData\\S124_Portrayal\\");
		BasicFilePath.push_back(S_124); 

		BasicFile S_126;
		S_126.Set_BasicFile(L"..\\ProgramData\\xml\\S-126 Physical Environment_0.0.1.xml"
			, L"..\\ProgramData\\S126_Portrayal\\");
		BasicFilePath.push_back(S_126); 

		BasicFile S_127;
		S_127.Set_BasicFile(L"..\\ProgramData\\xml\\S-127_FC.xml"
			, L"..\\ProgramData\\S127_Portrayal\\");
		BasicFilePath.push_back(S_127); 

		BasicFile S_128;
		S_128.Set_BasicFile(L"..\\ProgramData\\xml\\Feature Catalogue for S-128 ENCs_0.1.4.xml"
			, L"..\\ProgramData\\S128_Portrayal\\");
		BasicFilePath.push_back(S_128); 

		BasicFile S_129;
		S_129.Set_BasicFile(L"..\\ProgramData\\xml\\S-129_FC.xml"
			, L"..\\ProgramData\\S129_Portrayal\\");
		BasicFilePath.push_back(S_129); 

		BasicFile S_412;
		S_412.Set_BasicFile(L"..\\ProgramData\\xml\\S-412_FC.xml"
			, L"..\\ProgramData\\S412_Portrayal\\");
		BasicFilePath.push_back(S_412); 

		BasicFile S_413;
		S_413.Set_BasicFile(L"..\\ProgramData\\xml\\S-413_Draft.xml"
			, L"..\\ProgramData\\S413_Portrayal\\");
		BasicFilePath.push_back(S_413); 

		BasicFile S_421;
		S_421.Set_BasicFile(L"..\\ProgramData\\xml\\S-421 Route information FC(0.1).xml"
			, L"..\\ProgramData\\S421_Portrayal\\");
		BasicFilePath.push_back(S_421);
	}
}


void CGISViewerApp::BasicFileSetting()
{ 
	if (!LayerManager::pPortrayalCatalogues) 
	{
		LayerManager::pS100Catalogs = new std::vector<Catalog*>();
		LayerManager::pPortrayalCatalogues = new std::vector<PortrayalCatalogue*>();
		
		LayerManager::hash_FC = new std::unordered_map<std::wstring, Catalog*>();
		LayerManager::hash_PC = new std::unordered_map<std::wstring, PortrayalCatalogue*>();

		for (unsigned i = 0; i < BasicFilePath.size(); i++)
		{  
			auto fc = LayerManager::AddS100FC(BasicFilePath[i].Get_FcPath());
			if (GetColorTable()!=L"") 
			{
				auto pc = LayerManager::AddS100PC(fc, BasicFilePath[i].Get_PortrayalPath(),GetColorTable());
				pc->CreatePatternImages(gisLib->D2.pD2Factory, gisLib->D2.pImagingFactory, gisLib->D2.D2D1StrokeStyleGroup.at(0));
				pc->CreateLineImages(gisLib->D2.pD2Factory, gisLib->D2.pImagingFactory, gisLib->D2.D2D1StrokeStyleGroup.at(0));
			}
			else
			{
				auto pc = LayerManager::AddS100PC(fc, BasicFilePath[i].Get_PortrayalPath());
				pc->CreatePatternImages(gisLib->D2.pD2Factory, gisLib->D2.pImagingFactory, gisLib->D2.D2D1StrokeStyleGroup.at(0));
				pc->CreateLineImages(gisLib->D2.pD2Factory, gisLib->D2.pImagingFactory, gisLib->D2.D2D1StrokeStyleGroup.at(0));
			}
			
		}
		KRS_MSG_PROCESS::SendMessageToTargetWindow(KRS_MSG_INFO, L"FC/PC/SVG Setting completing", KRS_MSG_PROCESS::User_Developer_Mode, KRS_MSG_PROCESS::FC);
	}
}

std::wstring CGISViewerApp::GetColorTable()
{
	if (ENCCommon::m_eColorTable == ENCCommon::Day)
	{
		return L"Day";
	}
	else if (ENCCommon::m_eColorTable == ENCCommon::Dusk)
	{
		return L"Dusk";
	}
	else if (ENCCommon::m_eColorTable == ENCCommon::Night)
	{
		return L"Night";
	}
	else
	{
		return L"";
	}
}

void CGISViewerApp::InitCatalogSelectionDialog()
{
#ifndef TILE_MAP
	gisLib->GetLayerManager()->GetSelectedCatalogIndex = [](CString filepath = nullptr)
	{
		CT2CA pszConvertedAnsiString(filepath);
		std::string s(pszConvertedAnsiString);
		int findcount = s.find_last_of("\\");
		string fileptahValue = s.substr(findcount + 1, s.length());

		CDialogExCatalogSelect::OpenFileMode = true;
		CDialogExCatalogSelect dlg;

		dlg.m_fileName = CString(fileptahValue.c_str());//선택한 data 파일의 경로

		int result = dlg.DoModal();

		if (result == IDOK) 
		{
			return dlg.m_selectedIndex;
		}
		else
		{
			return -1;
		}
	};
#else
	gisLib->GetLayerManager()->GetSelectedCatalogIndex = [](CString filepath = nullptr) { return 0; };
#endif
}