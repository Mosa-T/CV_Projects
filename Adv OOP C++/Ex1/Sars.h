#pragma once

#include "Virus.h"

using namespace std;
class Sars : public Virus
{
private:
public:
	virtual char getType()const {return 's'; }
	virtual ~Sars();
	virtual Sars& operator=(const Sars& rhs);
	virtual void mutate();
	virtual void switchBase(char i, int j);
	Sars(const Sars& rhs);
	Sars(string n);
};
