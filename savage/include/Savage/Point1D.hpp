#ifndef SAVAGE_POINT1D_HPP
#define SAVAGE_POINT1D_HPP

#include "Coord.hpp"

namespace Savage
{

class Point1D
{
	Coord	x;
public:
	inline const Coord& getX() const
	{
		return x;
	}
	
	inline void setX(const Coord& _x)
	{
		x = _x;
	}
	
	inline void setX(const number_t _x)
	{
		x.setValue(_x);
	}
};

} // namespace Savage
#endif // SAVAGE_POINT1D_HPP