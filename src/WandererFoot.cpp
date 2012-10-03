
#include "WandererFoot.h"
#include "cinder\Rand.h"
#include "cinder\Perlin.h"
#include "cinder\CinderMath.h"
#include "cinder\app\App.h"
#include "boost\foreach.hpp"


WandererFoot::WandererFoot(Vec2f parent, Vec2f loc) {
	
	mType = WANDERERFOOT;

	mParent = parent;
	mLoc = Vec2f( 0.0f, 0.0f );
	mLoc = loc;
	mRad = 1;

	float velx = Rand::randFloat( .0000001, 1.0f );
	float vely = Rand::randFloat( .0000001, 1.0f );
	velx = (velx * 2.0f) - 1.0f;
	vely = (vely * 2.0f) - 1.0f;

	mVel = Vec2f( velx, vely );
	mAcc = Vec2f( 0.0f, 0.0f );
}

void WandererFoot::update() {

	Perlin mPerlin = Perlin( 4, Rand::randInt( 0, 1000000 ) );
	
	float pX = mLoc.x * .003f;
	float pY = mLoc.y * .003f;
	float pZ = app::getElapsedFrames() * 0.1f;
	
	float pNoise = mPerlin.fBm( Vec3f( pX, pY, pZ ) );
	
	float angle = 15.0f * pNoise;
	
	mVel += Vec2f( cos(angle), sin(angle) ) * 0.05f;
	
	mVel += mAcc;
	mVel.limit(2.0f);
	mLoc += mVel;
	constrain();
	mAcc.set(0.0f,0.0f);
}

void WandererFoot::constrain() {
	
	float vMulti = Rand::randFloat( -0.2f, -0.7f );
	float tDist = mLoc.distance(mParent);

	if( tDist - 15 >= 15 ) mVel *= vMulti;

}

Vec2f WandererFoot::getVel() {
	return mVel;
}

void WandererFoot::updateParent( Vec2f parent ) {
	mParent = parent;
}