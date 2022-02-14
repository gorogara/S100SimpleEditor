#pragma once
#include <string>
#include <list>
#include <unordered_map>

using namespace std;

class Tag
{
public:
	Tag();
	Tag(Tag *parent);

private:
	std::wstring m_name;
	std::wstring m_value;
	Tag *pParent = nullptr;
	list<Tag*> m_child;
	unordered_map<std::wstring, std::wstring> m_attribute;

public:
	void Setname(std::wstring value);
	std::wstring Getname();

	void Setvalue(std::wstring value);
	std::wstring Getvalue();

	void SetParent(Tag* value);
	Tag* GetParent();

	void SetChild(list<Tag*> value);
	void SetChild(Tag* value);
	list<Tag*> GetChild();

	void SetAttribute(unordered_map<std::wstring, std::wstring> value);
	void SetAttribute(std::wstring key, std::wstring value);
	unordered_map<std::wstring, std::wstring> GetAttribute();

	void AddAtribute(wchar_t* str, Tag data);
};