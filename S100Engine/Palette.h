#pragma once

#include <string>
#include <vector>
#include "Item.h"

using namespace std;

class Palette
{
public:
	Palette();
	virtual ~Palette();

public:
	wstring      name;
	vector<libS100Engine::Item> item;
};