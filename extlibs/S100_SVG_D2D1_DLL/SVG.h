#pragma once

#include "S100_SVG_D2D1_DLL.h"

#include "SymbolPath.h"
#include "SymbolCircle.h"
#include "Symbol.h"
#include "SymColor.h"
#include "DRAW_BRUSH_STRUCT.h"

#include "Title.h"
#include "Description.h"
#include "Metadata.h"
#include "BoxLayout.h"
#include "PivotPointLayout.h"
#include "DrawingPathUnit.h"

#include "..\\extlibs\\pugixml\\include\\pugixml.hpp"

#import <msxml4.dll>

#include<unordered_map>
#include <string>
#include <list>
#include <gdiplus.h>


#define factor (float)3.5

class S100_ColorProfile;

namespace S100_SVG_D2D1_DLL
{
	class CSS;
	class CSSStyle;
	class DrawingPattern;
	class OrgDrawingPattern;
	class DrawingPathUnit;

	class SVG
	{
	public:
		SVG();
		virtual ~SVG();   

	public:
		std::wstring m_filepath;
		std::wstring m_svgName;

		std::wstring m_width;
		std::wstring m_height;
		std::wstring m_viewBox;

		Title m_title;
		Description m_desc;
		Metadata m_metadata;
		BoxLayout m_symbolLayout;
		BoxLayout m_SVGBoxLayout;
		std::list<DrawingPattern*> m_drawingObjList;
		PivotPointLayout m_pivotPointLayout;

		std::list<OrgDrawingPattern*> m_orgDrawingObjList; 

		float m_OrgWidth;
		float m_OrgHeight;
		POINTF m_pivotPoint;

	public:
		bool ReadSVGFile(std::wstring path);
		bool ReadSVGFileByPugiXml(std::wstring path); 
		void GetSVGInfo(MSXML2::IXMLDOMNodePtr pNode);
		void GetSVGInfo(pugi::xml_node& node);

		void GetTitle(MSXML2::IXMLDOMNodeListPtr pNodeList);
		void GetTitle(pugi::xml_node& node);

		void Getdesc(MSXML2::IXMLDOMNodeListPtr pNodeList);
		void Getdesc(pugi::xml_node& node);

		void Getmetadata(MSXML2::IXMLDOMNodeListPtr pNodeList);
		void Getmetadata(pugi::xml_node& node);

		void GetFigure(MSXML2::IXMLDOMNodePtr pNode);
		void GetFigure(pugi::xml_node& node);

		void GetSymbolBoxLayout(MSXML2::IXMLDOMNodePtr pNode);
		void GetSymbolBoxLayout(pugi::xml_node& node);

		void GetSVGBoxLayout(MSXML2::IXMLDOMNodePtr pNode);
		void GetSVGBoxLayout(pugi::xml_node& node);

		void GetSymbol(MSXML2::IXMLDOMNodePtr pNode);
		void GetSymbol(pugi::xml_node& node);

		void GetPivotPointLayout(MSXML2::IXMLDOMNodePtr pNode);
		void GetPivotPointLayout(pugi::xml_node& node);

		void OrganizeSymbol();  
		std::list<CSSStyle*> GetStyle(int type, std::wstring strStyle);
		void DrawSVGInfomationToWindow(HDC hdc, int cx, int cy); 
		void DrawSVGOrganizedInfomationToWindow();
	    void DrawSVGOrganizedInfomationToWindow(HDC hdc, int cx, int cy, int rotation = 0, float scaleFactor = 1.0);
		void DrawSVGOrganizedInfomationToWindow(Gdiplus::Graphics *bitmapG, Gdiplus::PointF originPoint, Gdiplus::PointF symbolSize, float position, double rotation = 0.0);
		void DrawSVGOrganizedInfomationToWindow(Gdiplus::Graphics *bitmapG, Gdiplus::PointF originPoint, double rotation = 0.0);
	
		void DrawSVGSimpleLine(Gdiplus::Graphics *bitmapG, Gdiplus::PointF _p1, Gdiplus::PointF _p2); 
		Symbol GetSymbol(ID2D1Factory* m_pDirect2dFactory, std::wstring paletteName, S100_ColorProfile *colorProfile);

		void MoveVectorPoint(std::vector<DrawingPathUnit*> &pOrgVector, std::vector<DrawingPathUnit*> &pSourceVector);
		void RotatePoint(POINT &p, const POINT pivotPoint, const double ROTATION);
		void RotatePoint(int &x, int &y, const int pvX, const int pvY, const double ROTATION);
		void RotatePoint(Gdiplus::PointF &p, const POINT pivotPoint, const double ROTATION);
		void RotatePoint(float &x, float &y, const int pvX, const int pvY, const double ROTATION);
		void RotatePoint(float &x, float &y, const float pvX, const float pvY, const double ROTATION);
	};
}

