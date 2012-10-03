//WandererFoot.h

#pragma once

#include "Particle.h"
#include "cinder\Vector.h"


using namespace ci;

class WandererFoot : public Particle {
public:
	WandererFoot(Vec2f parent, Vec2f loc);
	virtual void update();
	virtual void constrain();
	Vec2f getVel();
	void updateParent( Vec2f parent );

private:
	Vec2f mParent;
};