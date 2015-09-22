#include "ofApp.h"

void testApp::setup() {
    //画面設定
    // ofBackgroundHex(0x000000);
    
    ofSetFrameRate(60);
    
    soundStream.setup(this, 0, 1, 44100, 256, 4);
    
    // Kinect初期設定
    // 深度とRGB情報のずれを補整
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    // 角度を調整(0度に)
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    ofToggleFullscreen();//画面をフルスクリーンモードにする。
    
}

void testApp::update() {
    // Kinect更新
    kinect.update();
    
    curVol = curVol * 10000;
}

void testApp::draw() {
    ofBackground(255, 255, 255);
    // ドラッグで視線を変更できるように(ofEasyCam)
    easyCam.begin();
    //ポイントクラウドの描画
    drawPointCloud();
    easyCam.end();
    cout << curVol << endl;
}

void testApp::drawPointCloud() {
    // 画面の幅と高さ
    int w = ofGetWidth();
    int h = ofGetHeight();
    // メッシュを生成
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    
    // 設定した間隔で、画面の深度情報と色を取得してメッシュの頂点に設定
    int step = 2;
    
    randomColor.setHsb(ofRandom(255), ofRandom(255), ofRandom(255));
    for(int y = 0; y < h; y += step) {
        for(int x = 0; x < w; x += step) {
            if(kinect.getDistanceAt(x, y) > 0) {
                //mesh.addColor(kinect.getColorAt(x,y));
                mesh.addColor(randomColor);
                mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
            }
        }
    }
    
    // メッシュの頂点を描画
    glPointSize(2);
    ofPushMatrix();
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000);
    glEnable(GL_DEPTH_TEST);
    mesh.drawVertices();
    glDisable(GL_DEPTH_TEST);
    ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::exit() {
    // Kinect終了
    kinect.close();
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
    
    // 矢印キーでKinectの角度を操作
    switch (key) {
            
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
    }
    
    // if(key=='f'){//もしキーボードで'f'を入力したとき
    //    ofToggleFullscreen();//画面をフルスクリーンモードにする。
    // }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    curVol = 0.0;
    for (int i = 0; i < bufferSize; i++) {
        curVol += input[i]*input[i];
    }
    curVol /= bufferSize;
}