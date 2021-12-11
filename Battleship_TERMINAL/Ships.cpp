#include "Ships.h"

	Ships::Ships() {
		carrier_points=5;
		battleship_points=4;
		destroyer_points=3;
		submarine_points=3;
		patrol_boat_points=2;

	}
	void Ships::set_coord_carrier(vector<string> coords) {
		carrier_coord = coords;
	}
	void Ships::set_coord_battleship(vector<string> coords) {
		battleship_coord = coords;
	}
	void Ships::set_coord_destroyer(vector<string> coords) {
		destroyer_coord = coords;
	}
	void Ships::set_coord_submarine(vector<string> coords) {
		submarine_coord = coords;
	}
	void Ships::set_coord_patrol_boat(vector<string> coords) {
		patrol_boat_coord = coords;
	}
	vector<string> Ships::get_carrier_coord() {
		return carrier_coord;
	}
	vector<string> Ships::get_battleship_coord() {
		return battleship_coord;
	}
	vector<string> Ships::get_destroyer_coord() {
		return destroyer_coord;
	}
	vector<string> Ships::get_submarine_coord() {
		return submarine_coord;
	}
	vector<string> Ships::get_patrol_boat_coord() {
		return patrol_boat_coord;
	}
	int Ships::get_points_carrier() {
		return carrier_points;
	}
	int Ships::get_points_battleship() {
		return battleship_points;
		}
	int Ships::get_points_destroyer() {
		return destroyer_points;
	}
	int Ships::get_points_submarine() {
		return submarine_points;
	}
	int Ships::get_points_patrol_boat() {
		return patrol_boat_points;
	}
	void Ships::carrier_hit(string coord) {
		carrier_points--;
		vector<string>::iterator s;
		if ( (s = find(carrier_coord.begin(), carrier_coord.end(), coord)) != carrier_coord.end()) {
			s->assign("X");
		}
	}
	void Ships::battleship_hit(string coord) {
		battleship_points--;
		vector<string>::iterator s;
		if ((s = find(battleship_coord.begin(), battleship_coord.end(), coord)) != battleship_coord.end()) {
			s->assign("X");
		}
	}
	void Ships::destroyer_hit(string coord) {
		destroyer_points--;
		vector<string>::iterator s;
		if ((s = find(destroyer_coord.begin(), destroyer_coord.end(), coord)) != destroyer_coord.end()) {
			s->assign("X");
		}
	}
	void Ships::submarine_hit(string coord) {
		submarine_points--;
		vector<string>::iterator s;
		if ((s = find(submarine_coord.begin(), submarine_coord.end(), coord)) != submarine_coord.end()) {
			s->assign("X");
		}
	}
	void Ships::patrol_boat_hit(string coord) {
		patrol_boat_points--;
		vector<string>::iterator s;
		if ((s = find(patrol_boat_coord.begin(), patrol_boat_coord.end(), coord)) != patrol_boat_coord.end()) {
			s->assign("X");
		}
	}
