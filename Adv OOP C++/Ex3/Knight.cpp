#include "Knight.h"



Knight::Knight(vector<string> parmaters) :Agent(parmaters[0])
{
	going_home = false;
	status = Moving_to;
	patrolIndex = 0;
	patrolOutOf = -1;
	degree = -1;
	moving_by_coordinate = false;
	moving_by_degree = false;
	if (parmaters.size() == 3)// create at castle
	{
		castle_name = parmaters[2];
		speed = 1;
	}
	else if (parmaters.size() == 4)// create at coordinate
	{
		throw string("Knight cannot be created by coodrinate");
	}
	else
		throw string("Invalid arguments to Knight con'");
}



void Knight::set_zone_at(vector<shared_ptr<Zone>> wh)
{
	vector<shared_ptr<KnightPatrols>> listZones;
	castle_at = wh[0];
	location = castle_at->getLocation();
	for (int i = 0; i < wh.size(); i++) {
		listZones.push_back(shared_ptr<KnightPatrols>(new KnightPatrols(wh[i])));
	}
	set_KnightCastleOrFarm_at(listZones);
}

void Knight::set_destination(string name)
{
	int index_zone_dest = get_index_castle(name);
	if (knightPatrols[index_zone_dest]->marked == true)
		throw string("this knight already went to " + name);
	else {
		patrolOutOf = patrolIndex;
		patrolIndex = index_zone_dest;
		status = Moving_to;
		moving_by_degree = false;
		moving_by_coordinate = false;
		move_to = knightPatrols[patrolIndex]->zonePatrol->getLocation();
		//moving_by_dest = true;
	}
}

int Knight::get_index_castle(string name)
{
	for (unsigned int i = 0; i < knightPatrols.size(); i++)
	{
		if (knightPatrols[i]->getName() == name)
			return i;
	}
	throw string("Error name Castle wasnt found in knight database");
}

void Knight::course(int dg, float spd)
{
	moving_by_degree = true;
	moving_by_coordinate = false;
	degree = dg;
	speed = 1;
	status = Moving_to;
}



Knight::~Knight(){}

string Knight::getStatus(){
	if (status == Stopped)
		return string("Knight " + name + " stopped at " + location.to_string());
	if (status == Dead)
		return string("Knight " + name + "is dead");
	if (status == Moving_to) {
		if(moving_by_degree)
			return string("Knight " + name + " at " + location.to_string() + ", Heading on course " + std::to_string(degree).substr(0, (to_string(degree).at(1) == '.' || to_string(degree).at(2) == '.') ? 2 : 3) + " deg, speed " + std::to_string((int)speed * 10) + " Km/h");
		else if (moving_by_coordinate)
			return string("Knight " + name + " at " + location.to_string() + ", Heading to position " + move_to.to_string() + ", speed " + std::to_string((int)speed * 10) + " Km/h");
		else 
			return string("Knight " + name  + " at " + location.to_string() + ", Heading to " + knightPatrols[patrolIndex]->zonePatrol->getName() + ", speed " + std::to_string((int)speed * 10) + " Km/h");
	}
	if (status == Unpacking)
		return string("Knight " + name + " Unpacking at " + castle_at->getName());
}
float Knight::getSpeed(){ return speed; }

void Knight::setNextInRoute()
{
	float temp_min ;
	int i_min=0;
	if (status == Stopped || moving_by_coordinate || moving_by_degree ) //R add this
		return;
	
	if (this->location == knightPatrols[patrolIndex]->zonePatrol->getLocation()) { //We've reached the Castle/Farm, time for the next one
		this ->location = knightPatrols[patrolIndex]->zonePatrol->getLocation(); //round up to the Castle/Farm location
		knightPatrols[patrolIndex]->marked = true;
		get_min_distance_unmarked();
	}
}

void Knight::get_min_distance_unmarked()
{
	float temp_min = FLT_MAX;
	int markCount = 0;
	int i_holder=0;
	for (int i=0; i< knightPatrols.size() ; i++)
	{
		if (knightPatrols[i]->marked == true) {
			markCount++;
			if (markCount == knightPatrols.size()) {
				if(location == knightPatrols[0]->zonePatrol->getLocation()){
					status = Stopped;
					return; //this means it finished the patrol, we stop the knight at the castle/farm he started the patrol.
				}
				patrolOutOf = patrolIndex;
				patrolIndex = 0; //mission acomplished we're going home boys.
				going_home = true;
				return; 
			}


			continue;
		}
		if (temp_min > Coordinate::DistanceCoordinate(knightPatrols[patrolIndex]->zonePatrol->getLocation(), knightPatrols[i]->zonePatrol->getLocation())) {
			temp_min = Coordinate::DistanceCoordinate(knightPatrols[patrolIndex]->zonePatrol->getLocation(), knightPatrols[i]->zonePatrol->getLocation());
			i_holder = i;
		}
	}
	patrolOutOf = patrolIndex;
	patrolIndex = i_holder;
}

void Knight::position(Coordinate pst,float speed) {
	move_to = pst;
	moving_by_coordinate = true;
	moving_by_degree = false;
	status = Moving_to;
	this->speed = 1;
}

void Knight::go() {
	if (status == Stopped) return;
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
		temp = (temp ) * pi / 180;
		float cos1 = (speed ) * cos(temp);
		float sin1 = (speed ) * sin(temp);

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
			location.SetX(location.GetX() -  cos1);
			location.SetY(location.GetY() -  sin1); //this is the range of 270 - 360 which is 270 to 360
		}
	}

	else if (moving_by_degree) {
		float temp = degree;
		float pi = 3.14159;
		temp = (temp + 90) * pi / 180;
		float cos1 = (speed ) * cos(temp);
		float sin1 = (speed ) * sin(temp);
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
	}
	else { 
		setNextInRoute();
		if (patrolOutOf == -1)
			set_destination(knightPatrols[0]->getName());
		float speedo = speed*10;
		float degreeio = Coordinate::getDegree(knightPatrols[patrolIndex]->zonePatrol->getLocation(),location);
		float pi = 3.14159;
		float temp = degreeio;
		temp = (temp)*pi / 180;
		float cos1 = (speed ) * cos(temp);
		float sin1 = (speed ) * sin(temp);
		if (knightPatrols[patrolIndex]->zonePatrol->getLocation().GetX() == location.GetX()) {
			cos1 = 0;
			//sin1 *= -1;
		}
		if (knightPatrols[patrolIndex]->zonePatrol->getLocation().GetY() == location.GetY()) {
			sin1 = 0;
			//cos1 *= -1;
		}

		 if (knightPatrols[patrolIndex]->zonePatrol->getLocation().GetX() >= location.GetX()
			&& knightPatrols[patrolIndex]->zonePatrol->getLocation().GetY() >= location.GetY())
		{ //up + right
				location.SetX(location.GetX() +  cos1);
				location.SetY(location.GetY() +  sin1);
		}
		 else if (knightPatrols[patrolIndex]->zonePatrol->getLocation().GetX() <= location.GetX()
			 && knightPatrols[patrolIndex]->zonePatrol->getLocation().GetY() <= location.GetY())
		 { //down + left
			 location.SetX(location.GetX() - cos1);
			 location.SetY(location.GetY() - sin1);

		 }
		 else if (knightPatrols[patrolIndex]->zonePatrol->getLocation().GetX() >= location.GetX()
				  && knightPatrols[patrolIndex]->zonePatrol->getLocation().GetY() <= location.GetY())
		 { //down + right
			location.SetX(location.GetX() +  cos1);
			location.SetY(location.GetY() +  sin1);
		}
		
		else { //up + left 
			location.SetX(location.GetX() -  cos1);
			location.SetY(location.GetY() -  sin1); //this is the range of 270 - 360 which is 270 to 360
		}
	}
}













