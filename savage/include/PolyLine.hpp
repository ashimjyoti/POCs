#ifndef SAVAGE_POLYLINE_HPP
#define SAVAGE_POLYLINE_HPP

#include <vector>
#include <tuple>

#include "types.hpp"
#include "ShapeElement.hpp"
#include "ListOfPointsContainer.hpp"

namespace Savage
{

class PolyLine : public ShapeElement, public ListOfPointsContainer
{
public:
	typedef ListOfPointsContainer::point_t point_t;
	typedef ListOfPointsContainer::listofpoints_t listofpoints_t;

public:
	inline PolyLine()
	: ShapeElement(SHAPEELEMENTTYPE_POLYLINE)
	{
	}
	
	std::ostream& toString(std::ostream& stream)
	{
		stream
			<< "<polyline points=\"";
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

#endif // SAVAGE_POLYLINE_HPP