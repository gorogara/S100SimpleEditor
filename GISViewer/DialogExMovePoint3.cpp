// DialogExMovePoint3.cpp : 구현 파일입니다. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExMovePoint3.h"
#include "afxdialogex.h"

#include "LatLonUtility\\LatLonUtility.h"

#include <regex> 

IMPLEMENT_DYNAMIC(CDialogExMovePoint3, CDialogEx)

CDialogExMovePoint3::CDialogExMovePoint3(CWnd* pParent )
: CDialogEx(CDialogExMovePoint3::IDD, pParent), lon(0), lat(0)
{

}

CDialogExMovePoint3::~CDialogExMovePoint3()
{
}

void CDialogExMovePoint3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_POS, m_EditPos);
}


BEGIN_MESSAGE_MAP(CDialogExMovePoint3, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExMovePoint3::OnBnClickedOk)
END_MESSAGE_MAP() 


BOOL CDialogExMovePoint3::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	m_EditPos.SetCueBanner(_T("입력 예 : 34-13-32.4N, 126-36-40.1E"), TRUE);

	return TRUE;  
}

#pragma warning(disable:4129)
void CDialogExMovePoint3::OnBnClickedOk()
{
	CString str;
	m_EditPos.GetWindowText(str);
	double a, b, c;
	bool test = LatLonUtility::CheckFormWGS(std::wstring(str), a, b, c); 
	CString cstr;
	m_EditPos.GetWindowText(cstr);

	std::wregex rx(L"^\\s*\\d+\\.?\\d*(\\s*\\-\\s*\\d+\\.?\\d*\\s*){0,2}\\s*[NSns]{1}\\s*\,?\\s*\\d+\\.?\\d*(\\s*\\-\\s*\\d+\\.?\\d*\\s*){0,2}\\s*[EWew]{1}\\s*$");
	std::wstring wstr = cstr;

	if (!std::regex_match(wstr, rx))
	{
		AfxMessageBox(_T("아래와 같은 형태로 입력하세요.\n34-13-32.4N, 126-36-40.1E"));
		return;
	}

	bool north = false;
	bool east = false;

	if (cstr.FindOneOf(_T("nN")) >= 0) {
		north = true;
	}

	if (cstr.FindOneOf(_T("wW")) >= 0) {
		east = true;
	}

	CString resToken;
	CString lat;
	CString lon;
	int curPosLat = 0;
	int curPosLon = 0;
	int curPosPos = 0;
	lat = cstr.Tokenize(_T("NSns"), curPosPos);
	lon = cstr.Tokenize(_T("EWew"), curPosPos);
	lat.Trim(_T(" ,"));
	lon.Trim(_T(" ,"));

	double latDeg = 0;
	double latMin = 0;
	double latSec = 0;
	double lonDeg = 0;
	double lonMin = 0;
	double lonSec = 0;
	int cntLat = 0;
	int cntLon = 0;

	resToken = lat.Tokenize(_T("-"), curPosLat);
	while (resToken != "") {
		switch (cntLat)
		{
		case 0:
			latDeg = _wtof(resToken);
			break;
		case 1:
			latMin = _wtof(resToken);
			break;
		case 2:
			latSec = _wtof(resToken);
			break;
		default:
			AfxMessageBox(_T("좌표 변환 중 오류가 발생하였습니다."));
			return;
		}
		resToken = lat.Tokenize(_T("-"), curPosLat);
		cntLat++;
	}

	resToken = lon.Tokenize(_T("-"), curPosLon);
	while (resToken != "") {
		switch (cntLon)
		{
		case 0:
			lonDeg = _wtof(resToken);
			break;
		case 1:
			lonMin = _wtof(resToken);
			break;
		case 2:
			lonSec = _wtof(resToken);
			break;
		default:
			AfxMessageBox(_T("좌표 변환 중 오류가 발생하였습니다."));
			return;
		}
		resToken = lon.Tokenize(_T("-"), curPosLon);
		cntLon++;
	}

	this->lat = LatLonUtility::DMStoDegree(latDeg, latMin, latSec);
	this->lon = LatLonUtility::DMStoDegree(lonDeg, lonMin, lonSec);

	CDialogEx::OnOK();
}
