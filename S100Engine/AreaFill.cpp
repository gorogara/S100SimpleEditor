#include "stdafx.h"
#include "AreaFill.h"

#include <vector>
#include <string>
#include <iostream>
AreaFill::AreaFill()
{
	v1_x = 0;
	v1_y = 0;
	v2_x = 0;
	v2_y = 0;

}


AreaFill::~AreaFill()
{

}

bool AreaFill::Read(std::wstring path)
{
	try
	{
		initializeCOM();

		IXMLDOMDocumentPtr pDoc = NULL;
		VARIANT_BOOL bBool;
		IXMLDOMNodePtr pNode;

		pDoc.CreateInstance(__uuidof(DOMDocument));
		pDoc->load((_variant_t)path.c_str(), &bBool); 
		_areaCRS = getNodeValue(pDoc, L"//symbolFill//areaCRS");
		_symbolReference = getNodeAttribute(pDoc, L"//symbolFill//symbol");
		_name = _symbolReference.substr(0, _symbolReference.size() - 1);

		v1_x = (float)_wtof(getNodeValue(pDoc, L"//symbolFill//v1//x").c_str());
		v1_y = (float)_wtof(getNodeValue(pDoc, L"//symbolFill//v1//y").c_str());
		v2_x = (float)_wtof(getNodeValue(pDoc, L"//symbolFill//v2//x").c_str());
		v2_y = (float)_wtof(getNodeValue(pDoc, L"//symbolFill//v2//y").c_str());
	}
	catch (exception ex)
	{
		return false;
	}
	return true;
}

bool AreaFill::ReadByPugi(std::wstring path)
{
	try 
	{
		initializeCOM();
		pugi::xml_document doc;
		doc.load_file(path.c_str());

		auto list = doc.child("symbolFill");
		for (auto instruction= list.first_child(); instruction; instruction= instruction.next_sibling())
		{
			auto instructionName = instruction.name();
			if (!strcmp(instructionName,"areaCRS"))
			{
				_areaCRS =pugi::as_wide(instruction.child_value());
			}
			else if (!strcmp(instructionName, "symbol"))
			{
				_symbolReference = pugi::as_wide(instruction.child_value());
				_name= _symbolReference.substr(0, _symbolReference.size() - 1);
			}
			else if (!strcmp(instructionName, "v1"))
			{
				v1_x =stof(instruction.child("x").child_value());
				v1_y = stof(instruction.child("y").child_value());
			}
			else if (!strcmp(instructionName, "v2"))
			{
				v2_x = stof(instruction.child("x").child_value());
				v2_y = stof(instruction.child("y").child_value());
			}
		}	
	}
	catch (exception e)
	{
		return false;
	}
	return true;
}  
bool AreaFill::initializeCOM() {
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
	CoInitialize(NULL);
#endif
	return true;
}

wstring AreaFill::getNodeValue(IXMLDOMDocumentPtr &pDoc, BSTR selectSingleNode)
{
	IXMLDOMNodePtr pNode;
	wstring wsResult = _T("");
	BSTR bszResult = _T("");
	
	auto result = pDoc->selectSingleNode(selectSingleNode, &pNode);

	if (S_OK == result)
	{
		pNode->get_text(&bszResult);

		wsResult.append((wstring)bszResult);
		return wsResult;
	}

	return L"";
}

wstring AreaFill::getNodeValue(pugi::xml_node node)
{
	return L"";
}

wstring AreaFill::getNodeAttribute(IXMLDOMDocumentPtr &pDoc, BSTR selectSingleNode)
{
	IXMLDOMNodePtr pNode;

	wstring wsResult = _T("");
	BSTR bszResult = _T("");
	auto result = pDoc->selectSingleNode(selectSingleNode, &pNode);

	if (S_OK == result)
	{
		VARIANT var;
		((IXMLDOMElementPtr)pNode)->getAttribute(_T("reference"), &var);

		wsResult.append((wstring)var.bstrVal);
		return wsResult;
	}

	return L"";
}
wstring AreaFill::getNodeAttribute(pugi::xml_node node) 
{
	return L"";
}