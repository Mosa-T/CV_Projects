#include "Sars.h"


Sars::Sars(const Sars & rhs) : Virus(rhs)
{

}
Sars::Sars(string n): Virus(n)
{

}
Sars::~Sars()
{
}
Sars& Sars::operator=(const Sars &rhs)
{
	if (refVal == rhs.refVal)
		return *this;
	--(refVal->refCount);
	refVal = rhs.refVal;
	strand = rhs.strand;
	rank = rhs.rank;
	return *this;
}


void Sars::switchBase(char i, int j) {
	switch (i) {
	case 'T': strand.at(j) = 'A'; break;
	case 'A': strand.at(j) = 'T'; break;
	}
}

void Sars::mutate()
{
	int temp;
	for (unsigned int i = 0; i < strand.size(); i++)
	{
		temp = (rand() % 100);
		if (temp <= 36) 
		{
			switchBase((*this).getStrand().at(i), i);
		}
	}
}

