#include "Peasant.h"

Peasant::Peasant(vector<string> parmaters) :Agent(parmaters),carrying_stock(0)
{
	status = Unpacking;

	speed = 0.5;

	if (parmaters.size() == 4)// create at coordinate
	{
		status = Unpacking;

		speed = 0.5;
		degree = 0;
		status = Stopped;
		location = create_coordinate(parmaters[2], parmaters[3]);
		starting_location = location;
		moving_by_coordinate = false;
		moving_by_degree = false;
		lifePoints = 10;
		//castle_at = nullptr;
	}
	else
		throw string("Invalid arguments to peasant con'");
}


Peasant::Peasant(string s) :Agent(s), carrying_stock(0) {
	if (s.size() > 12)
		throw string("Peasant name is too long");
	status = Unpacking;
	
	speed = 0.5;
}

void Peasant::attack_failed() {
	lifePoints -= 1;
	if (lifePoints <= 0) {
		status = Dead; //dead reset all locations etc
	}
}

void Peasant::attack_successful()
{
	status = Stopped;
	carrying_stock = 0;
	lifePoints -= 1;
	if (lifePoints <= 0) {
		status = Dead; //dead
	}
	//nullptr to the location peasant was going to
}

void Peasant::course(int dg, float spd)
{
		moving_by_degree = true;
		moving_by_coordinate = false;
		degree = dg;
		speed = 0.5;
		status = Moving_to;
}

void Peasant::position(Coordinate pst, float speed) {
	//this->speed = 1;
	move_to = pst;
	moving_by_coordinate = true;
	moving_by_degree = false;
	status = Moving_to;
	this->speed = 0.5;
}

Peasant::~Peasant(){}

string Peasant::getStatus()
{
	if (status == Stopped)
		return string("Peasant " + name + " stopped at " + location.to_string());
	if(status == Dead)
		return string("Peasant " + name + " is dead");
	if (status == Moving_to) {
		if (moving_by_degree)
			return string("Peasant " + name + " at " + location.to_string() + ", Heading on course " + std::to_string(degree).substr(0, (to_string(degree).at(1) == '.' || to_string(degree).at(2) == '.') ? 2 : 3) + " deg, speed " + std::to_string((int)(speed*10.0)) + " Km/h");
		else if (moving_by_coordinate)
			return string("Peasant " + name + " at " + location.to_string() + ", Heading to position " + move_to.to_string() + ", speed " + std::to_string((int)(speed * 10.0)) + " Km/h");
		else 
		if ((zoneList[0] == nullptr))
			return string("Peasant " + name + "  at " + location.to_string() + " heading to " + (zoneList[1]->getCastle()->getName()) + ", speed " + std::to_string((int)(speed * 10.0)) + " Km/h");
		else
			return string("Peasant " + name + "  at " + location.to_string() + " heading to " + (zoneList[0]->getFarm()->getName()) + ", speed " + std::to_string((int)(speed * 10.0)) + " Km/h");
	}
	if (status == Unpacking)
		return string("Peasant " + name + " at " + zoneList[1]->getCastle()->getName());
}

ostream& operator<<(ostream& os, const Peasant& pt) {
	 os << string("Peasant " + pt.name + " is currently at " + pt.location.to_string() + " with status " + ((pt.status == Agent::Stopped)? "Stopped ": (pt.status == Agent::Dead) ? "Dead ": "Moving to ") + " carrying " + std::to_string(pt.carrying_stock) + " stock " + "with " + std::to_string(pt.lifePoints) + " life points") << endl;
	 return os;
}

void Peasant::setRoute(shared_ptr<Farm> farm,shared_ptr<Castle> castle)
{
	if (currently_working) { //either deny and keep working on current move, or accepet and remove current work, or push back the work given,we choose push back.
		zoneList.push_back(make_shared<CastleFarmRoute>(CastleFarmRoute(nullptr, farm)));
		zoneList.push_back(make_shared<CastleFarmRoute>(CastleFarmRoute(castle, nullptr)));
		return;
	}
	zoneList.push_back(make_shared<CastleFarmRoute>(CastleFarmRoute(nullptr, farm)));
	zoneList.push_back(make_shared<CastleFarmRoute>(CastleFarmRoute(castle, nullptr)));
	zoneList[0]->getFarm() = farm;
	zoneList[1]->getCastle() = castle;
	currently_working = true;
	status = Moving_to;
}


void Peasant::restore_default()
{
	location = starting_location;
	carrying_stock = 0;
	lifePoints = 10;
}


float Peasant::getSpeed() {
	return speed;
}

void Peasant::go() {
	if (status == Dead || status == Stopped ) return;
	if (moving_by_coordinate) {
		if (location == move_to) {
			//either stop or start going back to castle
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
		temp = (temp)*pi / 180;
		float cos1 = (speed)*cos(temp);
		float sin1 = (speed)*sin(temp);

		if (move_to.GetX() == location.GetX()) {
			cos1 = 0;
			sin1 *= -1;
		}
		if (move_to.GetY() == location.GetY()) {
			sin1 = 0;
			//cos1 *= -1;
		}
		//20,10
		if (move_to.GetX() >= location.GetX()
			&& move_to.GetY() >= location.GetY())
		{ //up + right -----------------------------
			location.SetX(location.GetX() + cos1);
			location.SetY(location.GetY() + sin1);
		}
		else if (move_to.GetX() >= location.GetX()
			&& move_to.GetY() <= location.GetY())
		{ //down + right
			location.SetX(location.GetX() + cos1);
			location.SetY(location.GetY() + sin1);
		}
		else if (move_to.GetX() <= location.GetX()
			&& move_to.GetY() <= location.GetY())
		{ //down + left
			location.SetX(location.GetX() - cos1);
			location.SetY(location.GetY() - sin1);

		}
		else { //up + left
			location.SetX(location.GetX() - cos1);
			location.SetY(location.GetY() - sin1); //this is the range of 270 - 360 which is 270 to 360
		}
		return;
	} else if (moving_by_degree) {
		float temp = degree;
		float pi = 3.14159;
		temp = (temp + 90) * pi / 180;
		float cos1 = (speed)*cos(temp);
		float sin1 = (speed)*sin(temp);
		if (degree == 90 || degree == 180 || degree == 270 || degree == 0) {
			if (degree == 90) { //right
				location.SetX(location.GetX() - cos1);
			}
			if (degree == 180) { //down
				location.SetY(location.GetY() + sin1);
			}
			if (degree == 270) {//left
				location.SetX(location.GetX() - cos1);
			}
			if (degree == 0) {//up
				location.SetY(location.GetY() + sin1);
			}
		}
		else {
			if (degree > 0 && degree < 90) { //up + right
				location.SetX(location.GetX() + cos1 * -1);
				location.SetY(location.GetY() + sin1);
			}
			else if (degree > 90 && degree < 180) { //down + right
				location.SetX(location.GetX() - cos1);
				location.SetY(location.GetY() + sin1);
			}
			else if (degree > 180 && degree < 270) { //down + left
				location.SetX(location.GetX() - cos1);
				location.SetY(location.GetY() - fabs(speed * sin1));

			}
			else { //up + left
				location.SetX(location.GetX() + speed * cos1 * -1);
				location.SetY(location.GetY() + speed * sin1); //this is the range of 270 - 360 which is 270 to 360
			}
		}
		return;
	}
	setNextInRoute(); 
	if (status == Moving_to && zoneList[0] != nullptr) {
		float speedo = getSpeed() * 10;
		float degreeio = Coordinate::getDegree(zoneList[0]->getFarm()->getLocation(), location);
		float pi = 3.14159;
		float temp = degreeio;
		temp = (temp)*pi / 180;
		float cos1 = (speed ) * cos(temp);
		float sin1 = (speed ) * sin(temp);
		if (zoneList[0]->getFarm()->getLocation().GetX() == location.GetX()) {
			cos1 = 0;
			//sin1 *= -1;
		}
		if (zoneList[0]->getFarm()->getLocation().GetY() == location.GetY()) {
			sin1 = 0;
			//cos1 *= -1;
		}

		if (zoneList[0]->getFarm()->getLocation().GetX() >= location.GetX()
			&& zoneList[0]->getFarm()->getLocation().GetY() >= location.GetY())
		{ //up + right
			location.SetX(location.GetX() + cos1);
			location.SetY(location.GetY() + sin1);
		}
		else if (zoneList[0]->getFarm()->getLocation().GetX() <= location.GetX()
			&& zoneList[0]->getFarm()->getLocation().GetY() <= location.GetY())
		{ //down + left
			location.SetX(location.GetX() - cos1);
			location.SetY(location.GetY() - sin1);

		}
		else if (zoneList[0]->getFarm()->getLocation().GetX() >= location.GetX()
			&& zoneList[0]->getFarm()->getLocation().GetY() <= location.GetY())
		{ //down + right
			location.SetX(location.GetX() + cos1);
			location.SetY(location.GetY() + sin1);
		}

		else { //up + left 
			location.SetX(location.GetX() - cos1);
			location.SetY(location.GetY() - sin1); //this is the range of 270 - 360 which is 270 to 360
		}

	}
	else if (status == Moving_to && zoneList[0] == nullptr && zoneList[1] != nullptr) {
		//float speedo = getSpeed();
		float defreeFix = 0;
		float degreeio = Coordinate::getDegree(zoneList[1]->getCastle()->getLocation(), location);




		float speedo = getSpeed() * 10;
		//float degreeio = Coordinate::getDegree(zoneList[0]->getFarm()->getLocation(), location);
		float pi = 3.14159;
		float temp = degreeio;
		temp = (temp)*pi / 180;
		float cos1 = (speed ) * cos(temp);
		float sin1 = (speed ) * sin(temp);
		if (zoneList[1]->getCastle()->getLocation().GetX() == location.GetX()) {
			cos1 = 0;
			//sin1 *= -1;
		}
		if (zoneList[1]->getCastle()->getLocation().GetY() == location.GetY()) {
			sin1 = 0;
			//cos1 *= -1;
		}

		if (zoneList[1]->getCastle()->getLocation().GetX() >= location.GetX()
			&& zoneList[1]->getCastle()->getLocation().GetY() >= location.GetY())
		{ //up + right
			location.SetX(location.GetX() + cos1);
			location.SetY(location.GetY() + sin1);
		}
		else if (zoneList[1]->getCastle()->getLocation().GetX() <= location.GetX()
			&& zoneList[1]->getCastle()->getLocation().GetY() <= location.GetY())
		{ //down + left
			location.SetX(location.GetX() - cos1);
			location.SetY(location.GetY() - sin1);

		}
		else if (zoneList[1]->getCastle()->getLocation().GetX() >= location.GetX()
			&& zoneList[1]->getCastle()->getLocation().GetY() <= location.GetY())
		{ //down + right
			location.SetX(location.GetX() + cos1);
			location.SetY(location.GetY() + sin1);
		}

		else { //up + left 
			location.SetX(location.GetX() - cos1);
			location.SetY(location.GetY() - sin1); //this is the range of 270 - 360 which is 270 to 360
		}


	}
}

void Peasant::setNextInRoute()
{

	if (zoneList[0] != nullptr) {
		if (this->location == zoneList[0]->getFarm()->getLocation() && currently_working == true && status == Moving_to) { //we stopping at a farm
			//status = Stopped;
			if (zoneList[0]->getFarm()->get_stock() < 5) {
				carrying_stock = zoneList[0]->getFarm()->get_stock();
				zoneList[0]->getFarm()->set_stock(0);
			}
			else {
				carrying_stock = 5;
				zoneList[0]->getFarm()->set_stock(zoneList[0]->getFarm()->get_stock() - carrying_stock);
			}
			zoneList[0] = nullptr;
		}
	}
	else if(zoneList[1] != nullptr) {
		if (this->location == zoneList[1]->getCastle()->getLocation() && currently_working == true) { //we reached the castle!
			zoneList[1]->getCastle()->set_stock(zoneList[1]->getCastle()->get_stock() + carrying_stock); 
			carrying_stock = 0;
			lifePoints += 1;
			if (zoneList.size() > 2) {
				zoneList[1] = zoneList.back();
				zoneList.pop_back();
				zoneList[0] = zoneList.back();
				zoneList.pop_back();
				return;
			}
			status = Stopped;
			currently_working = false;
			zoneList[1] = nullptr;
		}
	}

}




bool Peasant::isUnpacking()
{
	if (status == Unpacking) return true;
	return false;
}







