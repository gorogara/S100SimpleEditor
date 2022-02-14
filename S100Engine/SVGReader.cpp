#include "stdafx.h"
#include "SVGReader.h"
#include "Rectangle.h"
#include <pugixml.hpp> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace simpleUse
{ 
	vector<CString> Split(CString _data, char parsingChar)
	{
		vector<CString> result;

		CString data = _data;
		while (data.GetLength() != 0)
		{
			data.TrimLeft(parsingChar);
			int nFind2 = data.Find(parsingChar);
			if (nFind2 == -1)
			{
				result.push_back(data);
				break;
			}
			CString strNum = data.Mid(0, nFind2);
			result.push_back(strNum);
			data = data.Mid(nFind2);
		}
		return result;
	}

	template<typename T>
	void split(const T& line, const T& separators, vector<T>& tokens)
	{
		size_t start = line.find_first_not_of(separators);
		size_t end = line.length();

		while ((start >= 0) && (start < end)) {
			size_t stop = line.find_first_of(separators, start);
			if ((stop < 0) || (stop > end)) stop = end;
			tokens.push_back(line.substr(start, stop - start));
			start = line.find_first_not_of(separators, stop + 1);
		}
	} 
	vector<CString> SplitBySpace(CString _data, int _space)
	{
		vector<CString> result;

		CString data = _data;
		for (int i = 0; i < _data.GetLength(); i += _space)
		{
			CString cs;
			for (int j = 0; j < _space; j++)
			{
				cs.AppendChar(_data[i + j]);
			}
			result.push_back(cs);
		}
		return result;
	} 
	int Conert16to10(char* ch)
	{
		int result = strtol(ch, NULL, 16);
		return result;
	} 
	char* ConvertCstringToChar(CString inCstring)
	{
		char* result;
		wchar_t *wchar_str;
		int char_str_len; 
		wchar_str = inCstring.GetBuffer(inCstring.GetLength());
		char_str_len = WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, NULL, 0, NULL, NULL); 

		result = (char*)malloc(char_str_len); 
		WideCharToMultiByte(CP_ACP, 0, wchar_str, -1, result, char_str_len, 0, 0); 
		return result;
	} 
	wstring ConvertCharToWstring(char* inChar)
	{
		std::string str = inChar;
		wstring result;

		result.assign(str.begin(), str.end());
		return result;
	} 
	char * ConvertWCtoC(wchar_t* str)
	{ 
		char* pStr = nullptr; 
		int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

		if (strSize <= 0)
		{
			OutputDebugString(_T("Failed to WideCharToMultiByte()\n"));
			return nullptr;
		} 
		pStr = new char[strSize]; 
		WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
		return pStr;
	}
}

#pragma region GetFunction                    

bool GetClass(char* attributeContent, bool& fill, wstring& colorName)
{
	wstring wsTemp = wstring(attributeContent, attributeContent + strlen(attributeContent));
	wstring temp;
	wstring wsColor;
	wstring wsFill;
	vector<wstring> wsVecTemp;

	if (wsTemp.size() == 6)
	{
		temp = wsTemp;
		wsColor = temp.substr(1, temp.size());
		wsFill = temp.substr(0, 1);
	}
	else
	{
		simpleUse::split<wstring>(wstring(attributeContent, attributeContent + strlen(attributeContent)),
			L" ",
			wsVecTemp);
		temp = wsVecTemp[wsVecTemp.size()-1].c_str();
		wsColor = temp.substr(1, temp.size());
		wsFill = temp.substr(0, 1);
	}

	if (&colorName != nullptr)
	{
		colorName = wsColor;
	}
	else
	{
		return false;
	}

	if (&fill != nullptr)
	{
		if (!wcscmp(wsFill.c_str(), L"f"))
		{
			fill = true;
			return true;
		}
		else
		{
			fill = false;
			return true;
		}
	}
	else
	{
		return false;
	}

	return false;
}

bool GetRotation(char* attributeContent, int& rotation)
{
	try
	{
		vector<wstring> wsVecTemp;
		simpleUse::split<wstring>(wstring(attributeContent, attributeContent + strlen(attributeContent)), L"rotate ()", wsVecTemp);
		rotation = _wtoi(wsVecTemp[0].c_str());
	}
	catch (exception ex)
	{
		return false;
	}
	return true;
}

bool GetStyle(char* attributeContent, double& strokeWidth, wstring& strokeDasharray, float& alpha)
{
	vector<wstring> wsVecTemp;
	simpleUse::split<wstring>(wstring(attributeContent, attributeContent + strlen(attributeContent)), L":;", wsVecTemp);
	for (int i = 0; i < (int)wsVecTemp.size(); i += 2)
	{
		const wchar_t* a = wsVecTemp[i].c_str();
		wstring sss = wsVecTemp[i + 1];
		if (!wcscmp(wsVecTemp[i].c_str(), L"stroke-width") && (&strokeWidth != nullptr))
		{
			strokeWidth = _wtof(wsVecTemp[i + 1].c_str());
			return true;
		}
		else if (!wcscmp(wsVecTemp[i].c_str(), L"stroke-dasharray") && (&strokeDasharray != nullptr))
		{
			strokeDasharray = wsVecTemp[i + 1];
			return true;
		}
		else if (!wcscmp(wsVecTemp[i].c_str(), L"fill-opacity") && (&strokeDasharray != nullptr))
		{
			alpha = _wtof(wsVecTemp[i + 1].c_str());
			return true;
		}
	}
	return false;
}

bool GetDouble(char* attributeContent, double& dataSpace)
{
	try
	{
		dataSpace = atof(attributeContent);
	}
	catch (exception ex)
	{
		return false;
	}
	return true;
}
#pragma endregion

SVGReader::SVGReader()
{
	bounding_x = 0;
	bounding_y = 0;
	bounding_width = 0;
	bounding_height = 0;

	svgBox_x = 0;
	svgBox_y = 0;
	svgBox_width = 0;
	svgBox_height = 0;
}


bool SVGReader::Open(char* path)
{                                                                                                                                                                                                                               

	return true;
}

bool SVGReader::OpenByPugi(char* path)
{
	auto document = pugi::xml_document();
	auto result = document.load_file(path);

	pugi::xml_node displayList = document.child("svg");
	if (displayList.empty())
	{
		OutputDebugString(_T("Failed to call xmlReadFile() in SVGReader::Open()\n"));
		return false;
	}

	for (pugi::xml_node instruction = displayList.first_child(); instruction; instruction=instruction.next_sibling()) 
	{
		if (instruction==nullptr)
		{
			return false;
		}

		const pugi::char_t* instructionName = instruction.name();
		if (!strcmp(instructionName,"rect"))
		{
			bool bSymbolBoxLayout = false;
			for (pugi::xml_attribute attri=instruction.first_attribute(); attri; attri=attri.next_attribute()) 
			{
				auto attriName = attri.name();
				auto attriValue = attri.value();
				if (!strcmp(attriValue, "svgBox layout")) 
				{
					bSymbolBoxLayout = true;
				}
				else if (!strcmp(attriName, "x")&& bSymbolBoxLayout)
				{
					bounding_x=stof(pugi::as_wide(attri.value()));
				}
				else if (!strcmp(attriName, "y") && bSymbolBoxLayout)
				{
					bounding_y= stof(pugi::as_wide(attri.value()));
				}
				else if (!strcmp(attriName, "height") && bSymbolBoxLayout)
				{
					bounding_height = stof(pugi::as_wide(attri.value()));
				}
				else if (!strcmp(attriName, "width") && bSymbolBoxLayout)
				{
					bounding_width = stof(pugi::as_wide(attri.value()));
				}
			}
		
		}
		else if (!strcmp(instructionName, "path"))
		{
			libS100Engine::Line* line = new libS100Engine::Line();
			vector<wstring> wsVecTemp;
			for (pugi::xml_attribute attri = instruction.first_attribute(); attri; attri = attri.next_attribute())
			{
				auto attriName = attri.name();
				auto attriValue = attri.value();
				wstring wsAttributeContent = wstring(attriValue, attriValue + strlen(attriValue));
				wsVecTemp.clear();

				if (!strcmp(attriName,"d"))
				{
					simpleUse::split<wstring>(wsAttributeContent, L" ,ML", wsVecTemp);
					line->m_points.clear();
					line->AddPoints(wsVecTemp);
				}
				else if(!strcmp(attriName,"class"))
				{
					char* value =(char*)attriValue;
					GetClass(value, line->fill, line->colorName);
				}
				else if (!strcmp(attriName,"style"))
				{
					char* value = (char*)attriValue;
					GetStyle(value, line->strokeWidth, line->strokeDasharray, line->alpha);
				}
				else if (!strcmp(attriName, "transform"))
				{
					char* value = (char*)attriValue;
					GetRotation(value, line->rotation);
				}
			}
			figures.push_back(line);
		}
		else if (!strcmp(instructionName, "circle"))
		{
			libS100Engine::Circle* circle = new libS100Engine::Circle();
			vector<wstring> wsVecTemp;

			for (pugi::xml_attribute attri = instruction.first_attribute(); attri; attri = attri.next_attribute())
			{
				auto attriName = attri.name();
				auto attriValue = attri.value();
				wstring wsAttributeContent;

				if (!strcmp(attriName, "cx"))
				{
					char * value = (char*)attriValue;
					GetDouble(value, circle->cx);
				}
				else if (!strcmp(attriName, "cy"))
				{
					char * value = (char*)attriValue;
					GetDouble(value, circle->cy);
				}
				else if (!strcmp(attriName, "r"))
				{
					char * value = (char*)attriValue;
					GetDouble(value, circle->radius);
				}
				else if (!strcmp(attriName, "class"))
				{
					char * value = (char*)attriValue;
					if (!strcmp(value, "pivotPoint layout"))
					{

					}
					else
					{
						GetClass(value, circle->fill, circle->colorName);
					}
				}
				else if (!strcmp(attriName, "style"))
				{
					char * value = (char*)attriValue;
					GetStyle(value, circle->strokeWidth, circle->strokeDasharray, circle->alpha);
				}
				else if (!strcmp(attriName, "transform"))
				{
					char * value = (char*)attriValue;
					GetRotation(value, circle->rotation);
				}
			}

			if (!wcscmp(circle->colorName.c_str(), L""))
			{
				circle->type = libS100Engine::pivotPoint;
				figures.push_back(circle);
			}
			else
			{
				figures.push_back(circle);
			}
		}

	}

	auto wPath = LibMFCUtil::ConvertCtoWC(path);
	CString cpath(wPath);
	delete[] wPath;  

	int length = cpath.GetLength();
	if (length <= 0)
	{
		return true;
	}
		
	int indexOfLastReverseSlash = cpath.ReverseFind('\\');
	if (indexOfLastReverseSlash >= 0)
	{
		int indexOfLastDot = cpath.ReverseFind('.');
		if (indexOfLastDot >= 0)
		{
			name = cpath.Mid(indexOfLastReverseSlash + 1, indexOfLastDot - indexOfLastReverseSlash - 1);
		}
	}
	return true;
}



void SVGReader::svgSet(char* path)
{                                                                                                                                                                               
}

SVGReader::SVGReader(char* path)
{
	bounding_x = 0;
	bounding_y = 0;
	bounding_width = 0;
	bounding_height = 0;

	svgBox_x = 0;
	svgBox_y = 0;
	svgBox_width = 0;
	svgBox_height = 0;

	svgSet(path);
}

SVGReader::~SVGReader()
{
	
}


void SVGReader::Close()
{
	for (int i = 0; i < (int)figures.size(); i++)
	{
		if (figures[i]!=nullptr)
		{
			delete figures[i];
			figures[i] = nullptr;
		}
	}

	figures.clear();

	for (auto i = geometry.begin(); i != geometry.end(); i++)
	{
		SafeRelease(&i->pGeometry);
	}
}


void SVGReader::CreateSVGGeometry(ID2D1Factory1* m_pDirect2dFactory)
{
	for (auto i = 0; i < (int)figures.size(); i++)
	{
		switch (figures[i]->type)
		{
		case libS100Engine::line:
			geometry.push_back(CreateSVGGeometryFromLine(m_pDirect2dFactory, (libS100Engine::Line*)figures[i]));
			break;
		case libS100Engine::circle:
			geometry.push_back(CreateSVGGeometryFromCircle((libS100Engine::Circle*)figures[i]));
			break;
		default:
			break;
		}
	}
}


SVGGeometry SVGReader::CreateSVGGeometryFromLine(ID2D1Factory1* m_pDirect2dFactory, libS100Engine::Line* line)
{
	SVGGeometry svgGeometry;

	svgGeometry.bFill = line->fill;
	svgGeometry.bStoke = !line->fill;
	svgGeometry.width = (FLOAT)line->strokeWidth;
	svgGeometry.strokeColorName = line->colorName;
	svgGeometry.fillColorName = line->colorName;
	svgGeometry.alpha = line->alpha;
	
	HRESULT hr = m_pDirect2dFactory->CreatePathGeometry(&svgGeometry.pGeometry);

	if (SUCCEEDED(hr))
	{
		ID2D1GeometrySink *pSink = nullptr;

		hr = svgGeometry.pGeometry->Open(&pSink);

		if (SUCCEEDED(hr))
		{
			pSink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);
			pSink->BeginFigure(
				D2D1::Point2F(line->m_points.begin()->x, line->m_points.begin()->y),
				D2D1_FIGURE_BEGIN_FILLED
				);

			for (auto k = line->m_points.begin() + 1; k != line->m_points.end(); k++)
			{
				pSink->AddLine(D2D1::Point2F(k->x, k->y));
			}

			pSink->EndFigure(D2D1_FIGURE_END_OPEN);

			hr = pSink->Close();

			if (!SUCCEEDED(hr))
			{
				OutputDebugString(_T("Faield to close sink\n"));
			}
		}
		else
		{
			OutputDebugString(_T("Faield to Open Sink\n"));
		}
	}
	else
	{
		OutputDebugString(_T("Failed to create geometry\n"));
	}

	return svgGeometry;
}


SVGGeometry SVGReader::CreateSVGGeometryFromCircle(libS100Engine::Circle* circle)
{
	SVGGeometry svgGeometry;

	svgGeometry.bFill = circle->fill;
	svgGeometry.bStoke = !circle->fill;
	svgGeometry.width = (FLOAT)circle->strokeWidth;
	svgGeometry.strokeColorName = circle->colorName;
	svgGeometry.fillColorName = circle->colorName;
	svgGeometry.pGeometry = nullptr;
	svgGeometry.alpha = circle->alpha;

	svgGeometry.ellipse.point.x = (FLOAT)circle->cx;
	svgGeometry.ellipse.point.y = (FLOAT)circle->cy;

	svgGeometry.ellipse.radiusX = (FLOAT)circle->radius;
	svgGeometry.ellipse.radiusY = (FLOAT)circle->radius;

	return svgGeometry;
}