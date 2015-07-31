#ifndef SAVAGE_TRANSFORM_HPP
#define SAVAGE_TRANSFORM_HPP

namespace Savage
{

class Transform
{
};

class Matrix
{
	number_t a;
	number_t b;
	number_t c;
	number_t d;
	number_t e;
	number_t f;
	
	Matrix(
		number_t _a = 0,
		number_t _b = 0,
		number_t _c = 0,
		number_t _d = 0,
		number_t _e = 0,
		number_t _f = 0)
	: a(_a)
	, b(_b)
	, c(_c)
	, d(_d)
	, e(_e)
	, f(_f)
	{
		
	}
};

} // namespace Savage

#endif // SAVAGE_TRANSFORM_HPP