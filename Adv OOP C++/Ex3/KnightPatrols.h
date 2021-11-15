#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "Castle.h"
#include "Farm.h"
using namespace std;
class KnightPatrols {
public:
	KnightPatrols(shared_ptr<Zone> wh) { zonePatrol = (wh); this->marked = false; };
	string getName()const { return zonePatrol->getName(); }
	shared_ptr<Zone> zonePatrol;
	bool marked;
};