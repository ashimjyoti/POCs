#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include <cstdio>
#include <vector>
#include <iostream>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <limits>

std::string XMLNS("my:");

std::string YEAR;

struct Transformer
{
	virtual void scale(double& x, double& y) const = 0;
};
// maxx, minx, 200, 0, maxy, miny, 200, 0
struct Scaler : Transformer
{
	const double factorx;
	const double shiftx;
	const double factory;
	const double shifty;
	
	Scaler(
		double old_max_x,
		double old_min_x,
		double new_max_x,
		double new_min_x,
		double old_max_y,
		double old_min_y,
		double new_max_y,
		double new_min_y)
	: factorx((new_max_x - new_min_x) / (old_max_x - old_min_x))
	, shiftx(old_min_x - new_min_x)
	, factory(-1 * factorx)
	, shifty(new_min_y - old_min_y)
	{
	}
	
	inline void scale(double& x, double& y) const
	{
		x = (x - shiftx) * factorx;
		y = (y - shifty) * factory;
	}
};

using namespace rapidjson;

void _fix(std::string &s)
{
	for(std::size_t i = 0; i < s.size(); i++)
	{
		if(!isalnum(s[i])) s[i] = '_';
	}
}

const char *getCountryType(const char *_t)
{
	if(0 == strcmp("Sovereign country", _t))
	{
		return "CT_SOVEREIGN_COUNTRY";
	}
	if(0 == strcmp("Country", _t))
	{
		return "CT_COUNTRY";
	}
	if(0 == strcmp("Dependency", _t))
	{
		return "CT_DEPENDENCY";
	}
	if(0 == strcmp("Indeterminate", _t))
	{
		return "CT_INDETERMINATE";
	}
	if(0 == strcmp("Disputed", _t))
	{
		return "CT_DISPUTED";
	}
	
	return _t;
}

template <typename StreamT>
StreamT& operator << (StreamT& s, const Value& v)
{
	if(v.IsInt())
	{
		return s << v.GetInt();
	}
	if(v.IsString())
	{
		return s << v.GetString();
	}
	if(v.IsDouble())
	{
		return s << v.GetDouble();
	}
	
	return s;
}

void showStringMember(const Value& v, const char *k)
{
	if(v.HasMember(k))
	{
		std::cout << " " << XMLNS << k <<"=\"" << v[k].GetString() << "\"";
	}
}

void showNames(const Value& v)
{
	if(v.IsObject())
	{
		showStringMember(v, "sovereignt");
		showStringMember(v, "admin");
		showStringMember(v, "name");
		showStringMember(v, "name_long");
	}
}

void showFixedClass(const Value& v, const char *name)
{
	if(v.HasMember(name) && (0 != strcmp("-99.000000", v[name].GetString())) && (0 != strcmp("-99", v[name].GetString()))) std::cout << " _" << name << "_" << (v[name].GetString());
}

void showClass(const Value& v)
{
	if(v.IsObject())
	{
		std::cout << "class=\"";
		showFixedClass(v, "iso_a2");
		showFixedClass(v, "iso_a3");
		showFixedClass(v, "iso_n3");
		showFixedClass(v, "un_a3");
		showFixedClass(v, "wb_a2");
		showFixedClass(v, "wb_a3");
		std::cout << "\"";
	}
}

void showFeatue(const Value& v)
{
	
}

double getVal(const std::string& code, const std::string& y, const Value& countries)
{
	// std::cerr << "code: " << code << " y: " << y << std::endl;
	if(countries.HasMember(code.c_str()))
	{
		const Value& country = countries[code.c_str()];
		if(country.HasMember(y.c_str()))
		{
			if(country[y.c_str()].IsDouble())
			{
				return country[y.c_str()].GetDouble();
			}
			else
			{
				std::cerr << "not double: " << code << " year: " << y << std::endl;
			}
		}
		else
		{
			std::cerr << "UNKNOWN_COLOR year: " << code << " year: " << y << std::endl;
		}
	}
	else
	{
		std::cerr << "UNKNOWN_COLOR code: " << code << std::endl;
		return 0.0;
	}
}

struct PaletteColor
{
	double min;
	double max;
	const std::string color;
};
std::vector<PaletteColor> palette = {
	/*
	{15, 20, "#564054"},
	{20, 25, "#594B61"},
	{25, 30, "#5A566F"},
	{30, 35, "#59627B"},
	{35, 40, "#566F86"},
	{40, 45, "#517B8F"},
	{45, 50, "#4D8896"},
	{50, 55, "#49949B"},
	{55, 60, "#49A09E"},
	{60, 65, "#4DAD9E"},
	{65, 70, "#56B89C"},
	{70, 75, "#64C499"},
	{75, 80, "#77CE94"},
	{80, 85, "#8CD88E"}
	{15, 20, "#EF7F86"},
	{20, 25, "#EA7E8C"},
	{25, 30, "#E57D92"},
	{30, 35, "#DE7D97"},
	{35, 40, "#D77D9C"},
	{40, 45, "#CF7DA1"},
	{45, 50, "#C67EA5"},
	{50, 55, "#BC7FA8"},
	{55, 60, "#B280AA"},
	{60, 65, "#A881AC"},
	{65, 70, "#9D82AD"},
	{70, 75, "#9282AD"},
	{75, 80, "#8683AD"},
	{80, 85, "#7B84AB"}
	*/
	
	{15, 20, "#5C2E29"},
	{20, 25, "#693532"},
	{25, 30, "#753B3C"},
	{30, 35, "#814246"},
	{35, 40, "#8D4951"},
	{40, 45, "#98515D"},
	{45, 50, "#A45969"},
	{50, 55, "#AF6176"},
	{55, 60, "#B96A84"},
	{60, 65, "#C37392"},
	{65, 70, "#CC7CA1"},
	{70, 75, "#D486B0"},
	{75, 80, "#DB91BF"},
	{80, 85, "#E19CCF"}
	// {45, 47, "#573F57"},
	// {47, 49, "#57455F"},
	// {49, 51, "#564C66"},
	// {51, 53, "#53526E"},
	// {53, 55, "#505974"},
	// {55, 57, "#4B607A"},
	// {57, 59, "#46677F"},
	// {59, 61, "#406D83"},
	// {61, 63, "#3A7486"},
	// {63, 65, "#347B89"},
	// {65, 67, "#2E818A"},
	// {67, 69, "#2B888A"},
	// {69, 71, "#2A8E89"},
	// {71, 73, "#2D9487"},
	// {73, 75, "#339A84"},
	// {75, 77, "#3CA080"},
	// {77, 79, "#47A57C"},
	// {79, 81, "#54AA77"},
	// {81, 83, "#61AF72"},
	// {83, 85, "#6FB46C"}
}; 

const std::string UNKNOWN_COLOR("#ffffff");

const std::string getColor(double d)
{
	for(auto pc : palette)
	{
		if(pc.min < d && pc.max >= d)
		{
			return pc.color;
		}
	}
	
	return UNKNOWN_COLOR;
}

void showPolygon(const Value& p, const Value& polygon, const Scaler& scaler)
{
	std::cout << "\t<polygon points=\"";
	double x, y;
	for(int i = 0; i < polygon.Size(); i++)
	{
		const Value& p = polygon[i];
		x = p[0].GetDouble();
		y = p[1].GetDouble();
		scaler.scale(x, y);
		std::cout << 100+x << "," << 100+y << " ";
		// std::cout << p[0].GetDouble() << "," << p[1].GetDouble() << " ";
	}
	std::cout << "\"/>" << std::endl;
}

void showGeometry(const Value& p, const Value& g, const Scaler& scaler, const Value& countries)
{
	std::cout << "<g ";
	showClass(p);
	showStringMember(p, "sovereignt");
	// showStringMember(p, "admin");
	// showStringMember(p, "name");
	// showStringMember(p, "name_long");
	double _le = getVal(p["iso_a3"].GetString(), YEAR, countries);
	// std::cerr << "_le: " << _le << std::endl;
	// std::cerr << "getColor(_le): " << getColor(_le) << std::endl;
	std::cout << " style=\"fill: " <<  getColor(_le) << ";stroke:#646464;stroke-opacity:0.05\"";
	std::cout << ">" << std::endl;
	if(0 == strcmp("Polygon", g["type"].GetString()))
	{
		if(g.HasMember("coordinates"))
		{
			const Value& rings = g["coordinates"];
			showPolygon(p, rings[0], scaler);
		}
	}
	else if(0 == strcmp("MultiPolygon", g["type"].GetString()))
	{
		if(g.HasMember("coordinates"))
		{
			const Value& polygons = g["coordinates"];
			for(int i = 0; i < polygons.Size(); i++)
			{
				const Value& rings = polygons[i];
				showPolygon(p, rings[0], scaler);
			}
		}
	}
	std::cout << "</g>" << std::endl;
}

template <int INDEX>
void getMinMax(const Value& features, double& min, double& max)
{
	max = std::numeric_limits<double>::min();
	min = std::numeric_limits<double>::max();
	
	for(int i = 0; i < features.Size(); i++)
	{
		const Value& f = features[i];
		const Value& p = f["properties"];
		
		if(f.HasMember("geometry") && f["geometry"].IsObject())
		{
			const Value& g = f["geometry"];
			if(0 == strcmp("Polygon", g["type"].GetString()))
			{
				if(g.HasMember("coordinates"))
				{
					const Value& rings = g["coordinates"];
					for(int j = 0; j < rings.Size(); j++)
					{
						const Value& polygon = rings[j];
						for(int k = 0; k < polygon.Size(); k++)
						{
							const Value& point = polygon[k];
							if(point[INDEX].GetDouble() > max) max = point[INDEX].GetDouble();
							if(point[INDEX].GetDouble() < min) min = point[INDEX].GetDouble();
						}
					}
				}
			}
			else if(0 == strcmp("MultiPolygon", g["type"].GetString()))
			{
				if(g.HasMember("coordinates"))
				{
					const Value& polygons = g["coordinates"];
					for(int l = 0; l < polygons.Size(); l++)
					{
						const Value& rings = polygons[l];
						for(int j = 0; j < rings.Size(); j++)
						{
							const Value& polygon = rings[j];
							for(int k = 0; k < polygon.Size(); k++)
							{
								const Value& point = polygon[k];
								if(point[INDEX].GetDouble() > max) max = point[INDEX].GetDouble();
								if(point[INDEX].GetDouble() < min) min = point[INDEX].GetDouble();
							}
						}
					}
				}
			}
		}
	}
	// std::cerr << "max: " << max << std::endl;
	// std::cerr << "min: " << min << std::endl;
}

int main(int argc, char **argv)
{
	FILE *fpGeoJSON = fopen(argv[1], "rb");
	if(NULL == fpGeoJSON)
	{
		printf("file error %s\n", argv[1]);
		return 0;
	}
	
	FILE *fpData = fopen(argv[2], "rb");
	if(NULL == fpData)
	{
		printf("file error %s\n", argv[2]);
		return 0;
	}
	
	YEAR = std::string(argv[3]);
	
	rapidjson::Document docGeoJSON;
	rapidjson::Document docData;
	
	char readBuffer[65536];
	{
		rapidjson::FileReadStream is(fpGeoJSON, readBuffer, sizeof(readBuffer));
		docGeoJSON.ParseStream(is);
		
		if(docGeoJSON.HasParseError())
		{
			printf("parse error : GeoJSON\n");
			return 0;
		}
	}
	{
		rapidjson::FileReadStream is(fpData, readBuffer, sizeof(readBuffer));
		docData.ParseStream(is);
		
		if(docData.HasParseError())
		{
			printf("parse error DATA\n");
			return 0;
		}
	}
	
	if(docGeoJSON.IsObject() && docGeoJSON.HasMember("features") && docGeoJSON["features"].IsArray())
	{
	}
	else
	{
		return 0;
	}
	
	rapidjson::Value& features = docGeoJSON["features"];
	
	double minx;
	double maxx;
	double miny;
	double maxy;
	
	getMinMax<0>(features, minx, maxx);
	getMinMax<0>(features, miny, maxy);
	Scaler scaler(maxx, minx, 1000, 0, maxy, miny, 1000, 0);
	
	std::cout << "<?xml-stylesheet type=\"text/css\" href=\"styles.css\" ?>" << std::endl;
	std::cout << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:my=\"http://my\" width=\"1200px\" height=\"1000px\">" << std::endl;
	for(int i = 0; i < features.Size(); i++)
	{
		const Value& f = features[i];
		const Value& p = f["properties"];
		
		if(f.HasMember("geometry") && f["geometry"].IsObject())
		{
			const Value& g = f["geometry"];
			showGeometry(p, g, scaler, docData);
		}
		std::cout << std::endl;
	}
	std::cout << "<text x=\"508\" y=\"850\" style=\"color:#564054;font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-size:72px;font-family:sans-serif;fill:#564054;stroke-width:1;\" >" << YEAR << "</text>" << std::endl;
	double y0 = 750;
	double deltay = 10;
	for(uint32_t i = 0; i < palette.size(); i++)
	{
		std::cout << "<rect x=\"" << 150 << "\" y=\"" << (y0 - deltay * i) << "\" width=\"" << 10 << "\" height=\"" << deltay << "\" style=\"fill:" << palette[i].color << "\"/>" << std::endl;
	}
	std::cout << "<text x=\"165\" y=\"770\" style=\"color:#573F57;font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-size:14px;font-family:sans-serif;fill:#573F57;stroke-width:1;\" >15 years</text>" << std::endl;
	std::cout << "<text x=\"165\" y=\"620\" style=\"color:#7B84AB;font-style:normal;font-variant:normal;font-weight:bold;font-stretch:normal;font-size:14px;font-family:sans-serif;fill:#7B84AB;stroke-width:1;\" >85 years</text>" << std::endl;
	std::cout << "</svg>" << std::endl;
	
	fclose(fpGeoJSON);
	return 0;
}
