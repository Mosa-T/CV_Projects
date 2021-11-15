#include "Mers.h"

Mers::Mers(const Mers & rhs) : Virus(rhs)
{

}
Mers::Mers(string n) : Virus(n)
{

}
Mers::~Mers()
{
	
}
Mers& Mers::operator=(const Mers &rhs)
{
	if (refVal == rhs.refVal)
		return *this;
	--(refVal->refCount);
	refVal = rhs.refVal;
	strand = rhs.strand;
	rank = rhs.rank;
	return *this;
}


void Mers::mutate()
{
	int temp;
	for (unsigned int i = 0; i < strand.size(); i++)
	{
		temp = rand() % strand.size();
		
		if (temp == 1)
		{
			switchBase((*this).getStrand().at(i), i);
		}
	}
}


void Mers::switchBase(char i, int j) {
	switch (i) {
	case 'A': strand.at(j) = 'T'; break;
	case 'C': strand.at(j) = 'G'; break;
	case 'G': strand.at(j) = 'C'; break;
	}
}