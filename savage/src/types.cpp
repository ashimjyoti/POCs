#include "types.hpp"

namespace LibSVG
{

Angle::Angle(number_t	_v, AngleUnit _u)
: v(_v)
, u(_u)
{
}

Length::Length(number_t	_v, LengthUnit _u)
: v(_v)
, u(_u)
{
}

Shape::Shape(ShapeType _t)
: t(_t)
{
}

Rectangle::Rectangle(Coord& _x, Coord& _y, Length& _w, Length& _h, Length& _rx, Length& _ry)
: Shape(RECTANGLE)
, x(_x)
, y(_y)
, w(_w)
, h(_h)
, rx(_rx)
, ry(_ry)
{
}

Circle::Circle(Coord& _cx, Coord& _cy, Length& _r)
: Shape(CIRCLE)
, cx(_cx)
, cy(_cy)
, r(_r)
{
}

Ellipse::Ellipse(Coord& _cx, Coord& _cy, Length& _rx, Length& _ry)
: Shape(ELLIPSE)
, cx(_cx)
, cy(_cy)
, rx(_rx)
, ry(_ry)
{
}

Line::Line(Coord& _x1, Coord& _y1, Coord& _x2, Coord& _y2)
: Shape(LINE)
, x1(_x1)
, y1(_y1)
, x2(_x2)
, y2(_y2)
{
}

PolyLine::PolyLine()
: Shape(POLYLINE)
{
}

Polygon::Polygon()
: Shape(POLYGON)
{
}

SVG::SVG(Coord& _x, Coord& _y, Length& _w, Length& _h)
: x(_x)
, y(_y)
, w(_w)
, h(_h)
{
}

} // namespace LibSVG