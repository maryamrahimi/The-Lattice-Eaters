//Particle.h
#pragma once
#include "cinder\Vector.h"
#include "cinder\Color.h"

class Particle {
public:
	virtual void update() {}
	virtual void draw() {}
    virtual void applyForce(ci::Vec2f force){ mAcc += force; } 
	virtual void constrain() {}
	
	bool isDead() { if(mLife <= 0 ) return true; else return false; }
	ci::Vec2f getLoc() { return mLoc; }
	ci::ColorA getColor() { return mColor; }
	int getRadius() { return mRad; }
	int getLife() { return mLife; }
	void setLife( int l ) { mLife = l; }
	

	enum PType { WANDERER, WANDERERFOOT, FOOD, PHEREMONE };

	PType getType() { return mType; }

protected:
	int mLife;
	ci::Vec2f mLoc, mVel, mAcc;
	ci::ColorA mColor;
	int mRad;
	PType mType;
};