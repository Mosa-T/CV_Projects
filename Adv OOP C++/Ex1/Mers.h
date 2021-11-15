#pragma once

#include "Virus.h"

using namespace std;
class Mers : public Virus
{
private:
public:
	virtual char getType()const { return 'm'; }
	virtual void mutate();
	virtual ~Mers();
	virtual Mers& operator=(const Mers& rhs);
	virtual void switchBase(char i, int j);
	Mers(const Mers& rhs);
	Mers(string n);
};
