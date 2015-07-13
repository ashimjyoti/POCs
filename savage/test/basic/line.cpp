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
	Savage::SVG _svg;
	
	_svg.setX(0);
	_svg.setY(0);
	_svg.setW(1000);
	_svg.setH(1000);
	
	std::shared_ptr<Savage::Line> _line = std::make_shared<Savage::Line>();
	_line->setX1(10);
	_line->setY1(10);
	_line->setX2(990);
	_line->setY2(990);
	_svg.addChild(_line);
	
	std::shared_ptr<Savage::Rect> _rect = std::make_shared<Savage::Rect>();
	_rect->setX(10);
	_rect->setY(10);
	_rect->setW(50);
	_rect->setH(50);
	_rect->setRX(20);
	_rect->setRY(20);
	_svg.addChild(_rect);
	
	std::shared_ptr<Savage::Circle> _circle = std::make_shared<Savage::Circle>();
	_circle->setCX(100);
	_circle->setCY(100);
	_circle->setR(40);
	_svg.addChild(_circle);
	
	std::shared_ptr<Savage::Ellipse> _ellipse = std::make_shared<Savage::Ellipse>();
	_ellipse->setCX(200);
	_ellipse->setCY(200);
	_ellipse->setRX(40);
	_ellipse->setRY(60);
	_svg.addChild(_ellipse);
	
	std::shared_ptr<Savage::PolyLine> _pl = std::make_shared<Savage::PolyLine>();
	_pl->addPoint(100, 100);
	_pl->addPoint(100, 200);
	_pl->addPoint(200, 200);
	_pl->addPoint(200, 300);
	_pl->addPoint(300, 300);
	_pl->addPoint(400, 400);
	_svg.addChild(_pl);
	
	std::shared_ptr<Savage::Polygon> _pg = std::make_shared<Savage::Polygon>();
	_pg->addPoint(400, 100);
	_pg->addPoint(400, 200);
	_pg->addPoint(600, 600);
	_pg->addPoint(200, 300);
	_pg->addPoint(300, 300);
	_pg->addPoint(400, 400);
	_svg.addChild(_pg);
	
	
	
	std::shared_ptr<Savage::Path> _path = std::make_shared<Savage::Path>();
	_svg.addChild(_path);
	std::shared_ptr<Savage::PathCommand> __pathCmd;
	
	std::shared_ptr<Savage::MoveToCommandAbsolute> moveToCmd;
	__pathCmd = moveToCmd = std::make_shared<Savage::MoveToCommandAbsolute>();
	moveToCmd->addPoint(100, 100);
	_path->addCommand(__pathCmd);
	
	std::shared_ptr<Savage::CurveToCommandAbsolute> curveToCmd;
	__pathCmd = curveToCmd = std::make_shared<Savage::CurveToCommandAbsolute>();
	curveToCmd->addPoint(200, 400, 400, 400, 500, 200);
	curveToCmd->addPoint(550, 400, 550, 400, 600, 100);
	_path->addCommand(__pathCmd);
	
	std::shared_ptr<Savage::ArcCommandAbsolute> arcCmd;
	__pathCmd = arcCmd = std::make_shared<Savage::ArcCommandAbsolute>();
	arcCmd->addPoint(200, 200, 45, 0, 1, 200, 200);
	_path->addCommand(__pathCmd);
	
	
	_path->getStyle().setFill(0xFF, 0x00, 0xFF);
	
	std::shared_ptr<Savage::ClosePathCommand> closePathCmd;
	__pathCmd = closePathCmd = std::make_shared<Savage::ClosePathCommand>();
	_path->addCommand(__pathCmd);
	
	std::shared_ptr<Savage::LineToCommandAbsolute> lineToCmd;
	__pathCmd = lineToCmd = std::make_shared<Savage::LineToCommandAbsolute>();
	lineToCmd->addPoint(300, 350);
	lineToCmd->addPoint(350, 350);
	lineToCmd->addPoint(750, 150);
	_path->addCommand(__pathCmd);
	
	std::shared_ptr<Savage::Text> _text = std::make_shared<Savage::Text>();
	_text->setText("Hello World");
	_text->setX(600);
	_text->setY(200);
	_text->getStyle().setColor(0x00, 0x00, 0xFF);
	_svg.addChild(_text);
	
	_svg.toString(std::cout);
}