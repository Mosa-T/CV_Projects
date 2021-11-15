#ifndef FORWARDS_H
#define FORWARDS_H

#include "Player.h"

class Forwards: public Player {
public:
	Forwards():Player() {}

	Forwards(int i, int j, CGPoints targetPoint, vector<double> v,char type,int id):Player(i,j,targetPoint,v,type,id) {
		
	}

	Forwards(CGPoints posInput, CGPoints targetPoint, vector<double> v,char type,int id):Player(posInput,targetPoint,v,type,id) {
		
	}

	Forwards(const Forwards &a) :Player(a) {
		
	}
	~Forwards(){}
	 void IncDecSpeed(Player *p, CGPoints globalBest, CGPoints currPos) {
		srand((int)time(NULL));
		double random1, random2;
		random1 = ((((double)rand()) / RAND_MAX));
		random2 = ((((double)rand()) / RAND_MAX));
		speed[0] = 0.25*speed[0] + random1 * (this->getBestPos().GetX() - currPos.GetX()) + random2 * ((globalBest.GetX() - currPos.GetX()));
		speed[1] = 0.25*speed[1] + random1 * ((this->getBestPos().GetY() - currPos.GetY())) + random2 * ((globalBest.GetY() - currPos.GetY()));
	}


	 void update(CGPoints *globalBest, CGPoints targetPoint) {
		 CGPoints temp1 = this->getPos();
		 movePos();
		 Forwards::speedChange(*globalBest,temp1);
		 setDistance(targetPoint);
	 }
	 void speedChange(CGPoints globalBest,CGPoints currPos) {
		 Forwards::IncDecSpeed(this, globalBest,currPos);
	 }
};







#endif