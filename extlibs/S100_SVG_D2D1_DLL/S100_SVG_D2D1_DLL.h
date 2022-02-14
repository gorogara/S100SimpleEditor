// S100_SVG_D2D1_DLL.h : S100_SVG_D2D1_DLL DLL�� �⺻ ��� �����Դϴ�. 

#pragma once


#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif   
#include <string> 

#ifdef S100_SVG_D2D1_DLL_EXPORT
#define S100_SVG_D2D1_DLL_API __declspec(dllexport)
#else
#define S100_SVG_D2D1_DLL_API __declspec(dllimport)
#endif                                

class PortrayalCatalogue;

namespace S100_SVG_D2D1_DLL
{
	class SVGManager;
	class CS100_SVG_D2D1_DLLApp
	{
	public:
		CS100_SVG_D2D1_DLLApp(); 
	public: 
		SVGManager* GetSVGManager();
		SVGManager *svgMng;

	public:
		void SetFactory(); 
		void SetTarget(CDC* pDC, CRect rectView);  
		void PushSymbol(std::wstring _symName, D2D_POINT_2F _position, float _rotation = 0.0, float _scale = 1.0);

		void PushSymbol(
			SVGManager *svgManager,
			std::wstring _symName, 
			D2D_POINT_2F _position, 
			float _rotation = 0.0, 
			float _scale = 1.0);  
		void PushSymboledLine(std::wstring _lineName, D2D1_POINT_2F _startPos, D2D1_POINT_2F _endPos);  
		void PushPattern(std::wstring symName, D2D1_POINT_2F* points, int pointSize);  
		void PushText(std::wstring _text, POINTF _startPos, float _fontSize); 
		void DrawSymbols();
		void DrawSymbols(PortrayalCatalogue *pc); 
		void DrawSymboledLine(); 
		void DrawPattern(); 
		void DrawTexts(CRect rectView);
	};

	CS100_SVG_D2D1_DLLApp* GetApp();
}
