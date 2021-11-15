#include "Covid.h"

Covid::Covid(const Covid & rhs) : Virus(rhs)
{

}
Covid::Covid(string n) : Virus(n)
{

}
Covid::~Covid()
{
	
}
Covid& Covid::operator=(const Covid &rhs)
{
	if (refVal == rhs.refVal)
		return *this;
	(refVal->refCount)--;
	rank = rhs.rank;
	refVal = rhs.refVal;
	strand = rhs.strand;
	return *this;
}

void Covid::mutate()
{
	int temp;
	for (unsigned int i = 0; i < strand.size(); i++)
	{
		temp = (rand() % strand.size());

		if (temp < 2) 
		{	
			switchBase((*this).getStrand().at(i), i);
		}
	}
}

void Covid::switchBase(char i,int j) {
	switch (i) {
	case 'T': strand.at(j) = 'A'; break;
	case 'C': strand.at(j) = 'G'; break;
	case 'G': strand.at(j) = 'C'; break;
	}
}