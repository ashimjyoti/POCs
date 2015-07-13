#ifndef SAVAGE_LINE_HPP
#define SAVAGE_LINE_HPP

#include "ShapeElement.hpp"

namespace Savage
{

class Line : public ShapeElement
{
	Coord x1;
	Coord y1;
	Coord x2;
	Coord y2;
	
public:
	inline Line()
	: ShapeElement(SHAPEELEMENTTYPE_LINE)
	{
	}
	
	inline const Coord& getX1() const
	{
		return x1;
	}
	
	inline const Coord& getY1() const
	{
		return y1;
	}
	
	inline const Coord& getX2() const
	{
		return x2;
	}
	
	inline const Coord& getY2() const
	{
		return y2;
	}
	
	inline void setX1(const Coord& _x1)
	{
		x1 = _x1;
	}
	
	inline void setY1(const Coord& _y1)
	{
		y1 = _y1;
	}
	
	inline void setX2(const Coord& _x2)
	{
		x2 = _x2;
	}
	
	inline void setY2(const Coord& _y2)
	{
		y2 = _y2;
	}
	
	std::ostream& toString(std::ostream& stream)
	{
		return stream
			<< "<line"
			<< " x1=\"" << getX1() << "\""
			<< " y1=\"" << getY1() << "\""
			<< " x2=\"" << getX2() << "\""
			<< " y2=\"" << getY2() << "\""
			<< " " << getStyle()
			<< " />"
			<< std::endl;
	}
};

} // namespace Savage
#endif // SAVAGE_LINE_HPP