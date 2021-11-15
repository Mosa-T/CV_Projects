#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Agent.h"
#include "Castle.h"
#include <list> 
#include <memory>
#include "CastleFarmRoute.h"
#include "Farm.h"


class Peasant : public Agent
{
private:
	vector<shared_ptr<CastleFarmRoute>> zoneList;
	int carrying_stock;
	bool currently_working = false;
public:
	friend ostream& operator<<(ostream& os, const Peasant& pt);
	Peasant(string);
	void attack_failed();
	Peasant(vector<string> parmaters);
	void attack_successful();
	virtual void course(int, float);
	virtual void set_zone_at(vector<shared_ptr<Zone>> wh) {  };
	virtual ~Peasant();
	virtual string getType(){ return string("Peasant"); }
	virtual string getStatus();
	virtual void stop() { this->status = Stopped; /*this->speed = 0*/; moving_by_coordinate = false; moving_by_degree = false;}
	virtual float getSpeed();
	void setRoute(shared_ptr<Farm> farm, shared_ptr<Castle> castle);
	void restore_default();
	virtual void position(Coordinate, float);
	virtual Coordinate getLocation() { return location; }
	virtual string getName() { return name; }
	vector<shared_ptr<CastleFarmRoute>> getZonePeasantList() { return this->zoneList; }
	virtual void go();
	void setNextInRoute();
	bool isUnpacking();
};