#include "Virus.h"





Virus::Virus(string n)
{
	rank = 0;
	strand = n;
	refVal = new referenceValue();
}



Virus::Virus(const Virus& rhs)
{
	refVal = rhs.refVal;
	++(refVal->refCount);
	strand = rhs.strand;
	
	rank = rhs.rank;
}




Virus& Virus::operator=(const Virus& rhs)
{
	if (refVal == rhs.refVal)
		return *this;
	--(refVal->refCount);
	refVal = rhs.refVal;
	strand = rhs.strand;
	rank = rhs.rank;
	return *this;
}

Virus::~Virus()
{
	if (--refVal->refCount == 0)
		delete refVal;
}


Virus::referenceValue::referenceValue() :refCount(1) {
}

Virus::referenceValue::~referenceValue()
{
}


char Virus::getType()const
{
	return 'v';
}


char& Virus::operator[](int i) {
	return strand.at(i);
}

const char& Virus::operator[](int i)const {
	return strand.at(i);
}


int Virus::getRefCnt()const
{
	if (refVal)
	{
		return refVal->refCount;
	}
	else return 0;
}

void Virus::decRef()
{
	if (refVal)
	{
		if (refVal->refCount > 0)
		{
			--refVal->refCount;
		}
	}
}



int Virus::updateStanding(const string apexVirus)
{
	int cnt = 0;
	for (unsigned int i = 0; i < apexVirus.size(); i++)
	{
		if (strand.at(i) == apexVirus.at(i))
			cnt++;
	}
		rank = cnt;
	return	rank;
}

int Virus::getRank()const
{
	if (refVal)
	{
		return rank;
	}
	return -1;
}



string Virus::getStrand() const {
	return strand;
}