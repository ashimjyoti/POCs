#ifndef SAVAGE_CIRCLE_HPP
#define SAVAGE_CIRCLE_HPP

#include "ShapeElement.hpp"

namespace Savage
{

class Circle : public ShapeElement
{
	Coord cx;
	Coord cy;
	Length r;
	
public:
	inline Circle()
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
	
	inline const Length& getR() const
	{
		return r;
	}
	
	inline void setR(const Length& _r)
	{
		r = _r;
	}

	std::ostream& toString(std::ostream& stream)
	{
		return stream
			<< "<circle"
			<< " cx=\"" << getCX() << "\""
			<< " cy=\"" << getCY() << "\""
			<< " r=\"" << getR() << "\""
			<< " " << getStyle()
			<< " />"
			<< std::endl;
	}
};

} // namespace Savage
#endif // SAVAGE_CIRCLE_HPP