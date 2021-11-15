#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Station.h"
#include "FileOpener.h"
#include <algorithm>
#include <climits> 

using namespace std;

class WorldMap
{
private:
	FileOpener file;
	vector<shared_ptr<Station>> stationGraph;
	vector<shared_ptr<Station>> stationGraphRev;
	WaitingTimes times;
	vector<shared_ptr<Station>> getReversedGraph(vector<shared_ptr<Station>>);
	shared_ptr<Station> findLocation(shared_ptr<Station> a, string name);
	int getIndexGivenName(vector<shared_ptr<Station>> a, string name);
	bool doesContainVehcileTypeRev(VehicleType type, vector<Vehicle> cars);
	vector<string> getallConectedViaTypeVehicleRev(vector<string> need_to_check, VehicleType typeV, vector<string> checked);
	int getIndexGivenNameInStationGraphRev(string name);
	void getInbound(string name, int i);
	string isSetOutPutFile(vector<string> args);
	string isSetConfigFile(vector<string> args);
	string of_file_string;
	vector<string> split(const string& str, const string& delim);
	void printGraphs();
	void printType(VehicleType a);
	void getOutbound(string name);
	int getIndexGivenNameInStationGraph(string name);
	bool doesContainVehcileType(VehicleType type, vector<Vehicle> cars);
	vector<string> getallConectedViaTypeVehicle(vector<string> need_to_check, VehicleType typeV, vector<string> checked);
	void printAllOutBound(vector<string> bus, vector<string> trams, vector<string> sprinters, vector<string> rails);
	void printAllInBound(vector<string> bus, vector<string> trams, vector<string> sprinters, vector<string> rails);
	bool findName(vector<Station> a, string name);
	StationType getStationTypeFromString(string name);
	bool doesContainVehcileTypeName(string type, vector<Vehicle> cars);
	void uniExpress(string source, string traget);
	void printUniExpress(int bus, int trams, int sprinters, int rails);
	void multiExpress(string source, string dest);
	void printUniExpress(int theBest);
	vector<vector<int>> getGraphGivenType(vector<shared_ptr<Station>> origin, VehicleType type);
	int neighborNode(int i, int j, VehicleType type);
	int getShortestDurationGivenTypeNVehicles(VehicleType type, vector<Vehicle> vehicles);
	int neighborNodeMult(int i, int j, VehicleType type);
	int getShortestRouteMult(string source, string target, VehicleType type);
	int getShortestDurationGivenTypeNVehiclesMult(VehicleType type, vector<Vehicle> vehicles, StationType statType);
	string givenIndexReturnName(int i);
	int minDistance(vector<int> dist, vector<bool> sptSet, int V);
	vector<int> dijkstra(vector<vector<int>> graph, int src);
	int getShortestRouteGivenVehicle(string source, string target, VehicleType);
	int getShortestRouteGivenVehicleMult(string source, string target, VehicleType type);
	vector<vector<int>> getGraphGivenTypeMult(vector<shared_ptr<Station>> origin, VehicleType type);
public:
	WorldMap();
	WorldMap(string fileName);
	WorldMap(int argc, char *argv[]);
	//WorldMap(WorldMap &);
	//WorldMap(WorldMap &&);
	//WorldMap& operator=(WorldMap &);
	//WorldMap& operator=(WorldMap &&);
	void run();
};