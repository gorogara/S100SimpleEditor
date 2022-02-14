#include "stdafx.h"
#include "S100ColorProfile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

S100ColorProfile::S100ColorProfile()
{
}

S100ColorProfile::~S100ColorProfile()
{
}                                           

bool S100ColorProfile::OpenByPugi(char *filePath)
{
	pugi::xml_document xmldoc;
	auto result = xmldoc.load_file(filePath);
	auto colorProfileNode = xmldoc.child("colorProfile");

	if (colorProfileNode.empty())
	{
		OutputDebugString(_T("Failed to Read xml file in S100ColorProfile::Open()\n"));
		return false;
	}

	for (pugi::xml_node instruction = colorProfileNode.first_child(); instruction; instruction = instruction.next_sibling())
	{
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"colors"))
		{
			extractionColors(instruction);
		}
		else if (!strcmp(instructionName, "palette"))
		{
			extractionPalette(instruction);
		}
	}


	return true;
}

D2D1_COLOR_F S100ColorProfile::GetColor(std::wstring _paletteName, std::wstring _token)
{
	D2D1_COLOR_F resultColor = D2D1::ColorF(D2D1::ColorF::Crimson);

	for (auto i = palette.begin(); i != palette.end(); i++)
	{
		if (!i->name.compare(_paletteName))
		{
			for (auto j = i->item.begin(); j != i->item.end(); j++)
			{
				if (!j->token.compare(_token))
				{
					return D2D1::ColorF((FLOAT)(j->srgb.red / 255.0), (FLOAT)(j->srgb.green / 255.0), (FLOAT)(j->srgb.blue / 255.0));
				}
			}
		}
	}

	CString errMsg;
	errMsg.Format(_T("Invalid color name (%s)\n"), _token.c_str());
	OutputDebugString(errMsg);

	return resultColor;
}                     

void S100ColorProfile::extractionColors(pugi::xml_node node)
{ 
	for (pugi::xml_node instruction=node.first_child(); instruction; instruction =instruction.next_sibling())
	{ 
		libS100Engine::Color color;
		if (instruction == nullptr)
		{
			return;
		}
	
		for (pugi::xml_attribute attri = instruction.first_attribute(); attri; attri = attri.next_attribute())
		{
			auto attriName = attri.name();
			if (strcmp(attriName, "name"))
			{
				color.name = pugi::as_wide(attri.value()); 
			}
			else if (strcmp(attriName, "token"))
			{
				color.token= pugi::as_wide(attri.value()); 
			}
		}

		auto desctiptionName=instruction.first_child().name();
		if (!strcmp(desctiptionName,"description"))
		{
			color.desctiption =pugi::as_wide(instruction.first_child().child_value());
		}
		colors.colors.push_back(color);
	}
	
}                                               

void S100ColorProfile::extractionPalette(pugi::xml_node node)
{ 
	Palette pale;
	for (pugi::xml_attribute attri=node.first_attribute(); attri; attri=attri.next_attribute()) 
	{
		auto attriName = attri.name();
		if (!strcmp(attriName,"name"))
		{
			pale.name =pugi::as_wide(attri.value());
		}
	}

	for (pugi::xml_node instruction = node.first_child(); instruction; instruction = instruction.next_sibling())
	{
		if (node == nullptr)
		{
			return;
		}
		auto instructionName = instruction.name();
		if (!strcmp(instructionName,"item"))
		{
			libS100Engine::Item item;
			for (pugi::xml_attribute attri= instruction.first_attribute(); attri; attri=attri.next_attribute())
			{
				auto attriName = attri.name();
				if (!strcmp(attriName,"token"))
				{
					item.token = pugi::as_wide(attri.value());
				}
			}

			for (pugi::xml_node child=instruction.first_child(); child; child=child.next_sibling())
			{
				if (child != nullptr)
				{
					for (pugi::xml_node srgbchild = child.first_child(); srgbchild; srgbchild = srgbchild.next_sibling())
					{
						auto srgbchildName = srgbchild.name();
						if (!strcmp(srgbchildName, "red"))
						{
							wstring value = pugi::as_wide(srgbchild.child_value());
							if (value!=L"") 
							{
								item.srgb.red = stoi(value);
							}
						}
						else if (!strcmp(srgbchildName, "green"))
						{
							wstring value = pugi::as_wide(srgbchild.child_value());
							if (value != L"")
							{
								item.srgb.green = stoi(value);

							}
						}
						else if (!strcmp(srgbchildName, "blue"))
						{
							wstring value = pugi::as_wide(srgbchild.child_value());
							if (value != L"")
							{
								item.srgb.blue = stoi(value);
								int i = 0;
							}
							
						}
					}
				}
			}
			pale.item.push_back(item);
	
		}

		palette.push_back(pale);
	}
}


vector<CString> S100ColorProfile::Split(CString _data, char parsingChar)
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

vector<CString> S100ColorProfile::SplitBySpace(CString _data, int _space)
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

int S100ColorProfile::Conert16to10(char* ch)
{
	int result = strtol(ch, NULL, 16);
	return result;
}

char* S100ColorProfile::ConvertCstringToChar(CString inCstring)
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

CString S100ColorProfile::ConvertCharToCString(char* inChar)
{
	return (CString)inChar;
}

wstring S100ColorProfile::ConvertCtoWS(char* c)
{
	string str(c);
	return std::wstring(str.begin(), str.end()).c_str();
}

char* S100ColorProfile::ConvertWCtoC(wchar_t* str)
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