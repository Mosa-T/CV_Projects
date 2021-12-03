#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

enum VehicleType { Bus, Tram, Sprinter, Rail };

class Vehicle
{
private:
	string name;
	VehicleType type;
	int duration;
public:
	Vehicle() {};
	Vehicle(VehicleType type, int duration, string name);
	~Vehicle();
	Vehicle(const Vehicle&);
	Vehicle(const Vehicle&&);
	Vehicle& operator=(const Vehicle&);
	Vehicle& operator=(const Vehicle&&);
	const VehicleType getType() { return type; };
	void setType(const VehicleType type) { this->type = type; };
	const int getDuartion() { return duration; };
	void setDuration(const int dur) { duration = dur; };
	string getName();
	void setName(string name);
	string to_string();
	string getType_string();



};