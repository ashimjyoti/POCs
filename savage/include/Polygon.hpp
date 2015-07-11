#ifndef SAVAGE_POLYGON_HPP
#define SAVAGE_POLYGON_HPP

#include <vector>
#include <tuple>

#include "types.hpp"
#include "ShapeElement.hpp"
#include "ListOfPointsContainer.hpp"

namespace Savage
{

class Polygon : public ShapeElement, public ListOfPointsContainer
{
public:
	typedef ListOfPointsContainer::point_t point_t;
	typedef ListOfPointsContainer::listofpoints_t listofpoints_t;

public:
	inline Polygon()
	: ShapeElement(SHAPEELEMENTTYPE_POLYGON)
	{
	}
	
	std::ostream& toString(std::ostream& stream)
	{
		stream
			<< "<polygon points=\"";
		for(auto p : points)
		{
			stream << std::get<0>(p) << "," << std::get<1>(p) << " ";
		}
		stream
			<< "\" />"
			<< std::endl;
	}
};

} // namespace Savage

#endif // SAVAGE_POLYGON_HPP