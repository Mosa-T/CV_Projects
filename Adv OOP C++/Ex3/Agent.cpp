#include "Agent.h"


Agent::Agent(vector<string> parmaters)
{
	name = parmaters[0];
	//degree
	//speed
	//starting_speed
	//status
	//location - starting location - status
}

Agent::Agent(string s) {
	if (s.size() > 12)
		throw string("name :" + s + "is too long");
	name = s;
	//degree
	//speed
	//starting_speed
	//status
}

Coordinate Agent::create_coordinate(string str_x, string str_y)
{
	float x, y;
	if (!Coordinate::check_correct_float_string(str_x) || !Coordinate::check_correct_float_string(str_y))
		throw string("wrong input in setting Coordinate");
	x = stof(str_x);
	y = stof(str_y);
	return Coordinate(x, y);
}