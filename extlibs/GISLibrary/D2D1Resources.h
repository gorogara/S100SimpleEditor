#pragma once
#include <vector>

class ENCCell;

namespace GISLibrary
{
	class D2D1Resources
	{
	private:
		ID2D1StrokeStyle1 *pSolidStrokeStyle = nullptr;
		ID2D1StrokeStyle1 *pDashStrokeStyle = nullptr;
		ID2D1StrokeStyle1 *pDotStrokeStyle = nullptr;
	public:
		D2D1Resources();
		virtual ~D2D1Resources(); 
		ID2D1Factory1 *pD2Factory = nullptr; 
		std::vector<ID2D1StrokeStyle1*> D2D1StrokeStyleGroup;

		IDWriteFactory *pDWriteFactory = nullptr;
		IDWriteTextFormat *pDWriteTextFormat = nullptr;
		IDWriteTextFormat* pDWriteTextFormatArea = nullptr;
		IDWriteTextLayout *pDWriteTextLayout = nullptr;
		IWICImagingFactory* pImagingFactory = nullptr;

		std::unordered_map<int, IDWriteTextFormat*> writeTextFormatListByFontSize; 
		ID2D1DCRenderTarget *pRT = nullptr;
		ID2D1SolidColorBrush *pBrush = nullptr; 
		ENCCell* pCell = nullptr;

	public:
		bool CreateDeviceIndependentResources();
		void DeleteDeviceIndependentResources();

		bool CreateDeviceDependentResources();
		void DeleteDeviceDependentResources();

		bool CreateReSizeTextFormat(int size);

		ENCCell* GetCell();
	};
}