#ifndef CALDIST_H
#define CALDIST_H

#include "CGPoints.h"
class Player;
class CalDist {
private:
	double distance;
	double bestDist;
	CGPoints bestPos;
public:
	CalDist();
	double GetDistance();
	void setDist(const CGPoints &p, const CGPoints p2);
	void incDecDistance(Player &p, CGPoints target);
	double getPersonalBestDis();
	CGPoints getBestPos();
	CalDist &operator=(const CalDist &a);
	~CalDist() {}
};

#endif