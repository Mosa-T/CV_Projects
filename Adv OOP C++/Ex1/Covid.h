#pragma once


#include "Virus.h"

using namespace std;
class Covid : public Virus
{
private:
public:
	virtual char getType()const { return 'c'; }
	virtual void mutate();
	virtual ~Covid();
	virtual Covid& operator=(const Covid& rhs);
	virtual void switchBase(char i, int j);
	Covid(const Covid & rhs);
	Covid(string n);
};