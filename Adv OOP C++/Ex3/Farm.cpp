#include "Farm.h"

Farm::Farm()
{

}


Farm::Farm(string the_name, Coordinate loc, vector<string> stock) : Zone(the_name, loc, stock)
{
	productivity = stoi(stock[1]);
}
Farm::Farm(const Farm& rhs)
{
	name = rhs.name;
	location = rhs.location;
	stock = rhs.stock;
	productivity = rhs.productivity;

}
Farm::Farm(const Farm&& rhs)
{
	name = rhs.name;
	location = rhs.location;
	stock = rhs.stock;
	productivity = rhs.productivity;
}
Farm& Farm::operator = (const Farm& rhs)
{
	if (this == &rhs)
		return *this;
	name = rhs.name;
	location = rhs.location;
	stock = rhs.stock;
	productivity = rhs.productivity;
	return *this;
}
Farm& Farm::operator = (const Farm&& rhs)
{
	if (this == &rhs)
		return *this;
	name = rhs.name;
	location = rhs.location;
	stock = rhs.stock;
	productivity = rhs.productivity;
	return *this;
}
void Farm::go()
{
	stock += productivity;
}
Farm::~Farm()
{

}

string Farm::getStatus()const
{
	return string("Farm " + name + " at position " + location.to_string() + ", Inventory:" + std::to_string(stock) + ", productivity:" + std::to_string(productivity));
}