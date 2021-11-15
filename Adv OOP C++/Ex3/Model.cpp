#include "Model.h"


Model* Model::ptr = 0;

void Model::go()
{
	time++;
	for (shared_ptr<Agent>temp : agents) {
		temp->go(); //update for all agents
	}
	vector<shared_ptr<Farm>> temp2 = get_farmS();
	for (shared_ptr<Farm>temp : temp2) {
		temp->go();
	}
	
	for (int i = 0; i < attacksHeld.size(); i++) {
		attack(attacksHeld[i]);
	}
	attacksHeld.clear();
}

Model& Model::get_Instance()
{
	if (!ptr)
		ptr = new Model();
	return *ptr;
}

void Model::set_on_course(vector<string> tokens)
{
	if (tokens.size() == 4)//thug
	{
		int deg = stoi(tokens[2]);
		float spd = stof(tokens[3]);
		shared_ptr<Thug> thug = get_thug_given_name(tokens[0]);
		if (thug->getType() != "Thug")
			throw string(tokens[0] + "is not a thug, cannot get speed");
		thug->course(deg, spd);
	}
	else if (tokens.size() == 3)// knight/peasant
	{
		if (!check_if_peasant(tokens[0])) {
			float deg = stof(tokens[2]);
			auto st = get_knight_given_name(tokens[0]);
			st->course(deg, 1);
		}
		else {
			float deg = stof(tokens[2]);
			auto st = get_peasant_given_name(tokens[0]);
			st->course(deg, 1);
		}
	}
}


void Model::initModel(int argc, char* argv[])
{
	if(argc != 3)
		throw string("Invalid arguments in init");
	FileOpener fo;
	fo.open_file_castle(argv[1]);
	fo.open_file_farm(argv[2]);
	this->zones = move(fo.getZones());
	time = 0;
}

void Model::set_to_default()
{

	for (unsigned int i = 0; i < zones.size(); i++)
	{
		zones[i]->restore_default();
	}
	agents.resize(0);
}

void Model::print_status()
{
	for (unsigned int i = 0; i < zones.size(); i++)
	{
		cout  <<zones[i]->getStatus() << endl;
	}
	
	for (unsigned int i = 0; i < agents.size(); i++)
	{
		cout  << agents[i]->getStatus() << endl;
	}
}

bool Model::agent_exist(string str)
{
	for (unsigned int i = 0; i < agents.size(); i++)
	{
		if (agents[i]->getName() == str)
			return true;
	}
	return false;
}



shared_ptr<Agent> Model::find_agent(string str)
{
	for (unsigned int i = 0; i < agents.size(); i++)
	{
		if (agents[i]->getName() == str)
			return agents[i];
	}
	throw string("Agent wasn't found in database");
}



void Model::create_agent(AgentFactory::TYPE type, vector<string> tokens)
{
	int last_added = agents.size();
	shared_ptr<Agent> temp = af.createVehicle(type, tokens);
	if (tokens.size() == 3)
	{
		string first = zones[0]->getName();
		swapForFirst(tokens[2]);
		temp->set_zone_at(this->zones);
		swapForFirst(first);
	}
	agents.push_back(temp);
}

void Model::swapForFirst(string a) {
	for (int i = 0; i < zones.size(); i++) {
		if (zones[i]->getName() == a)
			std::swap(zones[i], zones[0]);
	}
}

void Model::position(vector<string> tokens) 
{
	shared_ptr<Agent> temp = find_agent(tokens[0]);
	if (tokens.size() == 5)  
	{
		if (temp->getType() != "Thug")
		{
			throw string(tokens[0] + "is not a thug can't have speed");
		}
		if (!Coordinate::check_correct_float_string(tokens[4]))
			throw string("given speed incorrect");
		temp->position(create_coordinate(tokens[2]," "+tokens[3]), stof(tokens[4]));
		return;
	}
	else //its a knight
		if (temp->getType() != "Knight" && temp->getType() != "Peasant")
		{
			throw string(tokens[0] + "is a knight/peasant can't have speed");
		}
		temp->position(create_coordinate(tokens[2], " " + tokens[3]), 1);
	
}


void Model::stop_agent(string name)
{
	for (unsigned int i = 0; i < agents.size(); i++)
	{
		if (agents[i]->getName() == name)
		{
			agents[i]->stop();
			return;
		}
	}
	throw string("name wasn't found in database");
}


shared_ptr<Castle> Model::get_castle(string name)
{
	for (unsigned int i = 0; i < castles.size(); i++)
	{
		if (castles[i]->getName() == name)
			return castles[i];
	}
	return nullptr;
}

vector<shared_ptr<Castle>> Model::get_castleS()
{
		for (unsigned int i = 0; i < zones.size(); i++)
		{
			if (zones[i]->getType() == "Castle")
				castles.push_back(dynamic_pointer_cast<Castle>(zones[i]));
		}
	return move(this->castles);
}

shared_ptr<Farm> Model::get_farm(string name)
{
	for (unsigned int i = 0; i < farms.size(); i++)
	{
		if (farms[i]->getName() == name)
			return farms[i];
	}
	return nullptr;
}

vector<shared_ptr<Farm>> Model::get_farmS()
{
	for (unsigned int i = 0; i < zones.size(); i++)
	{
		if (zones[i]->getType() == "Farm")
			farms.push_back(dynamic_pointer_cast<Farm>(zones[i]));
	}
	return move(this->farms);
}


bool Model::is_castle_exist(string name)
{
	for (unsigned int i = 0; i < zones.size(); i++)
	{
		if (zones[i]->getName() == name)
			return true;
	}
	return false;
}
bool Model::is_farm_exist(string name)
{
	for (unsigned int i = 0; i < zones.size(); i++)
	{
		if (zones[i]->getName() == name)
			return true;
	}
	return false;
}
Coordinate Model::create_coordinate(string str_x, string str_y) 
{
	float x, y;
	
	string temp("(");
	if (str_x.at(0) != temp[0])
		throw string("wrong input in setting Coordinate");
	temp = ",";
	if (str_x.at(str_x.size()-1) != temp[0])
		throw string("wrong input in setting Coordinate");
	temp = " ";
	if (str_y[0] != temp[0])
		throw string("wrong input in setting Coordinate");
	int last_index = str_y.size() - 1;
	temp = ")";
	if (str_y[last_index] != temp[0])
		throw string("wrong input in setting Coordinate");
	////////////////////////////////////////////////////delete first too charters and last then do split then stof em to x and y.
	str_x.erase(str_x.begin());
	str_x.erase(str_x.end()-1);
	str_y.erase(str_y.begin());
	str_y.erase(str_y.end() - 1);
	if (!Coordinate::check_correct_float_string(str_x) || !Coordinate::check_correct_float_string(str_y))
		throw string("wrong input in setting Coordinate");
	x = stof(str_x);
	y = stof(str_y);
	return Coordinate(x, y);
}

bool Model::is_castle_exist(Coordinate pos) 
{
	for (unsigned int i = 0; i < zones.size(); i++)
	{
		if (zones[i]->getLocation() == pos)
			return true;
	}
	return false;
}
bool Model::is_farm_exist(Coordinate pos) 
{
	for (unsigned int i = 0; i < zones.size(); i++)
	{
		if (zones[i]->getLocation() == pos)
			return true;
	}
	return false;
}

void Model::set_destination_for_knight(vector<string> tokens)
{
	if (tokens.size() != 3)
		throw string("not given enough arguments");
	string name_st = tokens[0];
	string dest = tokens[2];
	if (!is_castle_exist(dest))
		throw string("Error castle does not exist");
	get_knight_given_name(name_st)->set_destination(dest);
}


shared_ptr<Thug> Model::get_thug_given_name(string name)
{
	for (unsigned int i = 0; i < agents.size(); i++)
	{
		if (agents[i]->getName() == name)
		{
			if (agents[i]->getType() == "Thug")
				return dynamic_pointer_cast<Thug>(agents[i]);
		}
	}
	throw string(name + " thug doesnt exist");
}

shared_ptr<Knight> Model::get_knight_given_name(string name)
{
	for (unsigned int i = 0; i < agents.size(); i++)
	{
		if (agents[i]->getName() == name)
		{
			if (agents[i]->getType() == "Knight")
				return dynamic_pointer_cast<Knight>(agents[i]);
		}
	}
	throw string(name + " knight doesnt exist");
}


bool Model::check_if_peasant(string name)
{
	for (unsigned int i = 0; i < agents.size(); i++)
	{
		if (agents[i]->getName() == name)
		{
			if (agents[i]->getType() == "Peasant")
				return true;
		}
	}
	return false;
}


void Model::addAttacks(vector<string> tokens) {
	if (tokens.size() != 3)
		throw string("not given enough arguments");
	get_thug_given_name(tokens[0]);
	get_peasant_given_name(tokens[2]);
	for (unsigned int i = 0; i < attacksHeld.size(); i++)
	{
		if (attacksHeld[i][0] == tokens[0])
		{
			throw string("ERROR: attack was set for given thug");
		}
	}
	attacksHeld.push_back(tokens);
}
void Model::attack(vector<string> tokens)// Thug attacking peasant
{
	shared_ptr<Thug> thug = get_thug_given_name(tokens[0]);
	shared_ptr<Peasant> peasant = get_peasant_given_name(tokens[2]);
	float distnace_peasant_n_thug = Coordinate::DistanceCoordinate(thug->getLocation(), peasant->getLocation());
	if (distnace_peasant_n_thug < thug->get_atkRange())
	{
		if (safe_to_attack(peasant->getLocation()))
		{ //peasant hijacked most lose all cargo and set to stopped or dead, thug must increase lp by 1 and status stopped
			peasant->attack_successful();
			thug->attack_succsess();
		}
		else { // attack failed peasant continues thug loses 1 LP and status becomes stopped
			thug->attack_failed();
			peasant->attack_failed();
		}
	}
	else {
		thug->attack_failed(); 
	}
}


bool Model::safe_to_attack(Coordinate crdnt_peasant)
{
	for (shared_ptr<Agent> temp : agents)
	{
		if (temp->getType() == "Knight")
		{
			float distance = Coordinate::DistanceCoordinate(crdnt_peasant, temp->getLocation());
			if (distance < 0.25)
				return false;
		}
		if (temp->getType() == "Peasant") {
			if (temp->isUnpacking()) return false; //this means the peasant is at a castle/farm and cannot be attacked
		}
	}
	return true;
}

shared_ptr<Peasant> Model::get_peasant_given_name(string name)
{
	for (unsigned int i = 0; i < agents.size(); i++)
	{
		if (agents[i]->getName() == name)
		{
			if (agents[i]->getType() == "Peasant")
				return dynamic_pointer_cast<Peasant>(agents[i]);
		}
	}
	throw string(name + " peasant is not in database");
}

shared_ptr<Farm> Model::get_farm_given_name(string name)
{
	for (unsigned int i = 0; i < zones.size(); i++)
	{
		if (zones[i]->getName() == name)
		{
			if (zones[i]->getType() == "Farm")
				return dynamic_pointer_cast<Farm>(zones[i]);
		}
	}
	throw string(name + " farm is not in database");
}

shared_ptr<Castle> Model::get_castle_given_name(string name)
{
	for (unsigned int i = 0; i < zones.size(); i++)
	{
		if (zones[i]->getName() == name)
		{
			if (zones[i]->getType() == "Castle")
				return dynamic_pointer_cast<Castle>(zones[i]);
		}
	}
	throw string(name + " Castle is not in database");
}
void Model::updateView() {

	for (int i = 0; i < zones.size(); i++) {
		View::get_Instance().updates(zones[i]->getLocation().GetX(), zones[i]->getLocation().GetY(), zones[i]->getName().substr(0, 2));
	}
	for (unsigned int i = 0; i < agents.size(); i++)
		View::get_Instance().updates(agents[i]->getLocation().GetX(), agents[i]->getLocation().GetY(), agents[i]->getName().substr(0,2));
}

void Model::start_peasant_work(vector<string> tokens)
{
	shared_ptr<Peasant> peasant = get_peasant_given_name(tokens[0]);
	shared_ptr<Castle> castle = get_castle_given_name(tokens[3]);
	shared_ptr<Farm> farm = get_farm_given_name(tokens[2]);
	peasant->setRoute(farm,castle); 
	
}

void Model::peasant_status(string tokens)
{
	shared_ptr<Peasant> peasant = get_peasant_given_name(tokens);
	cout << *peasant;
}


