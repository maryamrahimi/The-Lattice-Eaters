//Wanderer.h

#pragma once

#include "Particle.h"
#include <list>
#include "WandererFoot.h"
#include "Food.h"
#include "boost\shared_ptr.hpp"

using namespace ci;

class Wanderer : public Particle {
public:
	Wanderer(Vec2f loc);
	virtual ~Wanderer();
	virtual void update();
	virtual void draw();
	virtual void applyForce( Vec2f force );
	virtual void applyForce( boost::shared_ptr<Particle> p );
	virtual void constrain(Vec2f min, Vec2f max);
	void addFoot(Vec2f loc);

protected:
	std::list<boost::shared_ptr<WandererFoot>> mFeet;
	int numFeet;
	float speedCoefficient;
};