#ifndef SAVAGE_LISTOFPOINTSCONTAINER_HPP
#define SAVAGE_LISTOFPOINTSCONTAINER_HPP

namespace Savage
{

class ListOfPointsContainer
{
public:
	typedef std::tuple<number_t, number_t> point_t;
	typedef std::vector<point_t> listofpoints_t;

protected:
	std::vector<std::tuple<number_t, number_t>> points;

public:
	inline const listofpoints_t& getPoints() const
	{
		return points;
	}
	
	inline void addPoint(number_t _x, number_t _y)
	{
		points.emplace_back(_x, _y);
	}
};

} // namespace Savage

#endif // SAVAGE_LISTOFPOINTSCONTAINER_HPP