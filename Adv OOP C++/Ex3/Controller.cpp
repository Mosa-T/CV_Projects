#include "Controller.h"

Controller* Controller::ptr2 = 0;

Controller& Controller::get_Instance() {
	if (!ptr2)
		ptr2 = new Controller();
	return *ptr2;
}




void Controller::run()
{
	string str;
	vector<string> tokens;
	
	int i  = 0;
	while (true)
	{
		std::getline(std::cin, str);
		cout << "TIME " << to_string(Model::get_Instance().getTime()) << ": Enter command: " << str << endl;
		if (str == "exit") {
			exit(0);
		}
		tokens = FileOpener::split(str, " ");
		i = get_choice(tokens); // gets choice
		switch (i) {
		case (1):
			return;
			break;
		case (2)://default
			Model::get_Instance().set_to_default();
			View::get_Instance().set_to_default();
			break;
		case (3)://status
			Model::get_Instance().print_status(); //this maybe should call view to print to the terminal whatever is being done here.
			break;
		case(4)://go - this should activate Model to update everything, we dont see changes unless we use status or show 
			Model::get_Instance().go();
			break;
		case(5)://show - this should get coordinates of all things, vehicles and warehouses and using the setting View was set on to, to display it in a file OR ON THE TERMINAL
			Model::get_Instance().updateView();
			View::get_Instance().show();
			break;
		case(6)://size
			try{
				if (tokens.size() != 2)
					throw string("ERROR: too many argumets ");
			View::get_Instance().size(tokens[1]);
			}
			catch (string e)
			{
				cout << e << endl;
			}
			break;
		case(7)://zoom
			try{
				if (tokens.size() != 2)
					throw string("ERROR: too many argumets ");
				View::get_Instance().zoom(tokens[1]);
			}
			catch (string e)
			{
				cout << e << endl;
			}
			break;
		case(8)://pan - lines 5 through 8 are for View
			try{
				if (tokens.size() != 3)
					throw string("ERROR: too many argumets ");
			tokens.erase(tokens.begin());
			View::get_Instance().pan(tokens);
			}
			catch (string e)
			{
				cout << e << endl;
			}
			break;
		case(9)://create - create some sort of vehicle
			try{
			create_agent(tokens); 
			}
			catch (string e)
			{
				cout << "error in creating agent : " << e << endl;
			}
			break;
		case(10)://course - set course for given agent - arguemnts are degrees, both for knight and thug
			try {
				check_correct_tokens_for_course(tokens);
				Model::get_Instance().set_on_course(tokens);
			}
			catch (string e)
			{
				cout << "Error setting on course : " << e << endl;
			}
			break;
		case(11)://postion - declare where to is the agent heading, must be of Coordinate type, if it's a thug then speed is required, if knight, then Coordinates only.
			try{
			Model::get_Instance().position(tokens);
			}
			catch (string e)
			{
				cout << "Error in setting position to a agent " << e << endl;
			}
			break;
		case(12)://destination - decalre which warehouse to go to, argument is a castle/name
			try {
				Model::get_Instance().set_destination_for_knight(tokens); 
			}
			catch (string e)
			{
				cout << "error setting destination : " << e << endl;
			}
			break;
		case(13)://attack - thug attacks a peasant, argument is a peasant's name.
			try {
				Model::get_Instance().addAttacks(tokens);
			}
			catch (string e)
			{
				cout << "error attacking :" << e << endl;
			}
			break;
		case(14)://stop - not sure if peasant can be stopped
			try{
			Model::get_Instance().stop_agent(tokens[1]);
			}
			catch (string e)
			{
				cout << e << endl;
			}
		case(15)://start_working - peasant gets a farm location and a castle
			try {
				Model::get_Instance().start_peasant_work(tokens);
			}
			catch (string e)
			{
				cout << e << endl;
			}
			break;
		case(16)://Peasant status
			try {
				Model::get_Instance().peasant_status(tokens[0]);
			}
			catch (string e)
			{
				cout << e << endl;
			}
			break;
		case(-1):
			cout << "wrong input " << endl;
			break;
		default:
			cout << "wrong input " << endl;
			break;
		}
	}
}

bool Controller::check_correct_tokens_for_course(vector<string> tokens)
{
	if (tokens.size() == 4) // its a thug
	{
		int deg = stoi(tokens[2]);
		float spd = stof(tokens[3]);
		if (deg < 0 || deg > 360)
			throw string("degrees must be between 0 - 360");
		if (spd > 30 || spd < 0)
			throw string("speed for thug must be between 0-30 K/Mh");
		return true;
	}
	else if (tokens.size() == 3)//its a knight/peasant
	{
		int deg = stoi(tokens[2]);
		if (deg < 0 || deg > 360)
			throw string("degrees must be between 0 - 360");
		return true;
	}
	else {
		throw string("too few arguments for course. example : -name- course -degree- -speed- (speed is only for thug)");
	}
	throw string("ERROR: unclear input at Controller:156");
}

void Controller::create_agent(vector<string> tokens)
{
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].find("(") != string::npos)
			 tokens[i].erase(tokens[i].find("("), 1);
		if (tokens[i].find(")") != string::npos)
			tokens[i].erase(tokens[i].find(")"), 1);
		if (tokens[i].find(",") != string::npos)
			tokens[i].replace(tokens[i].find(","),1, "");
	}
	
	if (tokens.size() != 4 && tokens.size() != 5)
		throw string("Invalid arguments in creating agent");
	if (Model::get_Instance().agent_exist(tokens[1]))
		throw string("name agent already exist in data base");
	tokens.erase(tokens.begin());// erase token[0] = "create"
	if (tokens.size() == 4)
	{
	
		if (tokens[1] == "Thug")
		{
			if (Model::get_Instance().is_castle_exist(Coordinate(atof(tokens[2].c_str()), atof(tokens[3].c_str()))))
				throw string("Error creating agent/Thug at Castle or Farm, Thugs not allowed");
			Model::get_Instance().create_agent(AgentFactory::THUG,tokens);
		}
		else if (tokens[1] == "Peasant") {
			Model::get_Instance().create_agent(AgentFactory::PEASANT, tokens);
		}
		else {
			throw string("Ivalid arguments in creating agent. example : create -name- -type-  -coordinate-/-Castle-");
		}
	}
	else if (tokens.size() == 3) {
		if (!Model::get_Instance().is_castle_exist(tokens[2])) 
			throw string("Error creating agent at Castle, Castle doesn't exist");
		
		if (tokens[1] == "Knight")
		{
			Model::get_Instance().create_agent(AgentFactory::KNIGHT, tokens);
		}
		else {
			throw string("Ivalid arguments in creating agent. example : create -name- -type-  -coordinate-/-Castle-");
		}
	}
	else
		throw string("Ivalid arguments in creating agent. example : create -name- -type-  -coordinate-/-Castle-");
}



int Controller::get_choice(vector<string> tokens)
{
	if (tokens.size() == 0)
		return -1;
	else if (tokens[0] == "default")
		return 2;
	else if (tokens[0] == "status")
		return 3;
	else if (tokens[0] == "go")
		return 4;
	else if (tokens[0] == "show")
		return 5;
	else if (tokens[0] == "size")
		return 6;
	else if (tokens[0] == "zoom")
		return 7;
	else if (tokens[0] == "pan")
		return 8;
	else if (tokens[0] == "create")
		return 9;
	else if (tokens.size() == 1)
		return -1;
	else if (tokens[1] == "course")
		return 10;
	else if (tokens[1] == "position")
		return 11;
	else if (tokens[1] == "destination")
		return 12;
	else if (tokens[1] == "attack")
		return 13;
	else if (tokens[1] == "stop")
		return 14;
	else if (tokens[1] == "start_working")
		return 15;
	else if (tokens[1] == "status")
		return 16;
	return -1;
}