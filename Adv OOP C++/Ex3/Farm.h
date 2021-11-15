#pragma once
#include "Zone.h"
using namespace std;

class Farm: public Zone {
private:
	int productivity;
public:
	Farm();
	Farm(string the_name, Coordinate loc, vector<string> stock);
	Farm(const Farm& rhs);
	Farm(const Farm&& rhs);
	Farm& operator=(const Farm& rhs);
	Farm& operator=(const Farm&& rhs);
	void go();
	virtual string getType() { return "Farm"; };
	virtual string getStatus()const; 
	void restore_default() { stock = starting_stock;  }
	int getProduct() { return this->productivity; }

	~Farm();
};