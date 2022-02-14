#pragma once

#include <string>

class LayerManager;
class AddLayerThreadParameter
{
public:
	AddLayerThreadParameter();
	virtual ~AddLayerThreadParameter();

public:
	LayerManager* layerManager = nullptr;
	std::wstring fileName = L"";

public:
	void SetLayerManager(LayerManager* value);
	LayerManager* GetLayerManager();
	void SetFileName(std::wstring& value);
	void SetFileName(CString& value);
	std::wstring GetFileName();
};