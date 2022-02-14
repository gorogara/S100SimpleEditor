#include "stdafx.h"
#include "PGEnumString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

CPGEnumString::CPGEnumString() : m_asList(), m_nCurrentElement(0), m_cRef(0)
{
}

CPGEnumString::CPGEnumString(const list<wstring>& asList) : m_asList(asList), m_nCurrentElement(0), m_cRef(0)
{
}

CPGEnumString::CPGEnumString(const vector<wstring>& asList) : m_asList(), m_nCurrentElement(0), m_cRef(0)
{
	if (asList.begin() != asList.end())
		m_asList.insert(m_asList.end(), asList.begin(), asList.end());
}

CPGEnumString::~CPGEnumString()
{
}

ULONG STDMETHODCALLTYPE CPGEnumString::AddRef()
{
	return ::InterlockedIncrement(&m_cRef);
}

ULONG STDMETHODCALLTYPE CPGEnumString::Release()
{
	ULONG nCount = 0;

	nCount = (ULONG) ::InterlockedDecrement(&m_cRef);

	if (nCount == 0)
		delete this;

	return nCount;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::QueryInterface(REFIID riid, void** ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (ppvObject != NULL)
	{
		*ppvObject = NULL;

		if (IID_IUnknown == riid)
			*ppvObject = static_cast<IUnknown*>(this);

		else if (IID_IEnumString == riid)
			*ppvObject = static_cast<IEnumString*>(this);

		if (*ppvObject != NULL)
		{
			hr = S_OK;
			((LPUNKNOWN)*ppvObject)->AddRef();
		}
	}
	else
	{
		hr = E_POINTER;
	}

	return hr;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::Clone(IEnumString **ppenum)
{
	if (!ppenum)
		return E_POINTER;

	CPGEnumString* pnew = new CPGEnumString(m_asList);

	pnew->AddRef();
	*ppenum = pnew;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::Next(ULONG celt, LPOLESTR *rgelt, ULONG *pceltFetched)
{
	HRESULT hr = S_FALSE;

	if (0 == celt)
		celt = 1;

	ULONG i = 0;
	for (i = 0; i < celt; i++)
	{

		if (m_nCurrentElement == (ULONG)m_asList.size())
			break;

		list<wstring>::iterator it = m_asList.begin();
		for (ULONG idx = 0 ; idx < m_nCurrentElement ; idx++)
			++it;

		rgelt[i] = (LPWSTR)::CoTaskMemAlloc((ULONG)sizeof(wchar_t) * (it->length() + 1));
		wcscpy_s(rgelt[i], it->length() + 1, it->c_str());

		if (pceltFetched)
			*pceltFetched++;

		m_nCurrentElement++;
	}

	if (i == celt)
		hr = S_OK;

	return hr;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::Reset()
{
	m_nCurrentElement = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::Skip(ULONG celt)
{
	m_nCurrentElement += celt;

	if (m_nCurrentElement > (ULONG)m_asList.size())
		m_nCurrentElement = 0;

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::AddItem(wstring lpszItem)
{
	if (0 != lpszItem.length())
	{
		list<wstring>::iterator it;
		it = find(m_asList.begin(), m_asList.end(), lpszItem);

		if (m_asList.end() == it)
		{
			m_asList.push_back(lpszItem);
			return S_OK;
		}
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::AddItem(LPCWSTR lpszItem)
{
	return AddItem(wstring(lpszItem));
}

HRESULT STDMETHODCALLTYPE CPGEnumString::SetList(const std::vector<std::wstring>& asList)
{
	if (asList.begin() != asList.end())
	{
		list<wstring> lTemp;
		m_asList.swap(lTemp);
		m_asList.insert(m_asList.end(), asList.begin(), asList.end());
		return S_OK;
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::SetList(const std::list<std::wstring>& asList)
{
	if (asList.begin() != asList.end())
	{
		m_asList = asList;
		return S_OK;
	}
	return E_FAIL;
}

HRESULT STDMETHODCALLTYPE CPGEnumString::RemoveList()
{
	list<wstring> vTemp;
	m_asList.swap(vTemp);

	return S_OK;
}