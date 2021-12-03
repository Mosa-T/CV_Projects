#ifndef ELEMENT_H
#define ELEMENT_H
#include <iostream>
#include <vector>
using namespace std;
/// need to make something like in element
//,in element we iterate through two vectors with an overridden operator <= comparing all indexes
//, one vector needs to be smaller in all it's indexes to return true/false. anyway check sorting and youll understand.




class Element{
private:
	vector<float> X; // vector of vairablesweses
	vector<float> F; // vector of target
	int rank;
	int N; // size of X
	int M; // size of F
public:
	Element();
	virtual ~Element();
	Element(const Element &rhs);
	Element(int n, int m, vector<float> x);
	Element& operator=(const Element &rhs);
	vector<float> getX();
	vector<float> getF();
	void SetX(const vector<float> temp);
	void SetF(const vector<float> temp);
	void InitF();
	int GetRank();
	void SetRank(const int temp);
	int GetN();
	int GetM();
	void SetN(const int temp);
	void SetM(const int temp);
	friend bool operator<=(const Element& lhs, const Element& rhs);
};

#endif