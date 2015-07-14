#ifndef SAVAGE_ANGLE_HPP
#define SAVAGE_ANGLE_HPP

#include "types.hpp"

namespace Savage
{

enum AngleUnit
{
	ANGLEUNIT_UNDEFINED,
	ANGLEUNIT_DEGREE,
	ANGLEUNIT_RADIAN,
	ANGLEUNIT_GRAD
};

struct Angle
{
	const number_t	v;
	const AngleUnit	u;
	
	Angle(number_t	_v, AngleUnit _u = ANGLEUNIT_UNDEFINED);
};

} // namespace Savage

#endif // SAVAGE_ANGLE_HPP