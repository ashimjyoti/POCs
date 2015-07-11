#ifndef LIBSVG_TYPES_HPP
#define LIBSVG_TYPES_HPP

#include <vector>
#include <string>
#include <map>

namespace LibSVG
{

typedef double number_t;

enum AngleUnit
{
	ANGLEUNIT_UNDEFINED,
	ANGLEUNIT_DEGREE,
	ANGLEUNIT_RADIAN,
	ANGLEUNIT_GRAD
};

struct Angle
{
	const number_t	v;
	const AngleUnit	u;
	
	Angle(number_t	_v, AngleUnit _u = ANGLEUNIT_UNDEFINED);
};

enum LengthUnit
{
	LENGTHUNIT_UNDEFINED,
	LENGTHUNIT_EM,
	LENGTHUNIT_EX,
	LENGTHUNIT_PX,
	LENGTHUNIT_IN,
	LENGTHUNIT_CM,
	LENGTHUNIT_MM,
	LENGTHUNIT_PT,
	LENGTHUNIT_PC,
	LENGTHUNIT_PR
};

struct Length
{
	const number_t		v;
	const LengthUnit	u;
	
	Length(number_t _v, LengthUnit _u = LENGTHUNIT_UNDEFINED);
};

typedef Length Coord;

struct Classable
{
	std::vector<std::string> mClasses;
};

struct Stylable
{
	std::map<std::string, std::string> mStyles;
};

namespace Private
{

class TListOf1DPointsContainer
{
	std::vector<Coord> x;
};

class TListOf2DPointsContainer : TListOf1DPointsContainer
{
	std::vector<Coord> y;
};

} // namespace Private

enum ShapeType
{
	RECTANGLE,
	CIRCLE,
	ELLIPSE,
	LINE,
	POLYLINE,
	POLYGON
};

struct Shape : public Classable, public Stylable
{
	ShapeType t;
	
	Shape(ShapeType);
};

struct Rectangle : public Shape
{
	Coord x;
	Coord y;
	Length w;
	Length h;
	Length rx;
	Length ry;
	
	Rectangle(Coord&, Coord&, Length&, Length&, Length&, Length&);
};

struct Circle : public Shape
{
	Coord cx;
	Coord cy;
	Length r;
	
	Circle(Coord&, Coord&, Length&);
};

struct Ellipse : public Shape
{
	Coord cx;
	Coord cy;
	Length rx;
	Length ry;
	
	Ellipse(Coord&, Coord&, Length&, Length&);
};

struct Line : public Shape
{
	Coord x1;
	Coord y1;
	Coord x2;
	Coord y2;
	
	Line(Coord&, Coord&, Coord&, Coord&);
};

struct PolyLine : public Shape, public Private::TListOf2DPointsContainer
{
	PolyLine();
};

struct Polygon : public Shape, public Private::TListOf2DPointsContainer
{
	Polygon();
};

class CPath
{
public:
	enum ECommandType
	{
		ECOMMANDTYPE_CLOSEPATH,
		ECOMMANDTYPE_MOVETO_ABSOLUTE,
		ECOMMANDTYPE_MOVETO_RELATIVE,
		ECOMMANDTYPE_LINETO_ABSOLUTE,
		ECOMMANDTYPE_LINETO_RELATIVE,
		ECOMMANDTYPE_LINETO_HORIZONTAL_ABSOLUTE,
		ECOMMANDTYPE_LINETO_HORIZONTAL_RELATIVE,
		ECOMMANDTYPE_LINETO_VERTICAL_ABSOLUTE,
		ECOMMANDTYPE_LINETO_VERTICAL_RELATIVE,
		ECOMMANDTYPE_CURVETO_CUBIC_ABSOLUTE,
		ECOMMANDTYPE_CURVETO_CUBIC_RELATIVE,
		ECOMMANDTYPE_CURVETO_QUADRATIC_ABSOLUTE,
		ECOMMANDTYPE_CURVETO_QUADRATIC_RELATIVE,
		ECOMMANDTYPE_ARC_ABSOLUTE,
		ECOMMANDTYPE_ARC_RELATIVE,
		ECOMMANDTYPE_CURVETO_CUBIC_SMOOTH_ABSOLUTE,
		ECOMMANDTYPE_CURVETO_CUBIC_SMOOTH_RELATIVE,
		ECOMMANDTYPE_CURVETO_QUADRATIC_SMOOTH_ABSOLUTE,
		ECOMMANDTYPE_CURVETO_QUADRATIC_SMOOTH_RELATIVE,
	};
		
	class Command
	{
	public:
		Command(ECommandType _t = ECOMMANDTYPE_CLOSEPATH)
		: t(_t)
		{
		}
		
		inline ECommandType getType() const
		{
			return t;
		}
	private:
		ECommandType t;
	};
	
	template <ECommandType CommandTypeT>
	class _Command : public Command, public Private::TListOf2DPointsContainer
	{
	public:
		_Command()
		: Command(CommandTypeT)
		{
		}
	};
	
	typedef Command ClosePathCommand;
	typedef _Command<ECOMMANDTYPE_MOVETO_ABSOLUTE> MoveToCommandAbsolute;
	typedef _Command<ECOMMANDTYPE_MOVETO_RELATIVE> MoveToCommandRelative;
	typedef _Command<ECOMMANDTYPE_LINETO_ABSOLUTE> LineToCommandAbsolute;
	typedef _Command<ECOMMANDTYPE_LINETO_RELATIVE> LineToCommandRelative;
	typedef _Command<ECOMMANDTYPE_LINETO_HORIZONTAL_ABSOLUTE> HLineToCommandAbsolute;
	typedef _Command<ECOMMANDTYPE_LINETO_HORIZONTAL_RELATIVE> HLineToCommandRelative;
	typedef _Command<ECOMMANDTYPE_LINETO_VERTICAL_ABSOLUTE> VLineToCommandAbsolute;
	typedef _Command<ECOMMANDTYPE_LINETO_VERTICAL_RELATIVE> VLineToCommandRelative;
	typedef _Command<ECOMMANDTYPE_CURVETO_CUBIC_ABSOLUTE> CurveToCommandAbsolute;
	typedef _Command<ECOMMANDTYPE_CURVETO_CUBIC_RELATIVE> CurveToCommandRelative;
	typedef _Command<ECOMMANDTYPE_CURVETO_QUADRATIC_ABSOLUTE> QuadraticCurveToCommandAbsolute;
	typedef _Command<ECOMMANDTYPE_CURVETO_QUADRATIC_RELATIVE> QuadraticCurveToCommandRelative;
	typedef _Command<ECOMMANDTYPE_ARC_ABSOLUTE> ArcCommandRelative;
	typedef _Command<ECOMMANDTYPE_ARC_RELATIVE> ArcToCommandRelative;
	typedef _Command<ECOMMANDTYPE_CURVETO_CUBIC_SMOOTH_ABSOLUTE> SmoothCurveToCommandAbsolute;
	typedef _Command<ECOMMANDTYPE_CURVETO_CUBIC_SMOOTH_RELATIVE> SmoothCurveToCommandRelative;
	typedef _Command<ECOMMANDTYPE_CURVETO_QUADRATIC_SMOOTH_ABSOLUTE> QuadraticSmoothCurveToCommandAbsolute;
	typedef _Command<ECOMMANDTYPE_CURVETO_QUADRATIC_SMOOTH_RELATIVE> QuadraticSmoothCurveToCommandRelative;
private:
	std::vector<Command> mCommands;
public:
	inline const std::vector<Command>& getCommands()
	{
		return mCommands;
	}
	
	inline void addCommand(Command& cmd)
	{
		mCommands.push_back(cmd);
	}
};

struct G : public Classable, public Stylable
{
	std::vector<G> mGs;
	std::vector<Shape> mShapes;
};

struct SVG : public Classable, public Stylable
{
	Coord x;
	Coord y;
	Length w;
	Length h;
	
	std::vector<G> mGs;
	std::vector<Shape> mShapes;
	
	SVG(Coord&, Coord&, Length&, Length&);
};

} // namespace LibSVG

#endif // LIBSVG_TYPES_HPP