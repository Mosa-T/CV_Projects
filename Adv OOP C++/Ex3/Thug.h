#pragma once
#include <iostream>
#include "Agent.h"
#include "Castle.h"
#include <memory>
class Thug : public Agent
{
private:
	shared_ptr<Castle> castle_at; //not used
	float atk_range;
public:
	Thug(string s) :Agent(s) { castle_at = nullptr;}
	Thug(vector<string> parmaters);
	float get_atkRange()const { return atk_range; }
	void attack_failed();
	void attack_succsess();
	virtual Coordinate getLocation() { return location; }
	virtual void set_zone_at(vector<shared_ptr<Zone>> wh) { /*castle_at = wh[0];*/ } //not needed
	virtual ~Thug();
	virtual string getType(){ return string("Thug"); }
	virtual string getStatus();
	virtual void position(Coordinate, float);
	virtual void course(int, float);
	virtual float getSpeed();
	virtual string getName() { return name; }
	virtual void stop() { this->status = Stopped; this->speed = 0; moving_by_coordinate = false; moving_by_degree = false; }
	virtual void go();
	virtual bool isUnpacking() { if (status == Unpacking) return true; return false; }
};