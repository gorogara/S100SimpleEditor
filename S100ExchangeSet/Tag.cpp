#include "stdafx.h"
#include "Tag.h"

Tag::Tag()
{

}

Tag::Tag(Tag *parent)
{
	SetParent(parent);
}

void Tag::Setname(std::wstring value)
{
	m_name = value;
}

std::wstring Tag::Getname()
{
	return m_name;
}

void Tag::Setvalue(std::wstring value)
{
	m_value = value;
}

std::wstring Tag::Getvalue()
{
	return m_value;
}

void Tag::SetParent(Tag* value) 
{
	pParent = value;
}

Tag* Tag::GetParent() 
{
	return pParent;
}

void Tag::SetChild(list<Tag*> value) 
{
	m_child = value;
}
void Tag::SetChild(Tag* value)
{
	m_child.emplace_back(value);
}

list<Tag*> Tag::GetChild()
{
	return m_child;
}

void Tag::SetAttribute(unordered_map<std::wstring, std::wstring> value)
{
	m_attribute = value;
}

void Tag::SetAttribute(std::wstring key, std::wstring value)
{
	m_attribute.insert({key,value});
}

unordered_map<std::wstring, std::wstring> Tag::GetAttribute()
{
	return m_attribute;
}

