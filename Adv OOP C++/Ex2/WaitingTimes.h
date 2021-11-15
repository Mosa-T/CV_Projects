#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Vehicle.h"
#include "Station.h"

using namespace std;

class WaitingTimes
{
private:
	int bus, tram, sprinter, rail;
	int intercity, centraal, stad;
	vector<string> split(const string& str, const string& delim);
	void setWaitingTime(string type, string time);
	void setDefWaitingTimes();
public:
	WaitingTimes() { setDefWaitingTimes(); };
	~WaitingTimes() {};
	WaitingTimes(vector<string> data);

	
	
	int getWaitingTime(VehicleType type);
	int getWaitingTime(StationType type);
	
};