#pragma once
#include <iostream>
#include "Agent.h"
#include "Castle.h"
#include "KnightPatrols.h"
#include <float.h>

class Knight : public Agent
{
private:
	void get_min_distance_unmarked();
	int get_index_castle(string name);
	shared_ptr<Zone> castle_at;
	float degree;
	bool on_course;
	int patrolOutOf;
	string castle_name;
	int patrolIndex;
	bool going_home;
	vector<shared_ptr<KnightPatrols>> knightPatrols; //brute salesman, will mark castles/farms visted and will only travel to closest, by checking every neighbor..sadly.
public:
	virtual void stop() { this->status = Stopped; this->speed = 1; moving_by_coordinate = false; moving_by_degree = false; }
	virtual void course(int, float);
	virtual bool isUnpacking() { if (status == Unpacking) return true; else false; }
	virtual Coordinate getLocation() { return location; }
	Knight(string s) :Agent(s), degree(-1) { castle_at = nullptr; };
	Knight(vector<string> parmaters);
	void set_destination(string name);
	virtual void position(Coordinate, float);
	virtual void set_zone_at(vector<shared_ptr<Zone>> wh); 
	void set_KnightCastleOrFarm_at(vector<shared_ptr<KnightPatrols>> wh) { knightPatrols = wh; };
	virtual ~Knight();
	virtual string getType(){ return string("Knight"); } 
	virtual string getStatus();
	virtual float getSpeed();
	virtual string getName() { return name; }
	void setNextInRoute();
	virtual void go();

};