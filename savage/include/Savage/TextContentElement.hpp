#ifndef SAVAGE_TEXTCONTENTELEMENT_HPP
#define SAVAGE_TEXTCONTENTELEMENT_HPP

#include "SVGElement.hpp"

namespace Savage
{

enum TextContentElementType
{
	TEXTCONTENTELEMENTTYPE_TEXT
};

class TextContentElement : public SVGElement
{
	const TextContentElementType textContentElementType;
	
public:
	inline TextContentElement(TextContentElementType _textContentElementType)
	: SVGElement(SVGELEMENTTYPE_TEXTCONTENT)
	, textContentElementType(_textContentElementType)
	{
	}
	
	inline TextContentElementType getTextContentElement() const
	{
		return textContentElementType;
	}
};

} // namespace Savage
#endif // SAVAGE_TEXTCONTENTELEMENT_HPP