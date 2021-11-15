#include "Station.h"

Station::Station()
{

}

Station::Station(string name, StationType type, shared_ptr<Station> next) 
{
	this->name = name;
	this->transports = transports;
	this->next = next;
}
Station::~Station()
{

}
Station::Station(Station &rhs)
{
	this->name = rhs.name;

	this->transports = rhs.transports;
	this->next = rhs.next;
}


Station::Station(shared_ptr<Station> rhs)
{
	this->name = rhs->name;

	this->transports = rhs->transports;
	this->next = rhs->next;
}

Station::Station(Station &&rhs)
{

	this->name = rhs.name;
	
	this->transports = rhs.transports;
	this->next = rhs.next;
}
Station& Station::operator = (Station &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	this->name = rhs.name;

	this->transports = rhs.transports;
	this->next = rhs.next;
	return *this;
}
Station& Station::operator = (Station &&rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	this->name = rhs.name;
	this->transports = rhs.transports;
	this->next = rhs.next;
	return *this;
}

void Station::setName(string name)
{
	this->name = name;
}
string Station::getName()
{
	return name;
}



void Station::setNext(shared_ptr<Station> next) {
	this->next = next;
}

shared_ptr<Station> Station::getNext() {
	return this->next;
}

void Station::setWeight(vector<Vehicle> w){
	transports = w;
}

void Station::addVehicle(Vehicle temp)
{
	for (int i = 0; i < transports.size(); i++)
	{
		if (transports[i].getName() == temp.getName())
		{
			if (transports[i].getDuartion() < temp.getDuartion())
			{
				transports[i].setDuration(temp.getDuartion());
				return;
			}
		}
	}
	transports.push_back(temp);
}

void Station::removeVehicle(string name)
{
	for (auto it = transports.begin(); it != transports.end(); ++it)
	{
		if ((*it).getName() == name)
			transports.erase(it);
	}
}


int Station::getVehicaleDurtion(string name)
{
	for (int i = 0; i < transports.size(); i++)
	{
		if (transports[i].getName() == name)
		{
			return transports[i].getDuartion();
		}
	}
	return -1;
}

string Station::to_string()// need to fix this
{
	string str = "name:	" + name + "	Type: " + getType_string();
	if (transports.size() > 0)
	{
		str += " Vehicels: "; 
		for (int i = 0; i < transports.size(); i++)
			str +=" " + transports[i].to_string() + " ";
	}
	return str;
}

string Station::getType_string()
{
	if (type == Intercity)
		return "Intercity";
	if (type == Centraal)
		return "Centraal";
	return "Stad";
}