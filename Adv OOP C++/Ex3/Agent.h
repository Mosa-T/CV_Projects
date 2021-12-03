#pragma once
#include <iostream>
#include <string>
#include "Coordinate.h"
#include <vector>
#include "Castle.h"
#include <memory>
using namespace std;
class Agent
{
public:
	enum STATUS
	{
		Stopped, Unpacking,Dead, Moving_to
	};
	Agent(vector<string> parmaters);
	Agent(string s);
	virtual void stop() { this->status = Stopped; /*this->speed = 0;*/ }
	virtual void set_zone_at(vector<shared_ptr<Zone>> wh) = 0;
	virtual void course(int, float) = 0;
	virtual string getName() = 0;
	virtual string getType() = 0;
	virtual string getStatus() = 0;
	virtual float getSpeed() = 0;
	virtual Coordinate getLocation() = 0;
	virtual void position(Coordinate,float) = 0;
	virtual void go() = 0;
	virtual bool isUnpacking() = 0;
	virtual ~Agent(){}
protected:
	Coordinate create_coordinate(string str_x, string str_y);
	string name;
	Coordinate location;
	Coordinate starting_location;
	Coordinate move_to;
	float speed;
	float starting_speed;
	float degree;
	STATUS status;
	bool moving_by_coordinate;
	bool moving_by_degree;
	int lifePoints;
};