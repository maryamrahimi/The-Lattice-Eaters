//LSystem.h
#pragma once

#include "cinder\gl\gl.h"
#include "cinder\CinderMath.h"
#include "cinder\Rand.h"
#include "Food.h"
#include <vector>
#include "boost\shared_ptr.hpp"
#include "cinder\Perlin.h"

using namespace ci;
using namespace std;
using boost::shared_ptr;

class LSystem {
public:
	LSystem( Vec2f _loc );

	void simulate( int gen );
	string iterate( string _prod, string _rule );

	bool isDead();

	void updateList();
	void update();
	void draw();

	int mSteps, mInitNum;
	float mSomeStep, mXOff;
	string mAxiom, mRule;
	float mStartLength, mTheta;


	string mProduction;
	float mDrawLength;
	int mGenerations;

	Perlin mPerlin;
	Vec2f mLoc;

	vector<boost::shared_ptr<Food>> mFood;
};