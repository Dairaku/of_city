#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0, 0, 0);
    ofSetWindowShape(640, 480);
    ofSetFrameRate(30);
    
    kinect.setup();
    kinect.setRegister(true);
    kinect.setMirror(true);
    kinect.addDepthGenerator();
    kinect.addImageGenerator();
    
    kinect.getDepthGenerator().GetAlternativeViewPointCap().SetViewPoint(kinect.getImageGenerator());
    
    kinect.start();
    
    maskedImage.allocate(640, 480, OF_IMAGE_COLOR_ALPHA);
    scenery.loadImage("photo.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    unsigned char *maskedImageData = maskedImage.getPixels();
    unsigned char *imageData = kinect.getImagePixels().getPixels();
    unsigned short *depthData = kinect.getDepthRawPixels().getPixels();
    
    for (int k=0; k<640*480; k++) {
        maskedImageData[k*4+0]=imageData[k*3+0];
        maskedImageData[k*4+1]=imageData[k*3+1];
        maskedImageData[k*4+2]=imageData[k*3+2];
        
        if (880 <= depthData[k]&&depthData[k]<1200)
            maskedImageData[k*4+3]=255;
            maskedImageData[k*4+3]=0;
    }
    maskedImage.setFromPixels(maskedImageData, 640, 480, OF_IMAGE_COLOR_ALPHA);
}

//--------------------------------------------------------------
void ofApp::draw(){
    kinect.drawDepth(0,0,640,480);
    scenery.draw(640, 0, 640, 480);
    maskedImage.draw(640, 0, 640, 480);
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