#include "Environment.h"
#include "boost\foreach.hpp"

#include "cinder\app\App.h"

Environment::Environment() {
	mWidth = 600;
	mHeight = 600;
}

Environment::Environment( int width, int height ) {
	mWidth = width;
	mHeight = height;
}

void Environment::addWanderer(Vec2f loc) {
	if( loc.x > 0 && loc.y > 0 && loc.x < mWidth && loc.y < mHeight ) {
		Wanderer w = Wanderer( loc );
		mWanderers.push_back( w );
	}
}

void Environment::addFood(Vec2f loc, ColorA color) {
	if( loc.x > 0 && loc.y > 0 && loc.x < mWidth && loc.y < mHeight && mFood.size() < 200 ) { 
		LSystem t_sys = LSystem( loc );
		for( vector<boost::shared_ptr<Food>>::iterator fi = t_sys.mFood.begin(); fi != t_sys.mFood.end(); ++fi ) {
			boost::shared_ptr<Food> newFood( *fi );
			mFood.push_back( newFood );
		}
	}
}

boost::shared_ptr<Particle> Environment::findNearestFood( Wanderer inwanderer ) {
	boost::shared_ptr<Particle> returnPart;
	float dist = mWidth*mHeight + 100;
	Vec2f wLoc = inwanderer.getLoc();
	int index = 0;
	for( int i = 0; i < mFood.size(); i++ ) {
		boost::shared_ptr<Food> f = mFood[i];
		float curdist = wLoc.distance( f->getLoc() );
		if( curdist < dist && curdist < 200.0f ) {
			dist = curdist;
			returnPart = f;
			index = i;
		}
	}
	if( returnPart.use_count() > 0 && index < mFood.size() && dist < 50) {
		mFood[index]->setBeingEaten();
	}
	return returnPart;
}

void Environment::update() {
	for( vector<Wanderer>::iterator wi = mWanderers.begin(); wi != mWanderers.end(); ++wi ) {
		vector<Wanderer>::iterator wwi = wi;
		for( ++wwi; wwi != mWanderers.end(); ++wwi ) {
			Vec2f dir = wi->getLoc() - wwi->getLoc();
			float distSqrd = dir.lengthSquared();
			if( distSqrd > 0.0f ) {
				dir.normalize();
				float nF = 1.0f / distSqrd;
				wi->applyForce( dir * nF * 5.0f );
				wwi->applyForce( -1 * dir * nF * 5.0f );
			}
		}
		boost::shared_ptr<Particle> forcePart = findNearestFood((*wi));
		if( forcePart.use_count() > 0 ) wi->applyForce(forcePart);
		wi->update();
	}
	for( vector<boost::shared_ptr<Food>>::iterator fi = mFood.begin(); fi != mFood.end(); ) {
		if ( (*fi)->isDead() ) {
			fi = mFood.erase(fi);
		}
		else {
			(*fi)->update();
			++fi;
		}
	}
}

void Environment::draw() {
	for( vector<Wanderer>::iterator wi = mWanderers.begin(); wi != mWanderers.end(); ++wi ) {
		wi->draw();
	}
	BOOST_FOREACH( boost::shared_ptr<Food> f, mFood ) {
		f->draw();
	}
}