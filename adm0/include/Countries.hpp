#ifndef ADM0_HPP
#define ADM0_HPP

#include <string>
#include <vector>

enum EAdminType
{
	ADMINTYPE_SOVEREIGN_COUNTRY,
	ADMINTYPE_COUNTRY,
	ADMINTYPE_DEPENDENCY,
	ADMINTYPE_INDETERMINATE,
	ADMINTYPE_LEASE,
	ADMINTYPE_DISPUTED,
};

enum EContinent
{
	CONTINENT_ASIA,
	CONTINENT_AFRICA,
	CONTINENT_EUROPE,
	CONTINENT_NORTH_AMERICA,
	CONTINENT_SOUTH_AMERICA,
	CONTINENT_OCEANIA,
	CONTINENT_ANTARCTICA,
	CONTINENT_SEVEN_SEAS,
};

enum EUNRegion
{
	UNREGION_ASIA,
	UNREGION_AMERICAS,
	UNREGION_AFRICA,
	UNREGION_EUROPE,
	UNREGION_OCEANIA,
	UNREGION_ANTARCTICA,
	UNREGION_SEVEN_SEAS,
};

enum EWBRegion
{
	WBREGION_SOUTH_ASIA,
	WBREGION_LATIN_AMERICA_AND_CARRIBEAN,
	WBREGION_SUB_SAHARAN_AFRICA,
	WBREGION_EUROPE_AND_CENTRAL_ASIA,
	WBREGION_MIDDLE_EAST_AND_NORTH_AFRICA,
	WBREGION_EAST_ASIA_AND_PACIFIC,
	WBREGION_NORTH_AMERICA,
	WBREGION_ANTARCTICA,
};

struct Country
{
	EAdminType		adminType;
	EContinent		continent;
	EUNRegion		unRegion;
	EWBRegion		wbRegion;
	std::string		sov_name;
	std::string		adm_name;
	std::string		iso_a2;
	std::string		iso_a3;
	std::string		iso_n3;
	std::string		un_a3;
	std::string		wb_a2;
	std::string		wb_a3;
};

extern std::vector<Country> countries;

#endif // ADM0_HPP