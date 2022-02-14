// DialogExMovePointDegree.cpp : ���� �����Դϴ�. 

#include "stdafx.h"
#include "GISViewer.h"
#include "DialogExMovePointDegree.h"
#include "afxdialogex.h"

#include "LatLonUtility\\LatLonUtility.h"

#include <regex>
#include <string>
using namespace LatLonUtility;

IMPLEMENT_DYNAMIC(CDialogExMovePointDegree, CDialogEx)

CDialogExMovePointDegree::CDialogExMovePointDegree(CWnd* pParent )
	: CDialogEx(CDialogExMovePointDegree::IDD, pParent)
{
	bLat = false;
	bLon = false;
	lon = 0;
	lat = 0;
}

CDialogExMovePointDegree::~CDialogExMovePointDegree()
{
}

void CDialogExMovePointDegree::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LAT, m_EditLat);
	DDX_Control(pDX, IDC_EDIT_LON, m_EditLon);
}


BEGIN_MESSAGE_MAP(CDialogExMovePointDegree, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogExMovePointDegree::OnBnClickedOk)
	ON_EN_SETFOCUS(IDC_EDIT_LAT, &CDialogExMovePointDegree::OnEnSetfocusEditLat)
	ON_EN_KILLFOCUS(IDC_EDIT_LAT, &CDialogExMovePointDegree::OnEnKillfocusEditLat)
	ON_EN_KILLFOCUS(IDC_EDIT_LON, &CDialogExMovePointDegree::OnEnKillfocusEditLon)
END_MESSAGE_MAP()  
void CDialogExMovePointDegree::OnBnClickedOk()
{
	CString strLat, strLon;
	m_EditLat.GetWindowTextW(strLat);
	m_EditLon.GetWindowTextW(strLon);
	std::wstring wLat = strLat;
	std::wstring wLon = strLon;

	if (!CheckInput(wLat, wLon)) return;
	if (!SetMemberData(wLat, wLon)) return;

	CDialogEx::OnOK();
} 
bool CDialogExMovePointDegree::CheckInput(std::wstring& _lat, std::wstring& _lon)
{
	if (!CheckEmpty(_lat, _lon)) return false;
	if (!CheckForm(_lat, _lon)) return false;

	return true;
} 
bool CDialogExMovePointDegree::SetMemberData(std::wstring& _lat, std::wstring& _lon)
{
	double dLat = GetDegree(_lat);
	double dLon = GetDegree(_lon);

	if ((dLat > 90.0) || (dLat < -90.0) || (dLon < -180.) || (dLon > 180.))
	{
		AfxMessageBox(_T("�Է� ������ �ʰ��Ͽ����ϴ�.\n���� : -90 ~ 90\n�浵 : -180 ~ 180"));
		return false;
	}

	lat = dLat;
	lon = dLon;

	return true;
}

BOOL CDialogExMovePointDegree::OnInitDialog()
{
	CDialogEx::OnInitDialog(); 
	m_EditLat.SetCueBanner(_T("��-��-��N ���·� �Է��ϼ���."), TRUE);
	m_EditLon.SetCueBanner(_T("��-��-��E ���·� �Է��ϼ���."), TRUE);

	return TRUE;  
}


void CDialogExMovePointDegree::OnEnSetfocusEditLat()
{ 
}

bool CDialogExMovePointDegree::CheckEmpty(const std::wstring& _lat, const std::wstring& _lon) const
{
	if (_lat.empty() || _lon.empty())
	{
		AfxMessageBox(_T("����(Lat)�� �浵(Lon)�� ��� �Է��ϼ���."));
		return false;
	}

	return true;
}

#pragma warning(disable:4129)
bool CDialogExMovePointDegree::CheckForm(const std::wstring& _lat, const std::wstring& _lon) const
{
	std::wregex rx_D(L"^\\s*[+-]?\\s*\\d+\\.?\\d*\\s*$"); 
	std::wregex rx_DM(L"^\\s*[+-]?\\s*\\d+\\.?\\d*\\s*\\/\\s*\\d+\\.?\\d*\\s*$"); 
	std::wregex rx_DMS(L"^\\s*[+-]?\\s*\\d+\\.?\\d*\\s*\\/\\s*\\d+\\.?\\d*\\s*\\/\\s*\\d+\\.?\\d*\\s*$"); 
	std::wregex rx_D1(L"s*[+-]?\\s*\\d+\\.?\\d*\\s*[�ƨ�]{1}\\s*"); 
	std::wregex rx_DM1(L"\\s*[+-]?\\s*\\d+\\.?\\d*\\s*[�ƨ�]{1}\\s*\\d+\\.?\\d*\\s*\'\\s*"); 
	std::wregex rx_DMS1(L"\\s*[+-]?\\s*\\d+\\.?\\d*\\s*[�ƨ�]{1}\\s*\\d+\\.?\\d*\\s*'\\s*\\d+\\.?\\d*\\s*[\"\\��]{1}\\s*"); 

	if (!((std::regex_match(_lat, rx_D) || std::regex_match(_lat, rx_DM) || std::regex_match(_lat, rx_DMS) || 
		std::regex_match(_lat, rx_D1) || std::regex_match(_lat, rx_DM1) || std::regex_match(_lat, rx_DMS1))))
	{
		AfxMessageBox(_T("��/��/�� ���·� �Է��ϼ���.\n��1: 120/23/10.267\n��2: 120/34.56\n��3: 120.345"));
		return false;
	}

	if (!((std::regex_match(_lon, rx_D) || std::regex_match(_lon, rx_DM) || std::regex_match(_lon, rx_DMS) ||
		std::regex_match(_lon, rx_D1) || std::regex_match(_lon, rx_DM1) || std::regex_match(_lon, rx_DMS1))))
	{
		AfxMessageBox(_T("��/��/�� ���·� �Է��ϼ���.\n��1: 120/23/10.267\n��2: 120/34.56\n��3: 120.345"));
		return false;
	} 

	return true;
}

#pragma warning(disable:4996)
double CDialogExMovePointDegree::GetDegree(const std::wstring& _str) const
{
	return LatLonUtility::GetDegree(_str);

	double deg = 0;
	double min = 0;
	double sec = 0;

	std::wregex rx_D(L"^\\s*[+-]?\\s*\\d+\.?\\d*\\s*$"); 
	std::wregex rx_DM(L"^\\s*[+-]?\\s*\\d+.?\\d*\\s*\/\\s*\\d+.?\\d*$\\s*$"); 
	std::wregex rx_DMS(L"^\\s*[+-]?\\s*\\d+.?\\d*\\s*\/\\s*\\d+.?\\d*$\\s*\/\\s*\\d+.?\\d*$\\s*$");

	wchar_t* buff = nullptr;

	if (std::regex_match(_str, rx_D))
	{
		deg = std::stod(_str.c_str());
	}
	else if (std::regex_match(_str, rx_DM))
	{
		buff = wcstok((wchar_t*)(&_str[0]), L"\/");
		deg = std::stod(buff);
		buff = wcstok(nullptr, L"\/");
		min = std::stod(buff);
	}
	else if (std::regex_match(_str, rx_DMS))
	{
		buff = wcstok((wchar_t*)(&_str[0]), L"\/");
		deg = std::stod(buff);
		buff = wcstok(nullptr, L"\/");
		min = std::stod(buff);
		buff = wcstok(nullptr, L"\/");
		sec = std::stod(buff);
	}

	return DMStoDegree(deg, min, sec);
}

void CDialogExMovePointDegree::OnEnKillfocusEditLat()
{

}


void CDialogExMovePointDegree::OnEnKillfocusEditLon()
{

}


void CDialogExMovePointDegree::SplitCoordinates()
{

}