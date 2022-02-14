#pragma once
#include <string>

namespace S100DatasetGML
{
	class S100GML_Association
	{
	public:
		S100GML_Association();
		virtual ~S100GML_Association();

	public:
		std::wstring GetTag();
		void SetTag(std::wstring value);

		std::wstring GetId();
		void SetId(std::wstring value);

		std::wstring GetHref();
		void SetHref(std::wstring value);

		std::wstring GetRole();
		void SetRole(std::wstring value);

	public:
		std::wstring tag;
		std::wstring id;
		std::wstring href;
		std::wstring role;
	};
}