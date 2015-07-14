#ifndef SAVAGE_SVG_HPP
#define SAVAGE_SVG_HPP

#include <vector>
#include <memory>

#include "Coord.hpp"
#include "SVGElement.hpp"
#include "StructuralElement.hpp"

namespace Savage
{

class SVG : public StructuralElement
{
	Coord	x;
	Coord	y;
	Length	w;
	Length	h;
	
	std::vector<std::shared_ptr<SVGElement> > children;
public:
	inline SVG()
	: StructuralElement(STRUCTURALELEMENTTYPE_SVG)
	, x(0)
	, y(0)
	, w(0)
	, h(0)
	{
	}
	
	inline SVG(const Coord& _x, const Coord& _y, const Length& _w, const Length& _h)
	: StructuralElement(STRUCTURALELEMENTTYPE_SVG)
	, x(_x)
	, y(_y)
	, w(_w)
	, h(_h)
	{
	}
	
	inline const Coord& getX() const
	{
		return x;
	}
	
	inline const Coord& getY() const
	{
		return y;
	}
	
	inline const Length& getW() const
	{
		return w;
	}
	
	inline const Length& getH() const
	{
		return h;
	}
	
	inline void setX(const Coord& _x)
	{
		x = _x;
	}
	
	inline void setY(const Coord& _y)
	{
		y = _y;
	}
	
	inline void setW(const Length& _w)
	{
		w = _w;
	}
	
	inline void setH(const Length& _h)
	{
		h = _h;
	}
	
	inline const std::vector<std::shared_ptr<SVGElement> >& getChildren() const
	{
		return children;
	}
	
	inline void addChild(const std::shared_ptr<SVGElement>& child)
	{
		children.push_back(child);
	}
	
	std::ostream& toString(std::ostream& stream)
	{
		stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>" << std::endl;
		stream
			<< "<svg"
			<< " x=\"" << getX() << "\""
			<< " y=\"" << getY() << "\""
			<< " width=\"" << getW() << "\""
			<< " height=\"" << getH() << "\""
			<< " xmlns=\"http://www.w3.org/2000/svg\">"
			<< std::endl;
		for(auto child : getChildren())
		{
			child->toString(stream);
		}
		stream
			<< "</svg>"
				<< std::endl;
				
		return stream;
	}
};

} // namespace Savage

#endif // SAVAGE_SVG_HPP