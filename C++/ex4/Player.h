#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include "CGPoints.h"
#include "CalDist.h"
#include <cstdlib>
#include <ctime>
class Player {
protected:
	int id;
	CGPoints pos;
	vector<double> speed;
	CalDist distance;
	CGPoints targetPoint;
	char type;
public:
	char getType() {
		return type;
	}
	//speed
	void setSpeed(double x, double y);
	double getSpeedX();
	double getSpeedY();
	virtual void IncDecSpeed(Player *p, CGPoints globalBest);
	double getXSpeed();
	double getYSpeed();
	void setSpeed(const vector<double> &s);
	vector<double> getSpeedVec();
	//distance
	double getdistancePlayer();
	virtual void setDistance(const CGPoints d);
	double getPersonalBest();
	//pos
	CGPoints getPos();
	void setPosX(double a);
	void setPosY(double a);
	CGPoints getBestPos();
	void movePosX();
	void movePosY();
	virtual void movePos();
	virtual void speedChange(CGPoints globalBest);
	//update mix them all up
	virtual void update(CGPoints *globalBest, CGPoints targetPoint);
	//const/operators
	Player();
	Player(int i, int j, CGPoints targetPoint, vector<double> v,char type,int id);
	Player(CGPoints posInput, CGPoints targetPoint,vector<double> v,char type,int id);
	Player(const Player &a);
	Player &operator=(const Player &a);
	bool operator==(const Player& a) ;
	virtual ~Player();
	bool operator<(const Player &a);
	CalDist getDist() { return distance; }
	friend std::ostream &operator<<(std::ostream &output,const Player &a) {
		cout << a.type <<" "<< round(100*a.pos.GetX())/100 << " " << round(100*a.pos.GetY())/100;
		return output;
	}
};

#endif