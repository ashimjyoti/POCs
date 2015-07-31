#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"
#include <cstdio>
#include <iostream>
#include <ctype.h>
#include <string.h>
#include <math.h>

std::string XMLNS("my:");



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

void showPolygon(const Value& p, const Value& polygon)
{
	std::cout << "\t<polygon points=\"";
	for(int i = 0; i < polygon.Size(); i++)
	{
		const Value& p = polygon[i];
		std::cout << 256+(p[0].GetDouble())/100000.0 << "," << 256-(p[1].GetDouble())/100000.0 << " ";
		// std::cout << p[0].GetDouble() << "," << p[1].GetDouble() << " ";
	}
	std::cout << "\"/>" << std::endl;
}

void showGeometry(const Value& p, const Value& g)
{
	std::cout << "<g ";
	showClass(p);
	showStringMember(p, "sovereignt");
	// showStringMember(p, "admin");
	// showStringMember(p, "name");
	// showStringMember(p, "name_long");
	std::cout << ">" << std::endl;
	if(0 == strcmp("Polygon", g["type"].GetString()))
	{
		if(g.HasMember("coordinates"))
		{
			const Value& rings = g["coordinates"];
			showPolygon(p, rings[0]);
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
				showPolygon(p, rings[0]);
			}
		}
	}
	std::cout << "</g>" << std::endl;
}

int main(int argc, char **argv)
{
	FILE *fp = fopen(argv[1], "rb");
	if(NULL == fp)
	{
		printf("file error\n");
		return 0;
	}
	
	char readBuffer[65536];
	rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	
	rapidjson::Document d;
	d.ParseStream(is);
	
	if(d.HasParseError())
	{
		printf("parse error\n");
		return 0;
	}
	
	if(d.IsObject() && d.HasMember("features") && d["features"].IsArray())
	{
	}
	else
	{
		return 0;
	}
	
	rapidjson::Value& features = d["features"];
	std::cout << "<?xml-stylesheet type=\"text/css\" href=\"styles.css\" ?>" << std::endl;
	std::cout << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:my=\"http://my\">" << std::endl;
	for(int i = 0; i < features.Size(); i++)
	{
		const Value& f = features[i];
		const Value& p = f["properties"];
		
		if(f.HasMember("geometry") && f["geometry"].IsObject())
		{
			const Value& g = f["geometry"];
			showGeometry(p, g);
			// if(0 == strcmp("Polygon", g["type"].GetString()))
			// {
				// if(g.HasMember("coordinates"))
				// {
					// const Value& rings = g["coordinates"];
					// showPolygon(p, rings[0]);
				// }
			// }
			// else if(0 == strcmp("MultiPolygon", g["type"].GetString()))
			// {
				// if(g.HasMember("coordinates"))
				// {
					// const Value& polygons = g["coordinates"];
					// for(int i = 0; i < polygons.Size(); i++)
					// {
						// const Value& rings = polygons[i];
						// showPolygon(p, rings[0]);
					// }
				// }
			// }
		}
		std::cout << std::endl;
	}
	std::cout << "</svg>" << std::endl;
	
	fclose(fp);
	return 0;
}
