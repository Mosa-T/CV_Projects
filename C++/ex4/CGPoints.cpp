#include "CGPoints.h"

CGPoints::CGPoints() { 
	this->posXY.push_back(-1);
	this->posXY.push_back(-1);
}
CGPoints::CGPoints(double x, double y) {
	this->posXY.push_back(x);
	this->posXY.push_back(y);
}

double CGPoints::GetX()const { 
	return this->posXY.at(0);
}
double CGPoints::GetY()const {
	return this->posXY.at(1);
}
void CGPoints::SetX(double num) { 
	this->posXY.at(0) = num;
}
void CGPoints::SetY(double num) {
	this->posXY.at(1) = num;
}
void CGPoints::SetPoint(double i, double j) {
	this->posXY.clear();
	this->posXY.push_back(i);
	this->posXY.push_back(j);
}

vector<double> CGPoints::getVec()const
{
	return posXY;
}
double CGPoints::distanceFrom(const CGPoints& other) const {
	return ((sqrt((int)(other.GetX() - (int)this->GetX())*((int)other.GetX() - (int)this->GetX()) + ((int)other.GetY() - (int)this->GetY())*((int)other.GetY() - (int)this->GetY()))));
}
void CGPoints::Print() const {
	cout << "x = " << this->GetX() << "," << "y = " << this->GetY()<<endl;
}
CGPoints::CGPoints(const CGPoints &newPoint) {
	this->posXY.push_back(newPoint.GetX());
	this->posXY.push_back(newPoint.GetY());
}
CGPoints &CGPoints::operator=(const CGPoints &newPoint) { 
	this->posXY.clear();
	this->posXY.push_back(newPoint.GetX());
	this->posXY.push_back(newPoint.GetY());
	return *this;
}



bool CGPoints::operator==(const CGPoints &comparedTo) {
	return ((int)this->GetX() == (int)comparedTo.GetX() && (int)this->GetY() == (int)comparedTo.GetY()) ? true : false;
}



bool CGPoints::operator<(const CGPoints &comparedTo) {
	return (this->GetX() < comparedTo.GetX() && this->GetY() < comparedTo.GetY()) ? true : false;
}

bool CGPoints::operator> (const CGPoints& rhs) { return rhs.GetX() < this->GetX(); }
bool CGPoints::operator<=(const CGPoints& rhs) { return (!(this->GetX() < rhs.GetX()))*(!(this->GetY() < rhs.GetY())); }
bool CGPoints::operator>=(const CGPoints& rhs) { return (!(this->GetX() < rhs.GetX()))*(!(this->GetY() < rhs.GetY())); }


bool CGPoints::intCompare(const CGPoints & comparedTo)
{
	return ((int)this->GetX() == (int)comparedTo.GetX() && (int)this->GetY() == (int)comparedTo.GetY()) ? true : false;
}


