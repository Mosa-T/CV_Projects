#include "Player.h"

//speed

void Player::IncDecSpeed(Player *p, CGPoints globalBest) {
	srand((int)time(NULL));
	double random1, random2;
	//random1 = (round(((double)rand())*100 / RAND_MAX))/100;
	//random2 = (round(((double)rand())*100 / RAND_MAX)) / 100;
	random1 = ((((double)rand()) / RAND_MAX));
	random2 = ((((double)rand()) / RAND_MAX));
	speed[0] = 0.25*speed[0] + (random1 * ((*p).getBestPos().GetX() - (*p).getPos().GetX())) + (random2 * (globalBest.GetX() - (*p).getPos().GetX()));
	speed[1] = 0.25*speed[1] + (random1 * ((*p).getBestPos().GetY() - (*p).getPos().GetY())) + (random2 * (globalBest.GetY() - (*p).getPos().GetY()));
	//speed[0] = round(speed[0] * 100) / 100;
	//speed[1] = round(speed[1] * 100) / 100;
	//speed = 0.25*speed + (random1 * ((*p).getBestPos().getVec() - (*p).getPos().getVec())) + (random2 * (globalBest. - (*p).getPos()));
}

void Player::setSpeed(double x, double y) {
	this->speed.push_back(x);
	this->speed.push_back(y);
}

double Player::getSpeedX() { return speed[0]; }

double Player::getSpeedY() { return speed[1]; }


double Player::getXSpeed() {
	return getSpeedX();
}

double Player::getYSpeed() { 
	return getSpeedY(); 
}
void Player::setSpeed(const vector<double> &s) { 
	this->speed = s;
}
vector<double> Player::getSpeedVec() { 
	return speed;
}
//distance
double Player::getdistancePlayer() { 
	return distance.GetDistance();
}
void Player::setDistance(const CGPoints d) {
	this->distance.setDist(this->pos, d);
}
double Player::getPersonalBest() { 
	return this->distance.getPersonalBestDis();
}

//pos
CGPoints Player::getPos() { 
	return pos;
}
void Player::setPosX(double a) {
	 pos.SetX(a);
}
void Player::setPosY(double a) {
	pos.SetY(a);
}
CGPoints Player::getBestPos() { 
	return distance.getBestPos(); 
}
void Player::movePosX() { 
	//pos.SetX(round((100 * (pos.GetX() + speed.getSpeedX()))) / 100);
	pos.SetX((((pos.GetX() + getSpeedX()))));
}
void Player::movePosY() {
	//pos.SetY(round((100*(pos.GetY() + speed.getSpeedY())))/100); 
	pos.SetY((( (pos.GetY() + getSpeedY()))));
}
void Player::movePos() { 
	movePosX(); movePosY();
}
void Player::speedChange(CGPoints globalBest) { 
	IncDecSpeed(this, globalBest);
}
//update values of a single player
void Player::update(CGPoints *globalBest, CGPoints targetPoint) {
	movePos();
	setDistance(targetPoint);
	speedChange(*globalBest);
	//setDistance(targetPoint);
}

//costructors and operators
Player::Player() {}

Player::Player(int i, int j, CGPoints targetPoint, vector<double> v,char type,int id) { 
	setSpeed(v.at(0), v.at(1));
	this->targetPoint = targetPoint;
	pos.SetX(i);
	pos.SetY(j);
	distance.setDist(pos, targetPoint);
	this->type = type;
	this->id = id;
}

Player::Player(CGPoints posInput, CGPoints targetPoint, vector<double> v,char type,int id) { 
	setSpeed(v.at(0),v.at(1));
	this->targetPoint = targetPoint;
	pos = posInput;
	distance.setDist(pos, targetPoint);
	this->id = id;
	this->type = type;
}

Player::Player(const Player &a) { 
	this->distance = a.distance;
	this->pos = a.pos;
	this->speed = a.speed;
	this->targetPoint = a.targetPoint;
	this->id = a.id;
	this->type = a.type;
}


Player &Player::operator=(const Player &a) {
	this->distance = a.distance;
	this->pos = a.pos;
	this->speed = a.speed;
	this->targetPoint = a.targetPoint;
	this->type = a.type;
	this->id = a.id;
	return *this;
}


bool Player::operator==(const Player& a) {
	//return (this->pos == a.pos) ? true : false; 
	return (this->id == a.id);
}

bool Player::operator<(const Player &a) {
	return (this->id < a.id);
}

/* revert to this
bool Player::operator<(const Player &a)  {
	return (this->pos < a.pos);
}
*/

Player::~Player() {

}
