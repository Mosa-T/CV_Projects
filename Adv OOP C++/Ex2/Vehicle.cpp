#include "Vehicle.h"



Vehicle::Vehicle(VehicleType type, int duration,string name)
{
	this->name = name;
	this->type = type;
	this->duration = duration;
}
Vehicle::~Vehicle()
{

}

string Vehicle::getName()
{
	return name;
}

void Vehicle::setName(string name)
{
	if (name.empty())
		throw "Error: you cant set empty string to name of vehicle";
	this->name = name;
}

string Vehicle::to_string()
{
	return "name: " + name + "	Type: " + getType_string() + "	Duration: " + std::to_string(duration);
}

string Vehicle::getType_string()
{
	if (type == Bus)
		return "Bus";
	if (type == Sprinter)
		return "Sprinter";
	if (type == Tram)
		return "Tram";
	return "Rail";
}

Vehicle::Vehicle(const Vehicle &rhs)
{
	name = rhs.name;
	type = rhs.type;
	duration = rhs.duration;
	
}
Vehicle::Vehicle(const Vehicle &&rhs)
{
	name = rhs.name;
	type = rhs.type;
	duration = rhs.duration;
}
Vehicle& Vehicle::operator = (const Vehicle &rhs)
{
	if (this == &rhs)
		return *this;
	name = rhs.name;
	type = rhs.type;
	duration = rhs.duration;
	return *this;
}
Vehicle& Vehicle::operator = (const Vehicle &&rhs)
{
	if (this == &rhs)
		return *this;
	name = rhs.name;
	type = rhs.type;
	duration = rhs.duration;
	return *this;
}


