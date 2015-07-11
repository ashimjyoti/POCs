#ifndef SAVAGE_SHAPEELEMENT_HPP
#define SAVAGE_SHAPEELEMENT_HPP

#include "SVGElement.hpp"

namespace Savage
{

enum ShapeElementType
{
	SHAPEELEMENTTYPE_PATH,
	SHAPEELEMENTTYPE_RECT,
	SHAPEELEMENTTYPE_CIRCLE,
	SHAPEELEMENTTYPE_ELLIPSE,
	SHAPEELEMENTTYPE_LINE,
	SHAPEELEMENTTYPE_POLYLINE,
	SHAPEELEMENTTYPE_POLYGON,
};

class ShapeElement : public SVGElement
{
	const ShapeElementType shapeElementType;
	
public:
	inline ShapeElement(ShapeElementType _shapeElementType)
	: SVGElement(SVGELEMENTTYPE_SHAPE)
	, shapeElementType(_shapeElementType)
	{
	}
	
	inline ShapeElementType getShapeElementType() const
	{
		return shapeElementType;
	}
};

} // namespace Savage
#endif // SAVAGE_SHAPEELEMENT_HPP