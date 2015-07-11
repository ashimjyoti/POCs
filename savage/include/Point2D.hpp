#ifndef SAVAGE_POINT2D_HPP
#define SAVAGE_POINT2D_HPP

#include "Coord.hpp"
#include "Point1D.hpp"

namespace Savage
{

class Point2D : public Point1D
{
	Coord	y;
public:
	inline const Coord& getY() const
	{
		return y;
	}
	
	inline void setY(const Coord& _y)
	{
		y = _y;
	}
	
	inline void setY(const number_t _y)
	{
		y.setValue(_y);
	}
};

} // namespace Savage
#endif // SAVAGE_POINT2D_HPP