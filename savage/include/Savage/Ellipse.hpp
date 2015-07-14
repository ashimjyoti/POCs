#ifndef SAVAGE_ELLIPSE_HPP
#define SAVAGE_ELLIPSE_HPP

#include "ShapeElement.hpp"

namespace Savage
{

class Ellipse : public ShapeElement
{
	Coord cx;
	Coord cy;
	Length rx;
	Length ry;
	
public:
	inline Ellipse()
	: ShapeElement(SHAPEELEMENTTYPE_CIRCLE)
	{
	}
	
	inline const Coord& getCX() const
	{
		return cx;
	}
	
	inline const Coord& getCY() const
	{
		return cy;
	}
	
	inline void setCX(const Coord& _cx)
	{
		cx = _cx;
	}
	
	inline void setCY(const Coord& _cy)
	{
		cy = _cy;
	}
	
	inline const Length& getRX() const
	{
		return rx;
	}
	
	inline void setRX(const Length& _rx)
	{
		rx = _rx;
	}
	
	inline const Length& getRY() const
	{
		return ry;
	}
	
	inline void setRY(const Length& _ry)
	{
		ry = _ry;
	}

	std::ostream& toString(std::ostream& stream)
	{
		return stream
			<< "<ellipse"
			<< " cx=\"" << getCX() << "\""
			<< " cy=\"" << getCY() << "\""
			<< " rx=\"" << getRX() << "\""
			<< " ry=\"" << getRY() << "\""
			<< " " << getStyle()
			<< " />"
			<< std::endl;
	}
};

} // namespace Savage
#endif // SAVAGE_ELLIPSE_HPP