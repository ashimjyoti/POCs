#ifndef SAVAGE_STYLABLE_HPP
#define SAVAGE_STYLABLE_HPP

#include "Style.hpp"

namespace Savage
{

class Stylable
{
	Style style;
public:
	inline Style& getStyle()
	{
		return style;
	}
};

} // namespace Savage

#endif // SAVAGE_STYLABLE_HPP