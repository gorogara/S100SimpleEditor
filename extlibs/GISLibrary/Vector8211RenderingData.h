#pragma once

#include <list>

class R_FeatureRecord;
class SGeometry;
class Vector8211RenderingData
{
public:
	Vector8211RenderingData();
	virtual ~Vector8211RenderingData();

	R_FeatureRecord* m_feature; 
	SGeometry* m_point; 
	std::list<SGeometry*> m_geoCurve; 
	SGeometry* m_surface;     
	void Draw(int geoType);
};

