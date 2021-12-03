#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Castle.h"
#include "Thug.h"
#include "Knight.h"
#include "FileOpener.h"
#include "View.h"
#include "Farm.h"
using namespace std;
class Model
{
private :
	Model(){  }
	~Model() {  }
	static Model* ptr;
	int time;
	vector<vector<string>> attacksHeld;
	AgentFactory af;
	vector<shared_ptr<Castle>> castles;
	vector<shared_ptr<Farm>> farms;
	//vector<shared_ptr<Peasant>> peasants;
	vector<shared_ptr<Agent>> agents; 
	vector<shared_ptr<Zone>> zones;
	shared_ptr<Castle> get_castle(string name);
	vector<shared_ptr<Castle>> get_castleS();
	shared_ptr<Farm> get_farm(string name);
	vector<shared_ptr<Farm>> get_farmS();

public:
	static void ResetInstance()
	{
		delete ptr;
		ptr = NULL; 
	}
	void addAttacks(vector<string> a);
	int getTime() { return time; }
	void go();
	void set_on_course(vector<string> tokens);
	static Coordinate create_coordinate(string str_x, string str_y); //foramt must be (x, y) 
	static Model& get_Instance();
	Model(const Model&) = delete;
	Model& operator= (const Model&) = delete;
	Model(const Model&&) = delete;
	Model& operator= (const Model&&) = delete;
	void initModel(int argc, char* argv[]);
	void set_to_default();
	void print_status();
	bool agent_exist(string str);
	shared_ptr<Agent> find_agent(string str);
	void create_agent(AgentFactory::TYPE type, vector<string> tokens);
	bool is_castle_exist(string name);
	bool is_farm_exist(string name);
	bool is_castle_exist(Coordinate pos);
	bool is_farm_exist(Coordinate pos);
	bool check_if_peasant(string name);
	shared_ptr<Knight> get_knight_given_name(string name);
	shared_ptr<Thug> get_thug_given_name(string name);
	void stop_agent(string name);
	void set_destination_for_knight(vector<string> tokens);
	void swapForFirst(string);
	void position(vector<string>);
	void attack(vector<string> tokens);
	bool safe_to_attack(Coordinate );
	shared_ptr<Peasant> get_peasant_given_name(string name);
	shared_ptr<Farm> get_farm_given_name(string name);
	//shared_ptr<Zone> get_Zone_given_name(string name);
	shared_ptr<Castle> get_castle_given_name(string name);
	void updateView();
	void start_peasant_work(vector<string> tokens);
	void peasant_status(string);
	
};

