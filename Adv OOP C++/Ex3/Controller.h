#pragma once
#include "Model.h"
#include "View.h"
using namespace std;
class Controller
{
private:
	friend class Destroyer;
	Controller() {}
	~Controller() {}
	static Controller* ptr2;
	void create_agent(vector<string> tokens);
	int get_choice(vector<string>);
	bool check_correct_tokens_for_course(vector<string> tokens);
public:
	void run();
	static Controller& get_Instance();
	static void ResetInstance()
	{
		delete ptr2;
		ptr2 = NULL;
	}
};
