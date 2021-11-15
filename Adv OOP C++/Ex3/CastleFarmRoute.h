#pragma once
#include "Peasant.h"
#include "Farm.h"
class CastleFarmRoute {
public:
	shared_ptr<Castle> castleTarget;
	shared_ptr<Farm> farmTarget;
	CastleFarmRoute getTimer() { return *this; }
	shared_ptr<Castle> getCastle() { return castleTarget; }
	shared_ptr<Farm> getFarm() { return farmTarget; }
	shared_ptr<Castle> setCastle() { return castleTarget; }
	shared_ptr<Farm> setFarm() { return farmTarget; }
	CastleFarmRoute(shared_ptr<Castle> a, shared_ptr<Farm> b) {
		castleTarget = a;
		farmTarget = b;
	}
};