#ifndef SAVAGE_STRUCTURALELEMENT_HPP
#define SAVAGE_STRUCTURALELEMENT_HPP

#include "SVGElement.hpp"

namespace Savage
{

enum StructuralElementType
{
	STRUCTURALELEMENTTYPE_DEFS,
	STRUCTURALELEMENTTYPE_G,
	STRUCTURALELEMENTTYPE_SVG,
	STRUCTURALELEMENTTYPE_SYMBOL,
	STRUCTURALELEMENTTYPE_USE
};

class StructuralElement : public SVGElement
{
	const StructuralElementType structuralElementType;
	
public:
	inline StructuralElement(StructuralElementType _structuralElementType)
	: SVGElement(SVGELEMENTTYPE_STRUCTURAL)
	, structuralElementType(_structuralElementType)
	{
	}
	
	inline StructuralElementType getStructuralElementType() const
	{
		return structuralElementType;
	}
};

} // namespace Savage
#endif // SAVAGE_STRUCTURALELEMENT_HPP