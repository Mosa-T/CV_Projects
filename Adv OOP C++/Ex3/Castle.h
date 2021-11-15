#pragma once
#include "Zone.h"

using namespace std;

class Castle: public Zone{
private:
	//Coordinate location; 
public:
	Castle();
	Castle(string the_name, Coordinate loc, vector<string> stock);
	Castle(const Castle &rhs);
	Castle(const Castle &&rhs);
	Castle& operator=(const Castle &rhs);
	Castle& operator=(const Castle &&rhs);
	virtual string getStatus()const;
	virtual string getType() { return "Castle"; };
	virtual void restore_default() { Zone::stock = Zone::starting_stock; } 
	~Castle();
};