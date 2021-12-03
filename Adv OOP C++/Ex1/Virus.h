#pragma once

#include <string>
#include <vector>


using namespace std;
class Virus
{
public:
	Virus() { rank = 0; refVal = NULL; };
	Virus(const Virus & rhs);
	explicit  Virus(string n);
	virtual ~Virus();
	Virus& operator=(const Virus &rhs);
	virtual void switchBase(char, int) {};
	virtual void mutate() {}
	virtual string getStrand() const;
	virtual char getType()const;
	const char& operator[](int i)const;
	char& operator[](int i);
	int updateStanding(const string apexVirus);
	int getRefCnt()const;
	int getRank()const;
	void decRef();
	
protected:
	struct referenceValue {
		int refCount;
		referenceValue();
		~referenceValue();
	};
	int rank;
	string strand;
	referenceValue* refVal;
};
