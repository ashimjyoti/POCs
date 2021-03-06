#ifndef SAVAGE_SVGELEMENT_HPP
#define SAVAGE_SVGELEMENT_HPP

#include <ostream>
#include "Stylable.hpp"

namespace Savage
{

enum SVGElementType
{
	SVGELEMENTTYPE_ANIMATION,
	SVGELEMENTTYPE_DESCRIPTIVE,
	SVGELEMENTTYPE_SHAPE,
	SVGELEMENTTYPE_STRUCTURAL,
	SVGELEMENTTYPE_GRADIENT,
	SVGELEMENTTYPE_TEXTCONTENT,
};

class SVGElement : public Stylable
{
	SVGElementType svgElementType;
	
public:
	inline SVGElement(SVGElementType _svgElementType)
	: svgElementType(_svgElementType)
	{
	}
	
	inline SVGElementType getSVGElementType() const
	{
		return svgElementType;
	}
	
	virtual std::ostream& toString(std::ostream&) = 0;
};

} // namespace Savage
#endif // SAVAGE_SVGELEMENT_HPP