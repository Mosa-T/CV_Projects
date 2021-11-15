#ifndef CGPOINTS_H
#define CGPOINTS_H
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
class CGPoints {
private:
	vector<double> posXY;
public:
	CGPoints();
	CGPoints(double x, double y);
	double GetX()const;
	double GetY()const;
	vector<double> getVec()const;
	void SetX(double num);
	void SetY(double num);
	void SetPoint(double i, double j);
	double distanceFrom(const CGPoints& other) const;
	void Print() const;
	CGPoints(const CGPoints &newPoint);
	CGPoints &operator=(const CGPoints &newPoint);
	bool operator==(const CGPoints &comparedTo);
	bool intCompare(const CGPoints &comparedTo);
	~CGPoints() {};
	bool operator<(const CGPoints &comparedTo);
	bool operator> (const CGPoints& rhs);
	bool operator<=(const CGPoints& rhs);
	bool operator>=(const CGPoints& rhs);
};

#endif