#include "ofApp.h"
#include <deque>
 
//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofBackground(255,255,255);
    ofSetCircleResolution(8);
    rotX = 0;
    rotY = 0;
     
    f_screen = 1;
     
        kinect.init();
        kinect.setVerbose(true);
        kinect.open();
     
    // zero the tilt on startup
        angle = 0;
        kinect.setCameraTiltAngle(angle);
     
    //Threshold
    nearThreshold = 230;
        farThreshold  = 80;
     
    calibratedTex.allocate(kinect.width, kinect.height,GL_RGB);
        bLearnBakground = true;
     
    //最初は色が原点にあることにします
        one.pos = ofxVec2f(0,0);
     
    //それぞれの映像情報の大きさを指定してあげます。
        colorImg.allocate(kinect.width, kinect.height);
        colorImgHSV.allocate(kinect.width, kinect.height);
     
    hueImg.allocate(kinect.width, kinect.height);
        satImg.allocate(kinect.width, kinect.height);
        briImg.allocate(kinect.width, kinect.height);
     
    reds.allocate(kinect.width, kinect.height);
     
        //二値画像を作るための配列の大きさを指定
        colorTrackedPixelsRed = new unsigned char [kinect.width*kinect.height];
     
        //二値画像の大きさ
        trackedTextureRed.allocate(kinect.width, kinect.height, GL_LUMINANCE);
     
}
 
//--------------------------------------------------------------
void ofApp::update()
{
     
        kinect.update();
     
    unsigned char * kinectPixels = kinect.getPixels();
     
    //colorImgの中身をピクセルごとに指定
        colorImg.setFromPixels(kinectPixels, kinect.width, kinect.height);
     
    //HSV系に変換
    colorImgHSV = colorImg;
        colorImgHSV.convertRgbToHsv();
     
    //色相、彩度、明度にマッピング
    colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
     
        hueImg.flagImageChanged();
        satImg.flagImageChanged();
        briImg.flagImageChanged();
     
    //ピクセルの配列をそれぞれに作成
        unsigned char * huePixels = hueImg.getPixels();
        unsigned char * satPixels = satImg.getPixels();
        unsigned char * briPixels = briImg.getPixels();
     
    //ピクセルの数
        int nPixels = kinect.width*kinect.height;
     
    //ピクセルの色が指定した色と色相と彩度が近ければ、
        //colorTrackedPixelsRedに255を、遠ければ0を代入。
        for (int i=0; i<nPixels; i++) {
                if ( (huePixels[i]>=one.hue-12 && huePixels[i] <= one.hue + 12) &&
                    (satPixels[i]>=one.sat-24 && satPixels[i]<=one.sat+200)){
                        colorTrackedPixelsRed[i] = 255;
                    }else {
                            colorTrackedPixelsRed[i] = 0;
                        }
            }
     
    //colorTrackedPixelsRedをもとにredsを作成
        reds.setFromPixels(colorTrackedPixelsRed, kinect.width, kinect.height);
     
    //輪郭線を見つける
        finderRed.findContours(reds, 10, nPixels/3, 1, false, true);
     
    //colorTrackedPixelsRedをもとにtrackedTextureRedを作成
        trackedTextureRed.loadData(colorTrackedPixelsRed,
                                   kinect.width, kinect.height, GL_LUMINANCE);
     
    //追跡する色の位置を中心にあわせる
        if (finderRed.blobs.size()>0) {
                one.pos = ofxVec2f(finderRed.blobs[0].centroid.x, finderRed.blobs[0].centroid.y);
            }
     
    //particle
    for(deque <MyCircle *>::iterator it = circles.begin(); it != circles.end();){
        (*it)->update();
        if ((*it)->dead) {
            delete *it;
            it = circles.erase(it);
        } else {
            ++it;
        }
    }
}
 
//--------------------------------------------------------------
void testApp::draw()
{
    //背景色を指定
        ofBackground(100, 100, 100);
        ofSetColor(255, 255, 255, 255);
     
    if (f_screen > 0) {
        //元画像
        kinect.draw(0, 0);
         
        //元映像に輪郭線を表示
        finderRed.draw(0, 0);
    }
     
    //出力
    glPushMatrix();
     
    //マウスでの回転処理
    //回転軸
    glTranslatef(ofGetWidth()/2, ofGetHeight()/2, 0);
     
    if (f_screen < 0) {
        ofRotateX(rotX);
        ofRotateY(rotY);
    }
     
    //キネクト映像の表示軸
    glTranslatef(kinect.width/2, kinect.height/2, 1000);
     
    //ピクセル精度
    int step = 3;
    //補正
    int calibrateX = 10;
    int calibrateY = 15;
     
    //キネクトから画像の色情報取得（unsigned:負の値を使えなくする）
    unsigned char * calibratedPixels = kinect.getCalibratedRGBPixels();
    for (int j = 0; j < kinect.height; j+=step) {
        for (int i = 0; i < kinect.width; i+=step) {
             
            //深度情報
            float distance = kinect.getDistanceAt(i, j);
             
            int colorPos = kinect.width * j * 3 + i * 3;
            ofSetColor(0, 0, 0, 100);
            ofBackground(255,255,255);
            //ofSetColor(calibratedPixels[colorPos], calibratedPixels[colorPos+1], calibratedPixels[colorPos+2], 255);
             
            glPushMatrix();
             
            //各ピクセルに座標の中心
            glTranslatef(i - kinect.width, j - kinect.height, distance * -8.0f);
             
            if(distance < 160){
                //ここで描画してる
                ofCircle(0, 0, step*0.5);
            }
            glPopMatrix();
        }
    }
     
    glTranslatef(-kinect.width, -kinect.height, -700);
     
    //パーティクル出す
    glPushMatrix();
    for (int i = 0; i < finderRed.nBlobs; i++){
        circles.push_back(new MyCircle(ofPoint(finderRed.blobs[i].centroid.x, finderRed.blobs[i].centroid.y, ofRandom(-600, 600)), ofRandom(1, 20), 1.0, 0.25, 10.0));
    }
    //draw particle
    for(deque <MyCircle *>::iterator it = circles.begin(); it != circles.end(); ++it){
        (*it)->draw();
    }
    glPopMatrix();
     
    //-----"f"キーを押す：フルスクリーン表示＆追跡情報等非表示
    if (f_screen > 0){
        //マウスカーソルを表示
        ofShowCursor();
        //追跡情報
        finderRed.draw(0, 0);
         
        //追跡する色の位置情報を表示
        ofSetColor(0xffffff);
        if (finderRed.blobs.size()>0) {
            char tempStr1[255];
            sprintf(tempStr1, "x:%f\ny:%f",
                    finderRed.blobs[0].centroid.x,
                    finderRed.blobs[0].centroid.y);
            ofDrawBitmapString(tempStr1, kinect.width, kinect.height);
        }
    }
    if (f_screen < 0) {
        ofHideCursor();
    }
     
    glPopMatrix();
     
}
 
//--------------------------------------------------------------
void testApp::exit()
{
    kinect.setCameraTiltAngle(0);
        kinect.close();
}
 
//--------------------------------------------------------------
void testApp::keyPressed (int key)
{
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            f_screen = f_screen * -1;
            break;
    }
}
 
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
    rotX = float(y) / ofGetHeight() * 120 - 60;
    rotY = float(x) / ofGetWidth() * 120 - 60;
}
 
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{}
 
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    unsigned char * huePixels = hueImg.getPixels();
        unsigned char * satPixels = satImg.getPixels();
        unsigned char * briPixels = briImg.getPixels();
     
        //クリックした場所の色を追跡する色に設定。
        x=MIN(x,hueImg.width-1);
        y=MIN(y,hueImg.height-1);
     
        if (button==0) {
                one.hue = huePixels[x+(y*hueImg.width)];
                one.sat = satPixels[x+(y*satImg.width)];
                one.bri = briPixels[x+(y*briImg.width)];
            }
}
 
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{}
 
//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{}
 
//--------------------------------------------------------------
void testApp::audioReceived     (float * input, int bufferSize, int nChannels){
        // samples are "interleaved"
        for (int i = 0; i < bufferSize; i++){
                left[i] = input[i*2];
                right[i] = input[i*2+1];
            }
        bufferCounter++;
}