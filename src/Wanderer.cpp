//Wanderer.cpp

#include "Wanderer.h"
#include "boost\foreach.hpp"
#include "cinder\Rand.h"
#include "cinder\gl\gl.h"
#include "cinder\app\App.h"
#include "boost\lexical_cast.hpp"
#include "boost\enable_shared_from_this.hpp"

Wanderer::Wanderer(Vec2f loc) {
	mType = WANDERER;
	mLoc = loc;
	mVel = Vec2f( 0.0f, 0.0f );
	mAcc = Vec2f( 0.0f, 0.0f );
	mColor = ColorA( 0.0f, 0.0f, 0.0f, 1.0f );
	mRad = 15;
	mLife = 30000;
	numFeet = 5;
	for( int i = 0; i < numFeet; i++ ) {
		double x = mRad * cos( lmap((double)i,0.0,(double)numFeet,0.0, 2*M_PI));
		double y = mRad * sin( lmap((double)i,0.0,(double)numFeet,0.0, 2*M_PI));
		
		addFoot( Vec2f(mLoc.x + (float)x, mLoc.y + (float)y) );
	}
	speedCoefficient = 0.5f;
}

Wanderer::~Wanderer() {
	mFeet.clear();
}

void Wanderer::update() {
	
	for( std::list<boost::shared_ptr<WandererFoot>>::iterator pi = mFeet.begin(); pi != mFeet.end(); ++pi ) {
		boost::shared_ptr<WandererFoot> nwfA( *pi );
		for( std::list<boost::shared_ptr<WandererFoot>>::iterator ppi = mFeet.begin()++; ppi != mFeet.end(); ++ppi ) {
			
			boost::shared_ptr<WandererFoot> nwfB( *ppi );
			if( nwfA != nwfB ) {
				float dist = nwfA->getLoc().distance( nwfB->getLoc() );
				dist -= (nwfB->getRadius() + nwfA->getRadius() ) * 2.0f;
				if( dist < 0.0f ) {
				Vec2f vMulti = Rand::randVec2f();
				vMulti *= -2.0f;
				nwfA->applyForce( vMulti );
				}
			}
		}
		nwfA->updateParent( mLoc );
		nwfA->update();
		float theta = atan2( mLoc.x-nwfA->getLoc().x, mLoc.y-nwfA->getLoc().y );
		float dist = mLoc.distance(nwfA->getLoc())/mRad;
		mVel += Vec2f( dist*sin(theta),dist*cos(theta))*-1;
	}
	mVel = mVel / (float)mFeet.size() * speedCoefficient;
	mLoc += mVel;
	constrain(Vec2f(0.0f,0.0f), Vec2f((float)app::getWindowWidth(),(float)app::getWindowHeight()));
	mColor = mColor.lerp( 0.3f, ColorA( 0.0f, 0.0f, 0.0f, 1.0f ) );
	mAcc.set(0.0f,0.0f);
	speedCoefficient = 0.5f;
}

void Wanderer::draw() {
	glLineWidth( 1.0f );
	ci::gl::color( mColor );
	ci::gl::drawStrokedCircle( mLoc, 10 );
	glBegin(GL_LINE_LOOP);
	BOOST_FOREACH( boost::shared_ptr<WandererFoot> nwf, mFeet ) {
		ci::Vec2f iLoc = ci::Rand::randVec2f();
		iLoc += ci::Rand::randFloat() * 2.0f;
		ci::gl::vertex( mLoc + iLoc );
		ci::gl::vertex(nwf->getLoc());
	}
	glEnd();
	BOOST_FOREACH( boost::shared_ptr<WandererFoot> nwf, mFeet ) {
		ci::gl::drawStrokedCircle( nwf->getLoc(), (float)nwf->getRadius() );
	}
}

void Wanderer::applyForce( Vec2f force ) {
	BOOST_FOREACH( boost::shared_ptr<WandererFoot> nwf, mFeet ) {
		nwf->applyForce( force );
	}
}

void Wanderer::applyForce( boost::shared_ptr<Particle> p ) {
	if ( p->getType() == Particle::PType::FOOD ) {
		BOOST_FOREACH( boost::shared_ptr<WandererFoot> nwf, mFeet ) {

			ci::Vec2f fsLoc = p->getLoc();
			int fsLife = p->getLife();
			float dist = fsLoc.distance(nwf->getLoc());
			dist = 1.0f/dist;
			float qLife = float(fsLife)/200.0f;
			ci::Vec2f force = nwf->getLoc() - fsLoc;
			force *= -1;
			force.normalize();
			force *= qLife + dist;
			nwf->applyForce( force );
		}
		speedCoefficient = 0.5f;
	}
}

void Wanderer::constrain(Vec2f min, Vec2f max) {
	if ( mLoc.x < min.x - (mRad+15) ) {
		mLoc.x = max.x + mRad + 15 ;
	}
	else if ( mLoc.y < min.y - (mRad+15) ) {
		mLoc.y = max.y + mRad + 15 ;
	}
	if ( mLoc.x > max.x + (mRad+15) ) {
		mLoc.x = min.x - mRad + 15;
	}
	else if ( mLoc.y > max.y + (mRad+15) ) {
		mLoc.y = min.y - mRad - 15;
	}
}

void Wanderer::addFoot(Vec2f loc) {
	mFeet.push_back( boost::shared_ptr<WandererFoot>(new WandererFoot( mLoc, loc) ));
}