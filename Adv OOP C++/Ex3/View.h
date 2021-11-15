#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "Coordinate.h"
#include <iomanip>
#include <unordered_map> 
#include <map>



struct pair_hash {
	template <typename T1, typename T2>
	std::size_t operator () (const std::pair<T1, T2>& p) const {

		return std::hash<T1>{}(p.first)^ std::hash<T2>{}(p.second);
		
	}
};


class View
{
public:
	static View& get_Instance();
	void show();
	void size(string str_i); //changes display_size
	void zoom(string ); //changes scale variable. positive only
	void pan(vector<string> xy);
	void set_to_default() { origin.SetX(0); origin.SetY(0); scale = 2; display_size = 25; }
	void updates(float x, float y, string id);
	static void ResetInstance()
	{
		delete ptr3;
		ptr3 = NULL;
	}
private:
	
	bool has_only_digits(string str)
	{
		if (str[0] == '-')
		{
			throw string("ERROR: number must be positive");
		}
		return all_of(begin(str), end(str),
			[](char c) { return isdigit(c); });
	}
	bool print_obj(int x, int y); // return true if printed and marks the printed
	static View* ptr3;
	int display_size; //how many rows and cols to show default at 25 (the default size for the vector which is 25x25 by default, ranges from 6 to 30)
	Coordinate origin; //panning changes this thing. starts at (-10, -10) maybe?
	double scale; //jumps per row/col. positive only
	map<string, pair<float, float>> idAsKey;
	map<pair<int, int>, string> Coordinate_As_key;
	unordered_map<string, bool> isObj_printedmap;
	vector<vector<string>> arrayDisplay;
	bool updated;
	View();
	~View() {};
};