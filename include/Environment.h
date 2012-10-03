//Environment.h
#pragma once
#include <vector>
#include "cinder\Vector.h"
#include "Food.h"
#include "Wanderer.h"
#include "LSystem.h"
#include "boost\shared_ptr.hpp"
#include "boost\scoped_ptr.hpp"

using namespace ci;
using std::vector;
using boost::shared_ptr;

class Environment {
public:
	Environment();
	Environment( int width, int height );
	void addWanderer(Vec2f loc);
	void addFood(Vec2f loc, ColorA color);

	boost::shared_ptr<Particle> findNearestFood( Wanderer inwanderer );

	void update();
	void draw();

private:
	int mWidth, mHeight;

	vector<Wanderer> mWanderers;
	vector<boost::shared_ptr<Food>> mFood;
};