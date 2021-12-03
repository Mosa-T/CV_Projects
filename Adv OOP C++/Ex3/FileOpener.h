#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <sstream>
#include <fstream>
#include <memory>
#include "AgentFactory.h"
#include "Peasant.h"
#include "Coordinate.h"
#include "Castle.h"
#include "Farm.h"
#include "ZoneFactory.h"

using namespace std;

class FileOpener
{
private:
	ZoneFactory af;
	vector<shared_ptr<Zone>> zones;
	bool has_only_letters(string str);
	int get_number_from_string(string str);//this function deletes its first charcter for format porpuses check function.
	//bool peasant_exist_in_database(string str);
public:
	FileOpener();
	~FileOpener();
	static vector<string> split(const string& str, const string& delim);
	bool has_any_digits(const string& s);
	void open_file_castle(string fileName);
	void open_file_farm(string filename);
	//vector<shared_ptr<Zone>>& getCastles();
	//vector<shared_ptr<Peasant>>& getPeasant();
	//vector<shared_ptr<Zone>> &getFarms();
	vector<shared_ptr<Zone>>& getZones() { return zones; };
	shared_ptr<Zone> findCastle(string);
	shared_ptr<Zone> findFarm(string);
};