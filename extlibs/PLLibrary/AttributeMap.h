#pragma once
class CAttribute; 
class CAttributeMap
{
public:
enum Indication_type{
	FEATURE = 1,
	NATIONAL,
	SPATIAL,
	CARTO
};

enum Attribute_type{
	ENUMERATED = 1, 
	LIST, 
	FLOAT1, 
	INTEGER, 
	CODED_STRING, 
	FREE_TEXT 
};
enum LineCnt{
	Line1,
	Line2,
	Line3,
	Line4,
	Line5,
	Line6,
	Line7,
	Line8,
	Line9,
	Line10,
	Line11,
	Line12
};
enum LINE1{
	Acronym,
	Code,
	Indication,
	Project
};

private:
	CList<CAttribute*> m_attributs;
	CMap<int, int&, CAttribute*, CAttribute*&> aGetCode;
	CMap<CString, LPCTSTR, CAttribute*, CAttribute*&> aGetName;

public:
	CAttributeMap();
	virtual ~CAttributeMap();
	void AddAttributeToMaps(CAttribute *attribute);
	void InsertAttribute(CAttribute *attribute);
	BOOL ReadFileCheck(CString path);
	BOOL ReadFile(CString path);
	void SortListValues();
	CAttribute* GetAt(int code);
	CAttribute* GetAt(CString name);
	int GetAttributeType(char temp);
	void GetTokenize(CString strBuffer,CAttribute *tempAttribute);
	void GetLine3Tokenoze(CString strBuffer,CAttribute *tempAttribute,int count);
	CAttribute* GetAttributeFromAcronym(CString acronym);
	CAttribute* GetAttributeFromCode(int code);
	int GetCodeFromAcronym(CString acronym);
	CString GetAcronymFromCode(int code);
	CString GetDiscriptionFromCode(int code);
};

