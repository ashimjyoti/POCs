#ifndef SAVAGE_PATH_HPP
#define SAVAGE_PATH_HPP

#include "Point2D.hpp"

namespace Savage
{

class PathCommand
{
public:
	virtual std::ostream& toString(std::ostream&) = 0;
};

class ClosePathCommand : public PathCommand
{
public:
	virtual std::ostream& toString(std::ostream& stream)
	{
		return stream << " Z ";
	}
};

namespace __Private
{

template <int ...>
struct index_sequence {};

template <int N, int ...S>
struct make_sequence : make_sequence<N-1, N-1, S...> {};

template <int ...S>
struct make_sequence<0, S...> {
    typedef index_sequence<S...> type;
};

template <char C, typename...CoordsT>
class __PathCommandWithPoints : public PathCommand
{
public:
	typedef std::tuple<CoordsT...>	point_t;
	typedef std::vector<point_t>	listofpoints_t;
protected:
	listofpoints_t points;
	
	
	void toString(std::ostream& stream, number_t n)
	{
		stream << n << " ";
	}
	void toString(std::ostream& stream, number_t n1, number_t n2)
	{
		stream << n1 << "," << n2 << " ";
	}
	
	void toString(std::ostream& stream, number_t n1, number_t n2, number_t n3, number_t n4)
	{
		stream << n1 << "," << n2 << " " << n3 << "," << n4 << " ";
	}
	
	void toString(std::ostream& stream, number_t n1, number_t n2, number_t n3, number_t n4, number_t n5, number_t n6)
	{
		stream << n1 << "," << n2 << " " << n3 << "," << n4 << " " << n5 << "," << n6 << " ";
	}
	
	void toString(std::ostream& stream, number_t n1, number_t n2, number_t n3, number_t n4, number_t n5, number_t n6, number_t n7)
	{
		stream << n1 << "," << n2 << " " << n3 << " " << n4 << "," << n5 << " " << n6 << "," << n7 << " ";
	}
	
	template <int..._Indices>
	void toString(std::ostream& stream, const point_t& p, index_sequence<_Indices...>)
	{
		toString(stream,  std::get<_Indices>(p)...);
	}
public:
	inline const listofpoints_t& getPoints() const
	{
		return points;
	}
	
	inline void addPoint(CoordsT...coords)
	{
		points.emplace_back(coords...);
	}
	
	virtual std::ostream& toString(std::ostream& stream)
	{
		stream << C;
		for(auto p : points)
		{
			toString(stream, p, typename make_sequence<sizeof...(CoordsT)>::type());
		}
		return stream;
	}
};

} // namespace __Private

typedef __Private::__PathCommandWithPoints<'M', number_t, number_t> MoveToCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'m', number_t, number_t> MoveToCommandRelative;
typedef __Private::__PathCommandWithPoints<'L', number_t, number_t> LineToCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'l', number_t, number_t> LineToCommandRelative;

typedef __Private::__PathCommandWithPoints<'H', number_t> HLineToCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'h', number_t> HLineToCommandRelative;
typedef __Private::__PathCommandWithPoints<'V', number_t> VLineToCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'v', number_t> VLineToCommandRelative;

typedef __Private::__PathCommandWithPoints<'C', number_t, number_t, number_t, number_t, number_t, number_t> CurveToCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'c', number_t, number_t, number_t, number_t, number_t, number_t> CurveToCommandRelative;

typedef __Private::__PathCommandWithPoints<'S', number_t, number_t, number_t, number_t> SCurveToCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'s', number_t, number_t, number_t, number_t> SCurveToCommandRelative;

typedef __Private::__PathCommandWithPoints<'Q', number_t, number_t, number_t, number_t> QCurveToCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'q', number_t, number_t, number_t, number_t> QCurveToCommandRelative;

typedef __Private::__PathCommandWithPoints<'T', number_t, number_t> SQCurveToCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'t', number_t, number_t> SQCurveToCommandRelative;

typedef __Private::__PathCommandWithPoints<'A', number_t, number_t, number_t, number_t, number_t, number_t, number_t> ArcCommandAbsolute;
typedef __Private::__PathCommandWithPoints<'a', number_t, number_t, number_t, number_t, number_t, number_t, number_t> ArcCommandRelative;

class Path : public ShapeElement
{
	std::vector<std::shared_ptr<PathCommand>> commands;
public:
	inline Path()
	: ShapeElement(SHAPEELEMENTTYPE_PATH)
	{
	}
	
	inline const std::vector<std::shared_ptr<PathCommand>>& getCommands() const
	{
		return commands;
	}
	
	inline void addCommand(std::shared_ptr<PathCommand>& command)
	{
		commands.push_back(command);
	}
	
	virtual std::ostream& toString(std::ostream& stream)
	{
		stream << "<path d=\"";
		for(auto c : commands)
		{
			c->toString(stream);
		}
		stream << "\" />" << std::endl;
		return stream;
	}
};

} // namespace Savage

#endif // SAVAGE_PATH_HPP