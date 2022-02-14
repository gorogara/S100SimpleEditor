#pragma once

#include "SymbolParameter.h"
class CGeoObjectMap;
class CAttributeMap;
class CColorMap;
class CGeoObject;
class CAttribute;
class CSymbol;


typedef struct _Range 
{
	int	    Start;
	int 	End;
}Range;

typedef struct _CAttributeFindStruct
{
	unsigned *m_code;
	CString m_value;
}CAttributeFindStruct;

typedef struct _CObjectFindStruct
{
	unsigned m_objectCode;
	CList<CAttributeFindStruct> m_attrList;
}CObjectFindStruct;

class CSymbolMap
{
public:
	enum Field5_Type
	{
		type_S,
		type_O
	};
	enum Field6_Type
	{
		type_STANDARD = 0,
		type_OTHER,
		type_DISPLAYBASE,
		type_MARINERS_STANDARD,
		type_MARINERS_OTHER
	};
public:
	CSymbolMap();
	virtual ~CSymbolMap();

public:
	CGeoObjectMap *m_pGeoObjectMap;
	CAttributeMap *m_pAttributeMap;
	CSymbol *tempSymbol;
	CGeoObjectMap *p_object;
	CAttributeMap *p_attribute;
	CColorMap *p_color;
	Range *p_Range;
	int m_numSymbol;

	CString ErrorString;     

	CMap<int, int&, Range*, Range*&> arange;  

public:

	BOOL ReadFile(CString path);
	BOOL ReadFileCheck(CGeoObjectMap *object,CAttributeMap *attribute,CColorMap *color,CString path);
	int GetArrayTotalCount(CString path);
	BOOL Field1Tokenliz(CString resToken,int ArrayCnt);
	BOOL Field2Tokenliz(CString resToken,int ArrayCnt);
	BOOL Field3Tokenliz(CString resToken,int ArrayCnt);
	BOOL Field4Tokenliz(CString resToken,int ArrayCnt);
	BOOL Field5Tokenliz(CString resToken,int ArrayCnt);
	BOOL Field6Tokenliz(CString resToken,int ArrayCnt);
	BOOL Field7Tokenliz(CString resToken,int ArrayCnt);
	
	BOOL SYTokenliz(CString str,int ArrayCnt,int IndexCnt);
	BOOL TETokenliz(CString str,int ArrayCnt,int IndexCnt);
	BOOL TXTokenliz(CString str,int ArrayCnt,int IndexCnt);
	BOOL LSTokenliz(CString str,int ArrayCnt,int IndexCnt);
	BOOL LCTokenliz(CString str,int ArrayCnt,int IndexCnt);
	BOOL ACTokenliz(CString str,int ArrayCnt,int IndexCnt);
	BOOL APTokenliz(CString str,int ArrayCnt,int IndexCnt);
	BOOL CSTokenliz(CString str,int ArrayCnt,int IndexCnt);
	
	BOOL GetRange(int max);
	CSymbol* GetSymbole(int index);
	void Add(int Code,Range *p_Range);
	Range* GetAt(int Code);
	int GetIndexNumber(CObjectFindStruct* CObjectFindStruct);
	int GetIndexNumber(CString name);

};