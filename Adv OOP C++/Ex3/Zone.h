#pragma once
#include <iostream>
#include <string>
#include "Coordinate.h"
#include <vector>
#include <memory>
using namespace std;
class Zone
{
public:
	Zone();
	Zone(string the_name, Coordinate loc, vector<string> stock);
	virtual string getName() { return name; };
	virtual string getType() = 0;
	virtual void restore_default() = 0;
	virtual string getStatus() const = 0;
	virtual Coordinate getLocation() { return location; }
	virtual int get_stock() const { return stock; }
	virtual void set_stock(int newStock) { this->stock = newStock; }
	virtual ~Zone() {}


protected:
	string name;
	Coordinate location;
	int stock;
	int starting_stock;
};