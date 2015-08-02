#include <functional>
#include <string>
#include <cstring>
#include <cstdint>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>

#include "wb_regions.hpp"
#include "SVG.hpp"
#include "Line.hpp"
#include "Path.hpp"
#include "Text.hpp"

std::map<WBRegion, Savage::Color> colorsByRegion
{
	std::make_pair<WBRegion, Savage::Color>(WBREGION_UNKNOWN, {0x00, 0x00, 0x00}),
	std::make_pair<WBRegion, Savage::Color>(WBREGION_LATIN_AMERICA_AND_CARIBBEAN, {0x00, 0x00, 0x00}),
	std::make_pair<WBRegion, Savage::Color>(WBREGION_SOUTH_ASIA, {0x00, 0x00, 0x00}),
	std::make_pair<WBRegion, Savage::Color>(WBREGION_SUB_SAHARAN_AFRICA, {0x00, 0x00, 0x00}),
	std::make_pair<WBRegion, Savage::Color>(WBREGION_EUROPE_AND_CENTRAL_ASIA, {0x00, 0x00, 0x00}),
	std::make_pair<WBRegion, Savage::Color>(WBREGION_MIDDLE_EAST_AND_NORTH_AFRICA, {0x00, 0x00, 0x00}),
	std::make_pair<WBRegion, Savage::Color>(WBREGION_EAST_ASIA_AND_PACIFIC, {0x00, 0x00, 0x00}),
	std::make_pair<WBRegion, Savage::Color>(WBREGION_NORTH_AMERICA, {0x00, 0x00, 0x00})
};

struct Record
{
	// the country code: e.g. ARG
	std::string	mCountryName;
	// the country code: e.g. ARG
	std::string	mCountryCode;
	// key: year, value: life expectancy
	std::map<uint32_t, double>	mLifeExpectancy;
};

template <typename StreamT>
StreamT& operator << (StreamT& s, const Record& r)
{
	s << "{" << r.mCountryCode << "}";
	for(auto e : r.mLifeExpectancy)
	{
		s << e.second;
	}
	s << std::endl;
	return s;
}

template <typename StreamT, typename T>
StreamT& operator << (StreamT& s, const std::shared_ptr<T>& sp)
{
	return s << *(sp.get());
}

int load(const std::string& fileName, std::vector<std::shared_ptr<Record>>& records)
{
	int result = 1;
	
	std::ifstream is;
	is.open(fileName);
	if(!is.is_open())
	{
		std::cerr << "Could not open file: " << fileName << std::endl;
		return result;
	}
	
	while(!is.eof())
	{
		std::shared_ptr<Record> r = std::make_shared<Record>();
		is >> r->mCountryCode;
		for(uint32_t y = 1960; y < 2014; y++)
		{
			double e;
			is >> e;
			r->mLifeExpectancy[y] = e;
		}
		records.push_back(r);
	}
	
	is.close();
}

void usage(int argc, char **argv)
{
	std::cerr << "usage: " << argv[0] << " <csv file>" << std::endl;
}

bool hasNullData(const Record& r)
{
	bool result = false;
	
	for(auto e : r.mLifeExpectancy)
	{
		result = (0 == e.second);
		if(result) break;
	}
	
	return result;
}

WBRegion getWBRegion(const std::string& wbCountryCode)
{
	for(auto p : wb_region_by_wb_code)
	{
		// std::cerr << "getWBRegion: " << wbCountryCode << ":" << p.first << std::endl;
		if(0 == strcmp(wbCountryCode.c_str(), p.first.c_str()))
		{
			return p.second;
		}
	}
	return WBREGION_UNKNOWN;
}

int main(int argc, char **argv)
{
	if(2 != argc)
	{
		usage(argc, argv);
		exit(1);
	}
	
	const std::string inputFileName(argv[1]);
	
	std::vector<std::shared_ptr<Record>> records;
	if(!(load(inputFileName, records) >0))
	{
		exit(1);
	}
	
	Savage::SVG _svg;
	_svg.setX(100);
	_svg.setY(100);
	_svg.setW(1100);
	_svg.setH(1100);
	
	uint32_t delta_x = 15;
	uint32_t delta_year = 1;
	uint32_t scale_exp = 15;
	
	std::shared_ptr<Savage::PathCommand> __pathCmd;
	
	uint32_t ___color = 0;
	
	for(uint32_t i = 0; (i+1960) <= 2014; i+=1)
	{
		std::shared_ptr<Savage::Line> _line = std::make_shared<Savage::Line>();
		_line->setX1(i*delta_x);
		_line->setY1(0);
		_line->setX2(i*delta_x);
		_line->setY2(2000);
		_svg.addChild(_line);
		
		if(0 == i%10)
		{
			_line->getStyle().setStrokeColor(0xf6, 0xf6, 0xf6);
		}
		// else if(0 == i%2)
		// {
			// _line->getStyle().setStrokeColor(0xde, 0xde, 0xde);
		// }
		else
		{
			_line->getStyle().setStrokeColor(0xfd, 0xfd, 0xfd);
		}
		_line->getStyle().setStrokeWidth(1);
		_line->getStyle().setStrokeOpacity(1.0);
		
		if(0 == i%10)
		{
			std::shared_ptr<Savage::Text> _text = std::make_shared<Savage::Text>();
			char __tmp[64];
			snprintf(__tmp, sizeof(__tmp), "%d", i+1960);
			_text->setText(__tmp);
			_text->setX(i*delta_x);
			_text->setY(0);
			_text->getStyle().setColor(0x00, 0x00, 0x00);
			_text->getStyle().setFillColor(0x00, 0x00, 0x00);
			_svg.addChild(_text);
		}
	}
	
	for(uint32_t y = 0; y <= 100; y+=10)
	{
		std::shared_ptr<Savage::Line> _line = std::make_shared<Savage::Line>();
		_line->setX1(0);
		_line->setY1(100*scale_exp - y*scale_exp);
		_line->setX2(1000);
		_line->setY2(100*scale_exp - y*scale_exp);
		_svg.addChild(_line);
		
		std::shared_ptr<Savage::Text> _text = std::make_shared<Savage::Text>();
		char __tmp[64];
		snprintf(__tmp, sizeof(__tmp), "%d years", y);
		_text->setText(__tmp);
		_text->setX(0);
		_text->setY(100*scale_exp - y*scale_exp);
		_text->getStyle().setColor(0x00, 0x00, 0x00);
		_text->getStyle().setFillColor(0x00, 0x00, 0x00);
		_svg.addChild(_text);
		
		_line->getStyle().setStrokeColor(0xde, 0xde, 0xde);
		_line->getStyle().setStrokeWidth(1);
		_line->getStyle().setStrokeOpacity(1.0);
	}
	
	std::cerr << "wb_region_by_wb_code.size(): " << wb_region_by_wb_code.size() << std::endl;
	
	for(auto r : records)
	{
		if(hasNullData(*r)) continue;
		
		WBRegion region = getWBRegion(r->mCountryCode);
		if(WBREGION_UNKNOWN == region)
		{
			std::cerr << " region unknown: " << r->mCountryCode << std::endl;
			continue;
		}
		
		Savage::Color& color = colorsByRegion[region];
		
		std::shared_ptr<Savage::Path> _path = std::make_shared<Savage::Path>();
		_svg.addChild(_path);
		
		_path->getStyle().setStrokeColor(color.getR(), color.getG(), color.getB());
		_path->getStyle().setStrokeWidth(3);
		_path->getStyle().setStrokeOpacity(0.5);
		_path->setID(r->mCountryCode);
		_path->addClass(toString(region));
		
		std::shared_ptr<Savage::MoveToCommandAbsolute> moveToCmd;
		std::shared_ptr<Savage::LineToCommandAbsolute> lineToCmd;
		
		uint32_t curr_x = 0;
		for(uint32_t i = 1960; i < 2014; i += delta_year)
		{
			// std::shared_ptr<Savage::Line> _line = std::make_shared<Savage::Line>();
			// _line->setX1(curr_x);
			// _line->setY1(100*scale_exp - r->mLifeExpectancy[i]*scale_exp);
			// _line->setX2(curr_x+delta_x);
			// _line->setY2(100*scale_exp - r->mLifeExpectancy[i+delta_year]*scale_exp);
			// _svg.addChild(_line);
			
			if(!moveToCmd)
			{
				__pathCmd = moveToCmd = std::make_shared<Savage::MoveToCommandAbsolute>();
				moveToCmd->addPoint(curr_x, 100*scale_exp - r->mLifeExpectancy[i]*scale_exp);
				_path->addCommand(__pathCmd);
			}
			else if(!lineToCmd)
			{
				__pathCmd = lineToCmd = std::make_shared<Savage::LineToCommandAbsolute>();
				lineToCmd->addPoint(curr_x, 100*scale_exp - r->mLifeExpectancy[i]*scale_exp);
				_path->addCommand(__pathCmd);
			}
			else
			{
				lineToCmd->addPoint(curr_x, 100*scale_exp - r->mLifeExpectancy[i]*scale_exp);
			}
			curr_x += delta_x;
		}
	}
	
	_svg.toString(std::cout);
}

