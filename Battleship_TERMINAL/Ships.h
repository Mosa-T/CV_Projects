#pragma once
#ifndef _SHIPS_H_
#define _SHIPS_H_
#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iomanip>
#include <map>
#include <utility>
#include <iterator>




using namespace std;

class Ships {
private:
	int carrier_points;
	int battleship_points;
	int destroyer_points;
	int submarine_points;
	int patrol_boat_points;

	vector<string> carrier_coord;
	vector<string> battleship_coord;
	vector<string> destroyer_coord;
	vector<string> submarine_coord;
	vector<string> patrol_boat_coord;
public:
	Ships();
	void set_coord_carrier(vector<string> coords);
	void set_coord_battleship(vector<string> coords);
	void set_coord_destroyer(vector<string> coords);
	void set_coord_submarine(vector<string> coords);
	void set_coord_patrol_boat(vector<string> coords);
	vector<string> get_carrier_coord();
	vector<string> get_battleship_coord();
	vector<string> get_destroyer_coord();
	vector<string> get_submarine_coord();
	vector<string> get_patrol_boat_coord();
	int get_points_carrier();
	int get_points_battleship();
	int get_points_destroyer();
	int get_points_submarine();
	int get_points_patrol_boat();
	void carrier_hit(string coord);
	void battleship_hit(string coord);
	void destroyer_hit(string coord);
	void submarine_hit(string coord);
	void patrol_boat_hit(string coord);
};









#endif
