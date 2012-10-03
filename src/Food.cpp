//Food.cpp

#include "Food.h"
#include "cinder\gl\gl.h"
#include "cinder\Rand.h"

Food::Food() {

	mType = FOOD;

	mLoc = Vec2f( 0.0f, 0.0f );
	mVel = Vec2f( 0.0f, 0.0f );
	mAcc = Vec2f( 0.0f, 0.0f );
	
	mLife = 1000;

	mRad = 2;

	mColor = ColorA( Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), 1.0f );

	mBeingEaten = false;
}

Food::~Food() {
	mNextFood.reset();
}

Food::Food(Vec2f loc) {
	mType = FOOD;
	mLoc = loc;
	mVel = Vec2f( 0.0f, 0.0f );
	mAcc = Vec2f( 0.0f, 0.0f );
	
	mLife = 1000;
	mRad = 2;

	mColor = ColorA( Rand::randFloat(), Rand::randFloat(), Rand::randFloat(), 1.0f );

	mBeingEaten = false;
}

Food::Food(Vec2f loc, ColorA col) {
	
	mType = FOOD;
	mLoc = loc;
	mVel = Vec2f( 0.0f, 0.0f );
	mAcc = Vec2f( 0.0f, 0.0f );
	
	mLife = 1000;
	
	mRad = 2;

	mColor = col;

	mBeingEaten = false;

}

void Food::update() {
	if( mBeingEaten ) {
		mLife -= 50;
	}
	else {
		mLife--;
	}

	mColor = ColorA( 0.0f, 0.0f, 0.0f, float(mLife)/maxLife );
	
}

void Food::draw() {
	gl::color( mColor );
	boost::shared_ptr<Food> accessFood( mNextFood.lock() );
	if( accessFood.use_count() > 0 ) {
		gl::drawStrokedRect( Rectf( Vec2f(mLoc.x-1,mLoc.y-1),Vec2f(mLoc.x+1,mLoc.y+1) ) );
		gl::drawLine( mLoc, accessFood->getLoc() );
	}
}

void Food::setNext( boost::weak_ptr<Food> infood ) {
	boost::weak_ptr<Food> nextFood( infood );
	mNextFood = nextFood;
}

bool Food::isBeingEaten() {
	return mBeingEaten;
}

void Food::setBeingEaten() {
	mBeingEaten = true;
}