#pragma once

#include "TextPackageEnum.h"
#include "GraphicBasePackage.h"
#include "SymbolPackageEnum.h"

namespace TextPackage
{
	class TextElement;
	class TextFlags;
	class Font;

	class Text
	{
	public:
		Text();
		virtual ~Text();

		TextPackage::HorizontalAlignment horizontalAlignment = TextPackage::HorizontalAlignment::start;
		TextPackage::VerticalAlignment verticalAlignment = TextPackage::VerticalAlignment::bottom;
		std::vector<TextElement*> element; 
	};

	class TextPoint : public TextPackage::Text
	{
	public:
		TextPoint();
		virtual ~TextPoint();

		GraphicBasePackage::Vector* offset = nullptr; 
		double rotation = 0;
		SymbolPackage::AreaPlacementMode placementMode = SymbolPackage::AreaPlacementMode::visibleParts;
	};

	class TextLine : public TextPackage::Text
	{
	public:
		TextLine();
		virtual ~TextLine();

		double startOffset = 0; 
		double* endOffset = nullptr; 
		SymbolPackage::LinePlacementMode placementMode = SymbolPackage::LinePlacementMode::relative; 
	};

	class TextElement
	{
	public:
		TextElement();
		virtual ~TextElement();

		std::wstring text;
		double bodySize = 10; 
		double verticalOffset = 0;
		TextPackage::Font* font = nullptr; 
		GraphicBasePackage::Color foreground;
		GraphicBasePackage::Color* background = nullptr; 
		TextPackage::TextFlags* flags = nullptr; 
	};

	class Font
	{
	public:
		Font();
		virtual ~Font();
		TextPackage::FontWeight weight = TextPackage::FontWeight::medium; 
		TextPackage::FontSlant slant = TextPackage::FontSlant::upright; 
		TextPackage::_FontSubClassType subClassType = TextPackage::_FontSubClassType::_Font;
	};

	class FontReference : public TextPackage::Font
	{
	public:
		FontReference();
		virtual ~FontReference();
		std::wstring reference; 
	};

	class FontCharacteristics : public TextPackage::Font
	{
	public:
		FontCharacteristics();
		virtual ~FontCharacteristics();
		bool serifs = false; 
		TextPackage::FontProportion proportion = TextPackage::FontProportion::monoSpaced; 
	};

	class TextFlags
	{
	public:
		TextFlags();
		virtual ~TextFlags();
		std::vector<TextPackage::TextFlag> flag; 
	};
}