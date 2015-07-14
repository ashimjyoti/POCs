#ifndef GOTTU_COLORPROVIDER_HPP
#define GOTTU_COLORPROVIDER_HPP

#include <Savage/types.hpp>
#include <Savage/Color.hpp>

namespace Gottu
{

using Savage::number_t;
using Savage::Color;

class ColorProvider
{
public:
	Color getColor(number_t x) = 0;
};

} // namespace Gottu

#endif // GOTTU_COLORPROVIDER_HPP