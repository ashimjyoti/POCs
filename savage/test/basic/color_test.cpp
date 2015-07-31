#include <iostream>

#include "SVG.hpp"
#include "Line.hpp"
#include "Rect.hpp"
#include "Circle.hpp"
#include "Ellipse.hpp"
#include "PolyLine.hpp"
#include "Polygon.hpp"
#include "Path.hpp"
#include "Text.hpp"

int main()
{
	srand(time(NULL));
	
	Savage::SVG _svg;
	_svg.setX(0);
	_svg.setY(0);
	_svg.setW(1200);
	_svg.setH(1200);
	
	for(Savage::number_t x = 0; x < 0xFF; x++)
	{
		std::shared_ptr<Savage::Line> _line = std::make_shared<Savage::Line>();
		_line->setX1(100 + x*2);
		_line->setY1(100);
		_line->setX2(100 + x*2);
		_line->setY2(1000);
		_line->getStyle().setStrokeWidth(2);
		_line->getStyle().setStroke(x, 0, 0xFF);
		_svg.addChild(_line);
	}
	
	_svg.toString(std::cout);
}