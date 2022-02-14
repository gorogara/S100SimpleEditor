#pragma once 
#include <vector>
#include <string>

#include "figure.h"
#include "Line.h"
#include "Circle.h"
#include "PivotPoint.h"

#include "SVGGeometry.h"
using namespace std;

struct ID2D1Factory1;
struct ID2D1PathGeometry;



class SVGReader
{
public:
	SVGReader();
	SVGReader(char* path);
	virtual ~SVGReader();

	bool Open(char* path);
	bool OpenByPugi(char* path);
	void Close();
	void svgSet(char* path);

	void CreateSVGGeometry(ID2D1Factory1* m_pDirect2dFactory);
	SVGGeometry CreateSVGGeometryFromLine(ID2D1Factory1* m_pDirect2dFactory, libS100Engine::Line* line);
	SVGGeometry CreateSVGGeometryFromCircle(libS100Engine::Circle* circle);

	std::vector<libS100Engine::Figure*> figures;
	std::wstring name;

	std::vector<SVGGeometry> geometry; 
	float bounding_x;
	float bounding_y;
	float bounding_width;
	float bounding_height; 
	float svgBox_x;
	float svgBox_y;
	float svgBox_width;
	float svgBox_height;
};