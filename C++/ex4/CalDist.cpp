#include "CalDist.h"
#include "Player.h"
double CalDist::GetDistance() { 
	return distance; 
}

void CalDist::setDist(const CGPoints &p, const CGPoints p2) {
	distance = p.distanceFrom(p2);
	if (bestDist == -1 || bestDist > distance)
	{
		bestDist = distance;
		bestPos = p;
	}
}
void CalDist::incDecDistance(Player &p, CGPoints target)
{ 
	setDist(p.getPos(), target);
}
double CalDist::getPersonalBestDis() {
	return bestDist;
}
CGPoints CalDist::getBestPos() { 
	return bestPos;
}
CalDist::CalDist(){ bestDist = -1; }
CalDist &CalDist::operator=(const CalDist &a) { this->bestDist = a.bestDist; this->bestPos = a.bestPos; this->distance = a.distance; return *this; }