#ifndef SAVAGE_TEXT_HPP
#define SAVAGE_TEXT_HPP

#include <string>
#include <vector>
#include "types.hpp"
#include "TextContentElement.hpp"

namespace Savage
{

class Text : public TextContentElement
{
	std::string text;
	number_t	x;
	number_t	y;
public:
	Text()
	: TextContentElement(TEXTCONTENTELEMENTTYPE_TEXT)
	{
	}
	
	const std::string& getText() const
	{
		return text;
	}
	
	void setText(const std::string& _text)
	{
		text = _text;
	}
	
	const number_t& getX() const
	{
		return x;
	}
	
	void setX(const number_t _x)
	{
		x = _x;
	}
	
	const number_t& getY() const
	{
		return y;
	}
	
	void setY(const number_t _y)
	{
		y = _y;
	}
	
	std::ostream& toString(std::ostream& stream)
	{
		return stream
			<< "<text"
			<< " x=\"" << getX() << "\""
			<< " y=\"" << getY() << "\""
			<< " " << getStyle()
			<< " >"
			<< getText()
			<< "</text>"
			<< std::endl;
	}
};

} // namespace Savage

#endif // SAVAGE_TEXT_HPP