#include "Castle.h"

Castle::Castle()
{

}

Castle::Castle(string the_name, Coordinate loc, vector<string> stock): Zone(the_name,loc,stock)
{

}
Castle::Castle(const Castle &rhs) 
{
	name = rhs.name;
	location = rhs.location;
	stock = rhs.stock;
}
Castle::Castle(const Castle &&rhs)
{
	name = rhs.name;
	location = rhs.location;
	stock = rhs.stock;
}
Castle& Castle::operator = (const Castle &rhs)
{
	if (this == &rhs)
		return *this;
	name = rhs.name;
	location = rhs.location;
	stock = rhs.stock;
	return *this;
}
Castle& Castle::operator = (const Castle &&rhs)
{
	if (this == &rhs)
		return *this;
	name = rhs.name;
	location = rhs.location;
	stock = rhs.stock;
	return *this;
}
Castle::~Castle()
{

}

string Castle::getStatus()const
{
	return string("Castle " + name +
		" at position " + 
		location.to_string() +
		", Inventory:" + 
		std::to_string(stock));
}