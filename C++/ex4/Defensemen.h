#ifndef DEFENSEMEN_H
#define DEFENSEMEN_H

#include "Player.h"

class Defensemen : public Player {
public:
	Defensemen() :Player() {}

	Defensemen(int i, int j, CGPoints targetPoint, vector<double> v,char type,int id) :Player(i,j,targetPoint, v,type,id) {
	
	}
	~Defensemen(){}
	Defensemen(CGPoints posInput, CGPoints targetPoint, vector<double> v,char type,int id) :Player(posInput, targetPoint, v,type, id) {
	
	}

	Defensemen(const Defensemen &a) :Player(a) {
	
	}
	void IncDecSpeed(Player *p, CGPoints globalBest,CGPoints currPos) {
		srand((int)time(NULL));
		double random1, random2;
		random1 = ((((double)rand()) / RAND_MAX));
		random2 = ((((double)rand()) / RAND_MAX));
		speed[0] = 0.05*speed[0] + 0.1*random1 * (this->getBestPos().GetX() - currPos.GetX()) + 0 *random2 * ((globalBest.GetX() - currPos.GetX()));
		speed[1] = 0.05*speed[1] + 0.1*random1 * ((this->getBestPos().GetY() - currPos.GetY())) + 0 *random2 * ((globalBest.GetY() - currPos.GetY()));
	}
	
	void update(CGPoints *globalBest, CGPoints targetPoint) {
		CGPoints temp1 = this->getPos();
		movePos();
		setDistance(targetPoint);
		Defensemen::speedChange(*globalBest,temp1);
	}
	void speedChange(CGPoints globalBest,CGPoints currPos) {
		Defensemen::IncDecSpeed(this, globalBest,currPos);
	}
};







#endif