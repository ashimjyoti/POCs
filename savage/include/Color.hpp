#ifndef SAVAGE_COLOR_HPP
#define SAVAGE_COLOR_HPP

#include <stdint.h>

namespace Savage
{

class Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;

public:
	inline Color()
	: r(0)
	, g(0)
	, b(0)
	{
	}
	
	inline Color(uint8_t _r, uint8_t _g, uint8_t _b)
	: r(_r)
	, g(_g)
	, b(_b)
	{
	}
	
	inline const uint8_t getR() const
	{
		return r;
	}
	
	inline void setR(uint8_t _r)
	{
		r = _r;
	}
	
	inline const uint8_t getG() const
	{
		return g;
	}
	
	inline void setG(uint8_t _g)
	{
		g = _g;
	}
	
	inline const uint8_t getB() const
	{
		return r;
	}
	
	inline void setB(uint8_t _b)
	{
		b = _b;
	}
	
	inline void set(uint8_t _r, uint8_t _g, uint8_t _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}
};

namespace __Private
{

template <typename StreamT>
StreamT& __toHex(StreamT& stream, const uint8_t u)
{
	if(0 == (u & 0xF0))
	{
		stream << "0";
	}
	stream << std::hex << (int) u << std::dec;
	
	return stream;
}

} // namespace __Private

template <typename StreamT>
StreamT& operator << (StreamT& stream, const Color& _c)
{
	stream << "#";
	__Private::__toHex(stream, _c.getR());
	__Private::__toHex(stream, _c.getG());
	__Private::__toHex(stream, _c.getB());
	return stream;
}

} // namespace Savage

#endif // SAVAGE_COLOR_HPP