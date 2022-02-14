#pragma once

#include <string>

namespace std
{
#ifdef UNICODE
	typedef std::wstring                  tstring;
#else
	typedef std::string                   tstring;
#endif
}

using namespace std;

class TStringClass
{
public:
	static std::string formatA(const char* pszFormat, ...);
	static std::wstring formatW(const wchar_t* pszFormat, ...);
	static std::string& replaceA(std::string& strContext, const char* pszTarget, const char* pszReplace);
	static std::wstring& replaceW(std::wstring& strContext, const wchar_t* pszTarget, const wchar_t* pszReplace);
	static tstring& makeLowerT(tstring& strContext);
	static tstring& trimLeftT(tstring& strContext);
	static tstring& trimRightT(tstring& strContext);
	static tstring& trimT(tstring& strContext);
	static tstring tokenizeT(tstring& strContext, int& nOffset);
	static tstring tokenizeT(tstring& strContext, tstring strDelemeter, int& nOffset);
};

