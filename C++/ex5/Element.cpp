#include "Element.h"

Element::Element()
{

}
Element::~Element()
{

}
Element::Element(int n, int m, vector<float> x)
{
	N = n;
	M = m;
	X = x;
	F = vector<float>(m, 0);
}
Element::Element(const Element &rhs)
{
	X = rhs.X;
	F = rhs.F;
	rank = rhs.rank;
	M = rhs.M;
	N = rhs.N;
}
Element& Element::operator = (const Element &rhs)
{
	if (this == &rhs)
		return *this;
	X = rhs.X;
	F = rhs.F;
	rank = rhs.rank;
	M = rhs.M;
	N = rhs.N;
	return *this;
}
vector<float> Element::getX()
{
	return X;
}
vector<float> Element::getF()
{
	return F;
}
void Element::SetX(const vector<float> temp)
{
	X = temp;
}
void Element::SetF(const vector<float> temp)
{
	F = temp;
}
int Element::GetRank()
{
	return rank;
}
void Element::SetRank(const int temp)
{
	rank = temp;
}
int Element::GetN()
{
	return N;
}
int Element::GetM()
{
	return M;
}
void Element::SetN(const int temp)
{
	N = temp;
}
void Element::SetM(const int temp)
{
	M = temp;
}


void Element::InitF()
{
	if (F.size() == 0)
	{
		F = vector<float>(M);
	}
	
	for (int i = 0; i < M; i++)
	{
		F[i] = 0;// to reset the vector targets
		for (int j = 0; j < N; j++)
		{
			F[i] = F[i] + ((X[j] - (i + 1)) * (X[j] - (i + 1)));
		}
	}
}

//the lhs variable should be the one smaller one 
bool operator<=(const Element& lhs, const Element& rhs)
{
	bool flag = false;
	for (unsigned int i = 0; i < lhs.F.size(); i++)
	{
		if (lhs.F[i] > rhs.F[i]) return false;
		if (lhs.F[i] < rhs.F[i]) flag = true;
	}
	return flag;
}