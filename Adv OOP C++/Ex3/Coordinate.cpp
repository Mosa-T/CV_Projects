#include "Coordinate.h"

Coordinate::Coordinate()
{
	x = 0;
	y = 0;
}


/*
Coordinate::Coordinate(const Coordinate &&rhs)
{
	x = rhs.x;
	y = rhs.y;
}
Coordinate& Coordinate::operator=(const Coordinate &&rhs)
{
	if (&rhs == this)
		return *this;
	else {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
}
*/
Coordinate::Coordinate(string data_x,string data_y)
{
	string temp(" ");
	if (data_x.at(0) != temp[0])
		throw string("wrong input in setting Coordinate");
	temp = "(";
	if (data_x[1] != temp[0])
		throw string("wrong input in setting Coordinate");
	int last_index = data_y.size() - 1;
	temp = ")";
	if (data_y[last_index] != temp[0])
		throw string("wrong input in setting Coordinate");
	//delete first too charters and last then do split then stof em to x and y.
	data_x.erase(data_x.begin());
	data_x.erase(data_x.begin());
	data_y.erase(data_y.begin());
	data_y.erase(data_y.end()-1);
	if(!check_correct_float_string(data_x) || !check_correct_float_string(data_y))
		throw string("wrong input in setting Coordinate");
	x = stof(data_x);
	y = stof(data_y);
	
}


bool Coordinate::check_correct_float_string(string str)
{
	bool test = true;
	bool dot_appered = false;
	string dot = ".";
	int size_str = str.size();
	for (int i = 0; i < size_str; i++)
	{
		if (str[i] == dot[0])
		{
			if (dot_appered)
				test = false;
			dot_appered = true;
		}
		else
		{
			if (!isdigit(str[i]))
				test = false;
		}
	}
	return test;
}


Coordinate::Coordinate(float x, float y)
{
	this->x = x;
	this->y = y;
}

Coordinate::Coordinate(const Coordinate &rhs)
{
	x = rhs.x;
	y = rhs.y;
}
Coordinate::~Coordinate()
{

}
Coordinate Coordinate::operator+(const Coordinate &rhs)const
{

	return  Coordinate(this->x + rhs.x, this->y + rhs.y);
}
Coordinate Coordinate::operator-(const Coordinate &rhs)const
{
	return  Coordinate(this->x - rhs.x, this->y - rhs.y);
}
Coordinate& Coordinate::operator=(const Coordinate &rhs)
{
	if (&rhs == this)
		return *this;
	else {
		x = rhs.x;
		y = rhs.y;
		return *this;
	}
}
float Coordinate::GetX()const
{
	return x;
}
float Coordinate::GetY()const
{
	return y;
}
string Coordinate::to_string()const
{
	string s = "(";
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << x;
	 s += stream.str();
	 s += ", ";
	 stream.str(std::string());
	stream << std::fixed << std::setprecision(2) << y;
	s += stream.str();
	s += ")";
	return s;
}
void Coordinate::SetX(const float temp)
{
	x = temp;
}
void Coordinate::SetY(const float temp)
{
	y = temp;
}

void Coordinate::Print()const {
	if (x >= 10)
	{
		cout << x;
	}
	else {
		cout << x;
	}
	cout << " ";
	if (y >= 10){
		cout  << y;
	}
	else {
		cout  << y;
	}
}
Coordinate  Coordinate::operator*(const float i)const
{
	return Coordinate(x*i, y*i);
}

Coordinate operator*(const float i, const Coordinate& v)
{
	return v * i;
}


float  Coordinate::DistanceCoordinate(const Coordinate v1, const Coordinate v2)
{
	float temp = sqrt((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
	return temp;
}

bool operator==(const Coordinate &rhs, const Coordinate &lhs)
{
	return (fabs(roundf(rhs.x) - roundf(lhs.x)) <= 0.7 && fabs(roundf(rhs.y) - roundf(lhs.y)) <= 0.7); //round up numbers abit and add an 0.5/1.5 of error space
}





float Coordinate::slopeFormula(Coordinate a, Coordinate b) {
	return (b.GetY() - a.GetY()) / (b.GetX() - a.GetX()); 
}


float Coordinate::cal_Degree(float i) {
	return atan(i) * 180 /(atan(1.0) * 4);
}


float Coordinate::getDegree(Coordinate a, Coordinate b) {
	if ((b.GetY() - a.GetY()) == 0) return 0;
	if ((b.GetX() - a.GetX()) == 0) return 90;
	return cal_Degree(slopeFormula(a, b));
}
