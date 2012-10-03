//LSystem.cpp

#include "LSystem.h"
#include "cinder\app\App.h"


LSystem::LSystem( Vec2f _loc ) {
	mPerlin = Perlin();
	mLoc = _loc;
	mSteps = 0;
	mSomeStep = 0.1f;
	mXOff = 0.01f;
	mAxiom = "F";
	mRule = "|[+F]|[-F]F";
	mStartLength = 0.2f;
	mTheta = 90.0f;
	mInitNum = 3;
	mProduction = mAxiom;
	mDrawLength = mStartLength;
	mGenerations = 0;
	simulate ( mInitNum );
	updateList();
}

void LSystem::simulate( int gen ) {
	while( mGenerations < gen ) {
		mProduction = iterate( mProduction, mRule );
	}
}

string LSystem::iterate( string _prod, string _rule ) {
	mDrawLength = mDrawLength * 0.6f;
	mGenerations++;
	string new_production = _prod;
	int index = new_production.length()-1;
	for( int i = index; i >= 0; i-- ) {
		if( new_production.at(i) == 'F' ) new_production.replace( i, 1, _rule );
	}

	return new_production;
}

bool LSystem::isDead() {
	if ( mFood.size() < 0 ) return true;
	return false;
}

void LSystem::updateList() {
	mPerlin = Perlin( 8, Rand::randInt( 0, 100000 ) );
	mSteps = mProduction.length();
	if( mSteps > mProduction.length() ) {
		mSteps = mProduction.length();
	}
	gl::pushModelView();
	gl::translate( mLoc );
	gl::pushModelView();
	int countFood = 0;
	for( int i = 0; i < mSteps; i++ ) {
		char step = mProduction.at(i);

		if( step == 'F' || step == '|' ) {
			Vec2f current_loc = (gl::getModelView() * Vec4f( 0.0f, 0.0f, 0.0f, 1.0f )).xy();
			current_loc -= mStartLength;
			current_loc += mLoc;
			boost::shared_ptr<Food> add_food( new Food( current_loc, ColorA( ColorA::black() ) ) );
			mFood.push_back( add_food );
			if( countFood > 0 ) {
				boost::weak_ptr<Food> weakFood(add_food);
				mFood[countFood-1]->setNext( weakFood );
			}
			countFood++;
			gl::translate( 0, -mDrawLength + mPerlin.fBm( app::getElapsedFrames()*1.0f, i, 0.001f )*20000.0f );
		}
		else if( step == '+' ) {
			gl::rotate( mTheta + mPerlin.fBm( app::getElapsedFrames()*1.0f, i, 0.001f )*(2000.0f * i/30.0f));
		}
		else if( step == '-' ) {
			gl::rotate( -1*(mTheta + mPerlin.fBm( app::getElapsedFrames()*1.0f, i, 0.001f )*(2000.0f * i/30.0f)));
		}
		else if( step == '[' ) {
			gl::pushModelView();
		}
		else if( step == ']' ) {
			gl::popModelView();
		}
	}
	gl::popModelView();
	gl::popModelView();
}

void LSystem::update() {

}
void LSystem::draw() {

}