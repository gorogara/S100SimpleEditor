#pragma once

#include <initguid.h>
#include <shldisp.h>
#include <shlguid.h>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

class CPGEnumString : public IEnumString
{
public:
	CPGEnumString();
	CPGEnumString(const std::list<std::wstring>& asList);
	CPGEnumString(const std::vector<std::wstring>& asList);
	virtual ~CPGEnumString();

private:
	std::list<std::wstring> m_asList;
	ULONG m_nCurrentElement;
	LONG m_cRef;

public: 
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject); 
	HRESULT STDMETHODCALLTYPE Clone(IEnumString **ppenum);
	HRESULT STDMETHODCALLTYPE Next(ULONG celt, LPOLESTR *rgelt, ULONG *pceltFetched);
	HRESULT STDMETHODCALLTYPE Reset();
	HRESULT STDMETHODCALLTYPE Skip(ULONG celt); 
	HRESULT STDMETHODCALLTYPE AddItem(std::wstring lpszItem);
	HRESULT STDMETHODCALLTYPE AddItem(LPCWSTR lpszItem);
	HRESULT STDMETHODCALLTYPE SetList(const std::vector<std::wstring>& asList);
	HRESULT STDMETHODCALLTYPE SetList(const std::list<std::wstring>& asList);
	HRESULT STDMETHODCALLTYPE RemoveList();
};