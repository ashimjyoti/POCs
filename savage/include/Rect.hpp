#ifndef SAVAGE_RECTANGLE_HPP
#define SAVAGE_RECTANGLE_HPP

#include "ShapeElement.hpp"

namespace Savage
{

class Rect : public ShapeElement
{
	Coord x;
	Coord y;
	Length w;
	Length h;
	Length rx;
	Length ry;
	
public:
	inline Rect()
	: ShapeElement(SHAPEELEMENTTYPE_RECT)
	{
	}
	
	inline const Coord& getX() const
	{
		return x;
	}
	
	inline const Coord& getY() const
	{
		return y;
	}
	
	inline void setX(const Coord& _x)
	{
		x = _x;
	}
	
	inline void setY(const Coord& _y)
	{
		y = _y;
	}
	
	inline const Length& getW() const
	{
		return w;
	}
	
	inline const Length& getH() const
	{
		return h;
	}
	
	inline void setW(const Length& _w)
	{
		w = _w;
	}
	
	inline void setH(const Length& _h)
	{
		h = _h;
	}
	
	inline const Length& getRX() const
	{
		return rx;
	}
	
	inline const Length& getRY() const
	{
		return ry;
	}
	
	inline void setRX(const Length& _rx)
	{
		rx = _rx;
	}
	
	inline void setRY(const Length& _ry)
	{
		ry = _ry;
	}
	
	std::ostream& toString(std::ostream& stream)
	{
		return stream
			<< "<rect"
			<< " x=\"" << getX() << "\""
			<< " y=\"" << getY() << "\""
			<< " width=\"" << getW() << "\""
			<< " height=\"" << getH() << "\""
			<< " rx=\"" << getRX() << "\""
			<< " ry=\"" << getRY() << "\""
			<< " />"
			<< std::endl;
	}
};

} // namespace Savage
#endif // SAVAGE_RECTANGLE_HPP