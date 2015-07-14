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
	
	for(Savage::number_t x = 100; x <= 1100; x+=50)
	{
		std::shared_ptr<Savage::Line> _line = std::make_shared<Savage::Line>();
		_line->setX1(x);
		_line->setY1(1100);
		_line->setX2(x);
		_line->setY2(rand()%1000);
		_line->getStyle().setStrokeWidth(40);
		_svg.addChild(_line);
	}
	
	_svg.toString(std::cout);
}