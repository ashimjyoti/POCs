#ifndef SAVAGE_STYLE_HPP
#define SAVAGE_STYLE_HPP

#include <memory>

#include "types.hpp"
#include "Color.hpp"
#include "Length.hpp"

namespace Savage
{

enum StrokeLineCap
{
	STROKE_LINECAP_BUTT,
	STROKE_LINECAP_ROUND,
	STROKE_LINECAP_SQUARE,
};

enum StrokeLineJoin
{
	STROKE_LINEJOIN_MITER,
	STROKE_LINEJOIN_ROUND,
	STROKE_LINEJOIN_BEVEL,
};

class Style
{
	Color			color;
	
	Color			fill;
	number_t		fill_opacity;
	
	Color			stroke;
	Length			stroke_width;
	StrokeLineCap	stroke_linecap;
	StrokeLineJoin	stroke_linejoin;
	number_t		stroke_opacity;
	
public:
	Style()
	: fill_opacity(1)
	, stroke_width(1)
	, stroke_linecap(STROKE_LINECAP_BUTT)
	, stroke_linejoin(STROKE_LINEJOIN_MITER)
	, stroke_opacity(1)
	{
	}
	
	const Color& getColor() const
	{
		return color;
	}
	
	const void setColor(const Color& _color)
	{
		color = _color;
	}
	
	const void setColor(uint8_t _r, uint8_t _g, uint8_t _b)
	{
		color.set(_r, _g, _b);
	}
	
	const Color& getFill() const
	{
		return fill;
	}
	
	const void setFill(const Color& _fill)
	{
		fill = _fill;
	}

	const void setFill(uint8_t _r, uint8_t _g, uint8_t _b)
	{
		fill.set(_r, _g, _b);
	}
	
	const number_t& getFillOpacity() const
	{
		return fill_opacity;
	}
	
	const void setFillOpacity(const number_t _fill_opacity)
	{
		fill_opacity = _fill_opacity;
	}
	
	const Color& getStroke() const
	{
		return stroke;
	}
	
	const void setStroke(const Color& _stroke)
	{
		stroke = _stroke;
	}
	
	const void setStroke(uint8_t _r, uint8_t _g, uint8_t _b)
	{
		stroke.set(_r, _g, _b);
	}
	
	const Length& getStrokeWidth() const
	{
		return stroke_width;
	}
	
	const void setStrokeWidth(const Length& _stroke_width)
	{
		stroke_width = _stroke_width;
	}
	
	const StrokeLineCap& getStrokeLineCap() const
	{
		return stroke_linecap;
	}
	
	const void setStrokeLineCap(const StrokeLineCap _stroke_linecap)
	{
		stroke_linecap = _stroke_linecap;
	}
	
	const StrokeLineJoin& getStrokeLineJoin() const
	{
		return stroke_linejoin;
	}
	
	const void setStrokeLineJoin(const StrokeLineJoin _stroke_linejoin)
	{
		stroke_linejoin = _stroke_linejoin;
	}
	
	const number_t& getStrokeOpacity() const
	{
		return stroke_opacity;
	}
	
	const void setStrokeOpacity(const number_t _stroke_opacity)
	{
		stroke_opacity = _stroke_opacity;
	}
};

template <typename StreamT>
StreamT& operator << (StreamT& stream, const Style& _c)
{
	stream << "style=\"";
	stream << " color:" << _c.getColor() << ";";
	stream << " fill:" << _c.getFill() << ";";
	stream << " fill-opacity:" << _c.getFillOpacity() << ";";
	stream << " stroke:" << _c.getStroke() << ";";
	stream << " stroke-width:" << _c.getStrokeWidth() << ";";
	// stream << " stroke-linecap:" << _c.getStrokeLineCap() << ";";
	// stream << " stroke-linejoin:" << _c.getStrokeLineJoin() << ";";
	stream << " stroke-opacity:" << _c.getStrokeOpacity() << ";";
	stream << "\"";
	return stream;
}

} // namespace Savage

#endif // SAVAGE_STYLE_HPP