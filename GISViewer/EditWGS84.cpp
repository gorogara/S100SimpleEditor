#include "stdafx.h"
#include "EditWGS84.h"

#include "LatLonUtility\\LatLonUtility.h"

#include <regex>
CEditWGS84::CEditWGS84()
{
}


CEditWGS84::~CEditWGS84()
{
}


BOOL CEditWGS84::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{ 

	return CEdit::Create(dwStyle, rect, pParentWnd, nID);
}


BOOL CEditWGS84::PreCreateWindow(CREATESTRUCT& cs)
{ 

	return CEdit::PreCreateWindow(cs);
}


double CEditWGS84::GetLon()
{
	bool east = false;

	if (cstr.FindOneOf(_T("wW")) >= 0) {
		east = true;
	}

	CString resToken;
	CString lon;
	int curPosLon = 0;
	int curPosPos = 0;
	cstr.Tokenize(_T("NSns"), curPosPos);
	lon = cstr.Tokenize(_T("EWew"), curPosPos);
	lon.Trim(_T(" ,"));

	double lonDeg = 0;
	double lonMin = 0;
	double lonSec = 0;
	int cntLon = 0;

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
			return 0;
		}
		resToken = lon.Tokenize(_T("-"), curPosLon);
		cntLon++;
	}

	double longitude = LatLonUtility::DMStoDegree(lonDeg, lonMin, lonSec);
	if (east)
	{
		longitude *= -1;
	}

	return longitude;
}


double CEditWGS84::GetLat()
{
	bool north = false;
	bool east = false;

	if (cstr.FindOneOf(_T("nN")) >= 0) {
		north = true;
	}

	CString resToken;
	CString lat;
	int curPosLat = 0;
	int curPosPos = 0;
	lat = cstr.Tokenize(_T("NSns"), curPosPos);
	lat.Trim(_T(" ,"));

	double latDeg = 0;
	double latMin = 0;
	double latSec = 0;
	int cntLat = 0;

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
			return 0;
		}
		resToken = lat.Tokenize(_T("-"), curPosLat);
		cntLat++;
	}

	double latitude = LatLonUtility::DMStoDegree(latDeg, latMin, latSec);
	if (!north)
	{
		latitude *= -1;
	}

	return latitude;
}


#pragma warning(disable:4129)
bool CEditWGS84::CheckForm()
{  

	std::wregex rx(L"^\\s*\\d+\\.?\\d*(\\s*\\-\\s*\\d+\\.?\\d*\\s*){0,2}\\s*[NSns]{1}\\s*\,?\\s*\\d+\\.?\\d*(\\s*\\-\\s*\\d+\\.?\\d*\\s*){0,2}\\s*[EWew]{1}\\s*$");
	std::wstring wstr = cstr;

	if (!std::regex_match(wstr, rx))
	{
		AfxMessageBox(_T("아래와 같은 형태로 입력하세요.\n34-13-32.4N, 126-36-40.1E"));
		return false;
	}

	return true;
}


bool CEditWGS84::CheckValue()
{
	if (!CheckForm())
	{
		return false;
	}
	
	double lat = GetLat();

	if ((lat < -85) || (lat > 85))
	{
		AfxMessageBox(_T("위도의 범위는 -85º ~ +85º 입니다."));
		return false;
	}

	return true;
}BEGIN_MESSAGE_MAP(CEditWGS84, CEdit)
ON_CONTROL_REFLECT(EN_CHANGE, &CEditWGS84::OnEnChange)
END_MESSAGE_MAP()


void CEditWGS84::OnEnChange()
{     
	GetWindowText(cstr);
}
