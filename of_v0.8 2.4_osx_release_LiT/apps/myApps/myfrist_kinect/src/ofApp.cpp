#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    if (!kinect.isConnected()){
        ofSystemAlertDialog("Serial Error: Kinect is not connected. Check a USB port then push space bar.");
    }
    
    //gui
    ofxGuiSetDefaultWidth(300);
    ofxGuiSetDefaultHeight(10);
    gui.setup("Depth Making Control");
    gui.setPosition(10,10);
    //gui.add(radius.set( "Radius", 0, 0, 255 ));
    gui.add(near.set( "near", 0, 0, 255 ));
    gui.add(far.set( "far", 255, 0, 255 ));
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    if (kinect.isFrameNew()) {
        cameraImage.setFromPixels(kinect.getPixels(), kinect.width, kinect.height, OF_IMAGE_COLOR);
        
        depthImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
        
        unsigned char * cameraPixels = cameraImage.getPixels();
        unsigned char * depthPixels = depthImage.getPixels();
        maskedImage.allocate(kinect.width, kinect.height, OF_IMAGE_COLOR);
        
        unsigned char * maskedPixels = maskedImage.getPixels();
        
        for (int i=0; i<kinect.width*kinect.height; i++ ){
            if ((255-far.get() < depthPixels[i]) && (depthPixels[i] < 255-near.get())){
                maskedPixels[i*3] = cameraPixels[i*3+1];
                maskedPixels[i*3+1] = cameraPixels[i*3+1];
                maskedPixels[i*3+2] = cameraPixels[i*3+2];
            } else {
                maskedPixels[i*3] = 0;
                maskedPixels[i*3+1] = 0;
                maskedPixels[i*3+2] = 0;
            }
        }
        maskedImage.setFromPixels(maskedPixels, kinect.width, kinect.height, OF_IMAGE_COLOR);
    }
    cameraImage.draw(0, 0, kinect.width, kinect.height);
    depthImage.draw(0, kinect.height, kinect.width/2, kinect.height/2);
    
    maskedImage.draw(kinect.width/2, kinect.height, kinect.width/2, kinect.height/2);
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case ' ':
            kinect.init(); //初期化
            kinect.open();
            if (!kinect.isConnected()){
                ofSystemAlertDialog("Serial Error: Kinect is not connected. Check a USB port then push space bar.");
            }
            break;
    }
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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
