#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofBackground(0, 0, 0);
    ofSetWindowShape(640, 480);
    ofSetFrameRate(30);
    
    kinect.setup();
    kinect.setRegister(true);
    kinect.setMirror(true);
    kinect.addImageGenerator();
    kinect.addDepthGenerator();
    
    kinect.getDepthGenerator().GetAlternativeViewPointCap().SetViewPoint(kinect.getImageGenerator());
    kinect.addUserGenerator();
    
    kinect.start();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    kinect.drawDepth(0,0,640,480);
    kinect.drawSkeletons(0,0,640,480);
    
    if (kinect.getNumTrackedUsers() > 0) {
        ofxOpenNIUser user = kinect.getTrackedUser(0);
        
        //draw joint-circle
        ofSetColor(255, 255, 255,ofRandom(255));
        for (int i = 0; i < user.getNumJoints(); i++) {
            ofxOpenNIJoint joint = user.getJoint((enum Joint) i);
            if (joint.isFound()) {
                float x = joint.getProjectivePosition().x;
                float y = joint.getProjectivePosition().y;
                ofCircle(x, y, 10);
            }
        }
    }
}
//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}