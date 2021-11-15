#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include <sstream>
#define _USE_MATH_DEFINES
using namespace std;

class Coordinate {
private:
	float x, y;// 1 is 10 km
public:
	Coordinate();
	Coordinate(float x, float y);
	Coordinate(const Coordinate &rhs);
	~Coordinate();
	Coordinate operator+(const Coordinate &rhs)const;
	Coordinate operator-(const Coordinate &rhs)const;
	Coordinate operator*(const float i)const;
	Coordinate& operator=(const Coordinate &rhs);
	friend bool operator==(const Coordinate &lhs, const Coordinate &rhs);
	float GetX()const;
	float GetY()const;
	void SetX(const float temp);
	void SetY(const float temp);
	void Print()const;
	bool static check_correct_float_string(string str);
	float static DistanceCoordinate(const Coordinate v1, const Coordinate v2);
	float static slopeFormula(Coordinate a, Coordinate b);
	float static cal_Degree(float i);
	float static getDegree(Coordinate a, Coordinate b);
	Coordinate(string data_x,string data_y);
	string to_string()const;
};

Coordinate operator*(const float i, const Coordinate& v);