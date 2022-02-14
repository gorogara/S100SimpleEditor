#pragma once
class CGeoObject;
class CAttributes;

class CGeoObjectMap
{
public:
enum Types{
	COLLECTION = 1,
	GEO,
	META,
	CARTOGRAPHIC
};

enum AttributeType{ 
	NORMAL =1, 
	MUST, 
	DELETED, 
	OPTION 
};

enum Geometric_type{
	POINT1 = 0x01,
	LINE1 = 0x02,
	AREA1 = 0x04
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
	Line12,
	Line13,		
	Line14
};
enum LINE1{
	Acronym,
	Code,
	type,
	Project
};
public:
	CGeoObjectMap();
	virtual~CGeoObjectMap();

private:
	CMap<int, int&, CGeoObject*, CGeoObject*&> aGetCode;
	CMap<CString, LPCTSTR, CGeoObject*, CGeoObject*&> aGetName;

public:
	void Add(CGeoObject* tempGeoObject);
	BOOL ReadFileCheck(CString path);
	BOOL ReadFile(CString path);
	CGeoObject* GetAt(int code);
	CGeoObject* GetAt(CString name);
	void GetAttributeSet(int index,CString strBuffer,CGeoObject *tempGeoObject);
	int GetGeometricType(CString strBuffer);
	void GetTokenize(CString strBuffer,CGeoObject *tempGeoObject);
	int GetSize();
	CGeoObject* GetObjectFromAcronym(CString acronym);
	CGeoObject* GetObjectFromCode(int code);
	int GetCodeFromAcronym(CString acronym);
	CString GetAcronymFromCode(int code);
	CString GetDiscriptionFromCode(int code);


};

