#ifndef GOALIE_H
#define GOALIE_H

#include "Player.h"

class Goalie : public Player {
public:
	Goalie() :Player() {}

	Goalie(int i, int j, CGPoints targetPoint, vector<double> v,char type,int id) :Player(i,j,targetPoint, v,type,id) {
		
	}
	~Goalie(){}
	Goalie(CGPoints posInput, CGPoints targetPoint, vector<double> v,char type,int id) :Player(posInput, targetPoint, v,type,id) {
		
	}

	Goalie(const Goalie &a) :Player(a) {
		
	}
	void IncDecSpeed(Player *p, CGPoints globalBest,CGPoints currPos) {
		srand((int)time(NULL));
		double random1, random2;
		random1 = ((((double)rand()) / RAND_MAX));
		random2 = ((((double)rand()) / RAND_MAX));
		speed[0] = 0.01*speed[0] + (-0.1)*random1 * (this->getBestPos().GetX() - currPos.GetX()) + (-0.25)*random2 * ((globalBest.GetX() - currPos.GetX()));
		speed[1] = 0.01*speed[1] + (-0.1)*random1 * ((this->getBestPos().GetY() - currPos.GetY())) + (-0.25)*random2 * ((globalBest.GetY() - currPos.GetY()));
	}
	void update(CGPoints *globalBest, CGPoints targetPoint) {
		CGPoints temp1 = this->getPos();
		movePos();
		Goalie::speedChange(*globalBest,temp1);
		setDistance(targetPoint);
	}
	void speedChange(CGPoints globalBest,CGPoints currPos) {
		Goalie::IncDecSpeed(this, globalBest,currPos);
	}


};







#endif