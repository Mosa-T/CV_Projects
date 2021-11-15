#pragma once
#include <iostream>
#include <string> 
#include <fstream>
#include <vector>
#include <algorithm> 
#include <sstream>
#include "Station.h"
#include <stdlib.h>
#include <ctype.h>
#include "WaitingTimes.h"
using namespace std;

class FileOpener
{
private:
	shared_ptr<Station> origin;
	shared_ptr<Station> originRev;
	shared_ptr<Station> list;
	vector<shared_ptr<Station>> *stationGraph;
	vector<shared_ptr<Station>> *stationGraphRev;
	vector<string> split(const string& str, const string& delim);
	int getIndexGivenNameInStationGraph(string name);
	bool has_any_digits(const string& s);
	int getIndexGivenNameInStationGraphRev(string name);
	void setIntoStationGraphGivenName(string whereTo, shared_ptr<Station> obj);
	void setIntoStationGraphGivenNameRev(string whereTo, shared_ptr<Station> obj);
	VehicleType getVehicleTypeFromFileName(string filename);
	StationType getStationTypeFromString(string name);
public:
	void initOpenFile(string fileName, vector<shared_ptr<Station>> &stationGraph, vector<shared_ptr<Station>>& stationGraphRev);
	FileOpener(){
		stationGraph = nullptr;
		//packageGraph = nullptr;
	}
	static WaitingTimes openfileConfig(string fileName);
	
};