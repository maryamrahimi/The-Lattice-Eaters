//FaceDetect.h

#include "cinder\Capture.h"
#include "cinder\qtime\QuickTime.h"
#include "cinder\gl\Texture.h"
#include "cinder\app\App.h"

#include "CinderOpenCV.h"

using namespace ci;
using namespace std;

class FaceDetect {
public:
	FaceDetect();

	void updateFaces( Surface cameraImage );
	void update();
	void drawTexture( const Area &bounds );

	gl::Texture           mCameraTexture;
	Surface               mSurface;
	Capture               mCapture;
	
	cv::CascadeClassifier mFaceCascade;
	vector<Rectf>         mFaces;

	static const int MAX_FEATURES = 300;
};

FaceDetect::FaceDetect() {


	

	mCapture = Capture( 640, 480 );
	mCapture.start();

	mFaceCascade.load( "C:/Users/Brian/Documents/cinder projects/FinalWanderer/resources/haarcascade_frontalface_alt.xml" );
}

void FaceDetect::updateFaces( Surface cameraImage ) {

	const int calcScale = 4;

	cv::Mat grayCameraImage( toOcv( cameraImage, CV_8UC1 ) );

	int scaledWidth = cameraImage.getWidth() / calcScale;
	int scaledHeight = cameraImage.getHeight() / calcScale;
	cv::Mat smallImg( scaledHeight, scaledWidth, CV_8UC1 );
	cv::resize( grayCameraImage, smallImg, smallImg.size(), 0, 0, cv::INTER_LINEAR );

	cv::equalizeHist( smallImg, smallImg );

	mFaces.clear();

	vector<cv::Rect> faces;
	mFaceCascade.detectMultiScale( smallImg, faces );
	for( vector<cv::Rect>::const_iterator faceIter = faces.begin(); faceIter != faces.end(); ++faceIter ) {
		Rectf faceRect( fromOcv( *faceIter ) );
		faceRect *= calcScale;
		mFaces.push_back( faceRect );
	}
}

void FaceDetect::update() {
	if( mCapture && mCapture.checkNewFrame() ) {
		mSurface = mCapture.getSurface();
		mCameraTexture = gl::Texture(mSurface);
		updateFaces( mSurface );
	}
}

void FaceDetect::drawTexture( const Area &bounds ) {
	//if( mSurface ) gl::draw( mCameraTexture );
//	gl::color( ColorA( 1.0f, 1.0f, 1.0f, 0.6f ) );
	//gl::drawSolidRect( app::getWindowBounds() );
	
}