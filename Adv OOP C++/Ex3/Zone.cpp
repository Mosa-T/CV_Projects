#include "Zone.h"

Zone::Zone()
{

}

Zone::Zone(string the_name, Coordinate loc, vector<string> stock)
{
	name = the_name;
	location = loc;
	this->stock = stoi(stock[0]);
	starting_stock = this->stock;
}
