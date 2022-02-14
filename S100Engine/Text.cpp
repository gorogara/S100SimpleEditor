#include "stdafx.h"
#include "Text.h"

#pragma region class Text
TextPackage::Text::Text()
{
}


TextPackage::Text::~Text()
{
	for (auto i = element.begin(); i != element.end(); i++)
	{
		delete *i;
		*i = nullptr;
	}
}
#pragma endregion


#pragma region class TextPoint
TextPackage::TextPoint::TextPoint()
{
}


TextPackage::TextPoint::~TextPoint()
{
	if (offset)
	{
		delete offset;
		offset = nullptr;
	}
}
#pragma endregion


#pragma region class TextLine
TextPackage::TextLine::TextLine()
{
	
}


TextPackage::TextLine::~TextLine()
{
	if (endOffset)
	{
		delete endOffset;
		endOffset = nullptr;
	}
}
#pragma endregion


#pragma region class TextElement
TextPackage::TextElement::TextElement()
{
}


TextPackage::TextElement::~TextElement()
{
	if (font)
	{
		delete font;
		font = nullptr;
	}

	if (background)
	{
		delete background;
		background = nullptr;
	}

	if (flags)
	{
		delete flags;
		flags = nullptr;
	}
}
#pragma endregion


#pragma region class FontCharacteristics
TextPackage::FontCharacteristics::FontCharacteristics()
{
}


TextPackage::FontCharacteristics::~FontCharacteristics()
{
}
#pragma endregion


#pragma region class TextFlags
TextPackage::TextFlags::TextFlags()
{
}


TextPackage::TextFlags::~TextFlags()
{
}
#pragma endregion 


#pragma region class FontReference
TextPackage::FontReference::FontReference()
{
}


TextPackage::FontReference::~FontReference()
{
}
#pragma endregion 


#pragma region class Font
TextPackage::Font::Font()
{
}


TextPackage::Font::~Font()
{
}
#pragma endregion 