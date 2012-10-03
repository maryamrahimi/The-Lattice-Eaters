//WandererApp.cpp

#include "cinder\app\AppBasic.h"
#include "cinder\gl\gl.h"
#include "Environment.h"
#include "FaceDetect.h"
#include "cinder\Rand.h"
#include "cinder\Vector.h"


using namespace ci;
using namespace ci::app;

class WandererApp : public AppBasic {
public:
	void prepareSettings( Settings *settings );
	void setup();
	void update();
	void draw();

	Environment mEnv;
	FaceDetect mFaceDetect;
	Vec2f mLastFoodPos;
};

void WandererApp::prepareSettings( Settings *settings ) {
	settings->setWindowSize( 640, 480 );
	settings->setFrameRate( 60.0f );
}

void WandererApp::setup() {
	mEnv = Environment( getWindowWidth(), getWindowHeight() );
	for( int i = 0; i < 15; i++ ) {
		mEnv.addWanderer( Vec2f( Rand::randFloat( 25.0f, getWindowWidth() - 25.0f ), Rand::randFloat( 25.0f, getWindowHeight() - 25.0f ) ) );
	}
	mLastFoodPos = Vec2f( 0.0f, 0.0f );
}

void WandererApp::update() {
	mFaceDetect.update();
	if( mFaceDetect.mFaces.size() > 0 ) {
		for( std::vector<Rectf>::const_iterator fi = mFaceDetect.mFaces.begin(); fi != mFaceDetect.mFaces.end(); ++fi ) {
			if ( mFaceDetect.mCapture && mFaceDetect.mCameraTexture ) {
				if ( mLastFoodPos.distanceSquared( fi->getCenter() ) > 100.0f ) {
					mEnv.addFood( fi->getCenter(), ColorA::black() );
					mLastFoodPos = fi->getCenter();
				}
			}

		}
	}
	mEnv.update();
}

void WandererApp::draw() {
	gl::enableAlphaBlending();
	gl::clear( Color::white() );
	
	
	mEnv.draw();
	
}

CINDER_APP_BASIC( WandererApp, RendererGl )