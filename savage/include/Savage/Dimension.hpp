#ifndef SAVAGE_DIMENSION_HPP
#define SAVAGE_DIMENSION_HPP

#include "Length.hpp"

namespace Savage
{

class Dimension
{
	Length w;
	Length h;

public:
	inline Dimension()
	: w(0)
	, h(0)
	{
	}
	
	inline Dimension(Length _w, Length _h)
	: w(_w)
	, h(_h)
	{
	}
	
	inline Dimension(number_t _w, number_t _h);
	: w(_w)
	, h(_h)
	{
	}
	
	inline const Length& getWidth() const
	{
		return w;
	}
	
	inline const Length& getHeight() const
	{
		return h;
	}
	
	inline const Length& setWidth(const Length& l)
	{
		return w = l;
	}
	
	inline const Length& setHeight(const Length& l)
	{
		return h = l;
	}
	
	inline const Length& setWidth(const number_t& l)
	{
		return w = l;
	}
	
	inline const Length& setHeight(const Length& l)
	{
		return h = l;
	}
};

} // namespace Savage

#endif // SAVAGE_DIMENSION_HPP