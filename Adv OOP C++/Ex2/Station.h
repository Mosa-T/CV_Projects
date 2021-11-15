#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Vehicle.h"

using namespace std;


enum StationType { Intercity, Centraal, Stad};

class Station
{
private:
	string name;
	StationType type;
	vector<Vehicle> transports; // A -> next = B 
	shared_ptr<Station> next;
public:
	Station();
	~Station();
	Station(string name, StationType type, shared_ptr<Station> next);
	Station(Station &); 
	Station(Station &&);
	Station& operator=(Station &);
	Station& operator=(Station &&);
	void setName(string name);
	StationType getType() { return type; };
	string getType_string();
	void setNext(shared_ptr<Station> next);
	shared_ptr<Station> getNext();
	void setWeight(vector<Vehicle> w);
	int getVehicaleDurtion(string nameVehicle);
	vector<Vehicle> getVehicles() { return transports; };
	void addVehicle(Vehicle temp);
	void removeVehicle(string name);
	string getName();
	Station(shared_ptr<Station> rhs);
	string to_string();
};