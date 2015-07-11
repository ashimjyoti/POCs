#ifndef SAVAGE_LENGTH_HPP
#define SAVAGE_LENGTH_HPP

#include "types.hpp"

namespace Savage
{

enum LengthUnit
{
	LENGTHUNIT_UNDEFINED,
	LENGTHUNIT_EM,
	LENGTHUNIT_EX,
	LENGTHUNIT_PX,
	LENGTHUNIT_IN,
	LENGTHUNIT_CM,
	LENGTHUNIT_MM,
	LENGTHUNIT_PT,
	LENGTHUNIT_PC,
	LENGTHUNIT_PR
};

class Length
{
	number_t	v;
	LengthUnit	u;
public:
	inline Length()
	: v(0)
	, u(LENGTHUNIT_UNDEFINED)
	{
	}
	
	inline Length(number_t _v, LengthUnit _u = LENGTHUNIT_UNDEFINED)
	: v(_v)
	, u(_u)
	{
	}
	
	inline number_t getValue() const
	{
		return v;
	}
	
	inline LengthUnit getUnit() const
	{
		return u;
	}
	
	inline void setValue(const number_t _v)
	{
		v = _v;
	}
	
	inline void setUnit(const LengthUnit _u)
	{
		u = _u;
	}
	
	inline Length& operator = (number_t _v)
	{
		setValue(_v);
		return *this;
	}
};

template <typename StreamT>
StreamT& operator << (StreamT& stream, const LengthUnit& u)
{
	switch(u)
	{
		case LENGTHUNIT_EM:
		{
			return stream << "em";
		}
		case LENGTHUNIT_EX:
		{
			return stream << "ex";
		}
		case LENGTHUNIT_PX:
		{
			return stream << "px";
		}
		case LENGTHUNIT_IN:
		{
			return stream << "in";
		}
		case LENGTHUNIT_CM:
		{
			return stream << "cm";
		}
		case LENGTHUNIT_MM:
		{
			return stream << "mm";
		}
		case LENGTHUNIT_PT:
		{
			return stream << "pt";
		}
		case LENGTHUNIT_PC:
		{
			return stream << "pc";
		}
		case LENGTHUNIT_PR:
		{
			return stream << "%";
		}
		default:
		{
			return stream;
		}
	}
}

template <typename StreamT>
StreamT& operator << (StreamT& stream, const Length& _l)
{
	return stream << _l.getValue() << _l.getUnit();
}

} // namespace Savage

#endif // SAVAGE_LENGTH_HPP