#include "Thug.h"



Thug::Thug(vector<string> parmaters):Agent(parmaters[0])
{
	atk_range = 0.1;
	degree = 0;
	status = Stopped;
	lifePoints = 5;
	if (parmaters.size() == 3)// create at castle
	{
		throw string("error cant create thug at castle");
	}
	else if (parmaters.size() == 4)// create at coordinate
	{
		location = create_coordinate(parmaters[2], parmaters[3]);
		starting_location = location;
		speed = 0;
		castle_at = nullptr;
		moving_by_coordinate = true;
		moving_by_degree = false;
	}
	else
		throw string("Invalid arguments to thug con'");
}
Thug::~Thug(){}

void Thug::course(int dg, float spd)
{
	if (spd > 30 || spd < 0)
		throw string("given speed for thug invalid!");
	speed = spd / 10;
	degree = dg;
	moving_by_degree = true;
	moving_by_coordinate = false;
	status = Moving_to;
}


void Thug::position(Coordinate pst, float spd)
{
	if (spd > 30 || spd < 0)
		throw string("given speed for thug invalid!");
	speed = spd / 10;
	moving_by_coordinate = true;
	moving_by_degree = false;
	move_to = pst;
	status = Moving_to;
}
string Thug::getStatus()
{
		if (status == Stopped)
			return string("Thug " + name + " Stopped at " + location.to_string());
		if (status == Dead)
			return string("Thug " + name + " is dead");
		if (status == Moving_to) {
			if (moving_by_degree)
				return string("Thug " + name + " at " + location.to_string() + ", Heading on course " + std::to_string(degree).substr(0, (to_string(degree).at(1) == '.' || to_string(degree).at(2) == '.') ? 2 : 3) +" deg, speed " + std::to_string((int)(speed * 10)) + " Km/h)");
			else if(moving_by_coordinate)
				return string("Thug " + name + " at " + location.to_string() + ", Heading to position " + move_to.to_string() + ", speed " + std::to_string((int)speed*10) + " Km/h");
		} 
		if (status == Unpacking)
			return string("Thug " + name + " Unpacking at " + castle_at->getName());
		throw string("Error: check getStatus\n");
}
float Thug::getSpeed(){ return this->speed; }

void Thug::go()
{
	
	if (status == Stopped) return;
	if (moving_by_coordinate) { 
		if (location == move_to) {
			location = move_to;
			status = Stopped;
		}
		if (location == move_to) {
			
			location = move_to;
			status == Stopped;
		}
		if (location == move_to) {
			location = move_to;
			status = Stopped;
		}
		float defreeFix = 0;
		float degreeio = Coordinate::getDegree(move_to, location);
		float temp = degreeio;
		degree = degreeio;

		float pi = 3.14159;
		temp = (temp + 90) * pi / 180;
		float cos1 = (speed ) * cos(temp);
		float sin1 = (speed ) * sin(temp);



		if (move_to.GetX() >= location.GetX()
			&& move_to.GetY() >= location.GetY())
		{ //up + right -----------------------------
			location.SetX(location.GetX() + cos1 * -1);
			location.SetY(location.GetY() + sin1);
		}
		else if (move_to.GetX() >= location.GetX()
			&& move_to.GetY() <= location.GetY())
		{ //down + right
			location.SetX(location.GetX() - cos1);
			location.SetY(location.GetY() - sin1);
		}
		else if (move_to.GetX() <= location.GetX()
			&& move_to.GetY() <= location.GetY())
		{ //down + left
			location.SetX(location.GetX() + cos1);
			location.SetY(location.GetY() - sin1);

		}
		else { //up + left
			location.SetX(location.GetX() + speed * cos1 * -1);
			location.SetY(location.GetY() + speed * sin1); //this is the range of 270 - 360 which is 270 to 360
		}
	}
	else if (moving_by_degree) {
		float temp = degree;
		float pi = 3.14159;
		temp = (temp + 90) * pi / 180;
		float cos1 = (speed) * cos(temp);
		float sin1 = (speed) * sin(temp);
		if (degree == 90 || degree == 180 || degree == 270 || degree == 0) {
			if (degree == 90) { //right
				location.SetX(location.GetX() -  cos1);
			}
			if (degree == 180) { //down
				location.SetY(location.GetY() + sin1);
			}
			if (degree == 270) {//left
				location.SetX(location.GetX() -  cos1);
			}
			if (degree == 0) {//up
				location.SetY(location.GetY() +  sin1);
			}
		}
		else {
			if (degree > 0 && degree < 90) { //up + right
				location.SetX(location.GetX() +  cos1*-1);
				location.SetY(location.GetY() +  sin1);
			}
			else if (degree > 90 && degree < 180) { //down + right
				location.SetX(location.GetX() -  cos1);
				location.SetY(location.GetY() +  sin1);
			}
			else if (degree > 180 && degree < 270) { //down + left
				location.SetX(location.GetX() -  cos1);
				location.SetY(location.GetY() - fabs(speed * sin1));

			}
			else { //up + left
				location.SetX(location.GetX() + speed * cos1*-1);
				location.SetY(location.GetY() + speed * sin1); //this is the range of 270 - 360 which is 270 to 360
			}
		}
	}
}


void Thug::attack_failed()
{
	status = Stopped;
	if (lifePoints > 0)
	{
		lifePoints = lifePoints - 1;
	}
	if (lifePoints <= 0) {
		status = Dead; //dead
	}
}
void Thug::attack_succsess()
{
	status = Stopped;
	if(lifePoints < 20)
		lifePoints += 1;
}

