#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	int dirLoadIndex;
	ofDirectory dir;

	dir.allowExt("png");
	dir.listDir("LUT/");
	dir.sort();
	int dirSize = dir.size();
	cout << "num LUTs:" << dirSize << endl;
	luts.resize(dirSize);
	lutNames.resize(dirSize);

	for (int i = 0; i < dirSize; i++)
	{
		string lutPath = dir.getPath(i);
		ofStringReplace(lutPath, "LUT/", "");
		ofStringReplace(lutPath, ".png", "");
		//ofStringReplace(lutPath, "\/", "");//TODO: delete this char...
		lutNames[i] = lutPath;

		//auto paths = ofSplitString(dir.getPath(i), "LUT/");
		//auto names = ofSplitString(paths[1], ".png");
		//lutNames[i] = names[0];

		luts[i].load(dir.getPath(i));

		cout << "lutNames[i] :" << lutNames[i] << endl;
	}

	description = "space key : switch thumbnail / full-size view\n";
	description += "left key : previous filter\n";
	description += "right key : next filter\n";

	//source image
	//video.initGrabber(1920, 1080);
	image.load("img/background3.jpg");
	//image.load("img/photo2.jpg");

	isThumbnailView = true;
	lutIndex = 0;

	numCols = 7;
	numRows = 7;
	//thumbnailWidth = 1920 / (dirSize/ numCols);
 //   thumbnailHeight = 1080 / (dirSize / numRows);
	thumbnailWidth = 1920 / numCols;
	thumbnailHeight = 1080 / numRows;
}

//--------------------------------------------------------------
void ofApp::update() {
	//video.update();
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	if (isThumbnailView) 
	{
		for (int i = 0; i < luts.size(); i++)
		{
			//luts[i].begin();
			//image.draw(thumbnailWidth * fmodf(i, numCols), thumbnailHeight * floor(i / numRows), thumbnailWidth, thumbnailHeight);
			//luts[i].end();
			//
			//ofDrawBitmapStringHighlight(lutNames[i], thumbnailWidth * fmodf(i, numCols) + 4, thumbnailHeight * floor(i / numRows) + 14);

			luts[i].begin();
			//video.draw(thumbnailWidth * fmodf(i, 3), thumbnailHeight * floor(i / 3), thumbnailWidth, thumbnailHeight);
			image.draw(thumbnailWidth * fmodf(i, 3), thumbnailHeight * floor(i / 3), thumbnailWidth, thumbnailHeight);
			luts[i].end();

			ofDrawBitmapStringHighlight(lutNames[i], thumbnailWidth * fmodf(i, 3) + 4, thumbnailHeight * floor(i / 3) + 14);
		}
	}
	else 
	{
		luts[lutIndex].begin();
		//video.draw(0, 0, 1920, 1080);
		image.draw(0, 0, 1920, 1080);
		luts[lutIndex].end();

		ofDrawBitmapStringHighlight(lutNames[lutIndex], 4, 14);
	}

	ofDrawBitmapStringHighlight("FPS : " + ofToString(ofGetFrameRate()) + "\n" + description, 4, ofGetHeight() - 48);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case ' ':
		isThumbnailView = !isThumbnailView;
		break;

	case OF_KEY_RIGHT:
		if (!isThumbnailView) {
			lutIndex++;
			lutIndex %= luts.size();
		}
		break;

	case OF_KEY_LEFT:
		if (!isThumbnailView) {
			lutIndex--;
			if (lutIndex < 0) {
				lutIndex = luts.size()-1;
			}
		}
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
