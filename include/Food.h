//Food.h
#pragma once

#include "boost\weak_ptr.hpp"
#include "Particle.h"

using namespace ci;

class Food : public Particle {
public:
	Food();
	virtual ~Food();
	Food(Vec2f loc);
	Food(Vec2f loc, ColorA col);
	virtual void update();
	virtual void draw();

	void setNext(boost::weak_ptr<Food> infood);


	bool isBeingEaten();
	void setBeingEaten();
	
private:
	bool mBeingEaten;
	boost::weak_ptr<Food> mNextFood;
	static const int maxLife = 1000;
};