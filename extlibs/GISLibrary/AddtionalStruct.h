#pragma once

#include <list>

class Layer;
class ENC_Feature;
class MBR;

using namespace std;

struct FindedFeature
{
	FindedFeature() {}
	virtual ~FindedFeature() {}

public:
	Layer* layer;
	ENC_Feature* fe;
	MBR* mbr;
};

typedef list<FindedFeature> ListFindedFeature;