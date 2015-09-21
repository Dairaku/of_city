#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
 
#include "MyCircle.h"
 
#include <deque>
 
//色の基本的な情報を持ったクラスを作ります。
class Color {
public:
        float hue, sat, bri;
        ofxVec2f pos;
};
 
class testApp : public ofBaseApp
{
     
public:
     
        void setup();
        void update();
        void draw();
        void exit();
     
        void keyPressed  (int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
     
        void audioReceived  (float * input, int bufferSize, int nChannels);
        float * left;
        float * right;
        int     bufferCounter;
        int     drawCounter;
     
        ofxKinect kinect;
     
        float rotX, rotY;
     
        int nearThreshold;
        int farThreshold;
     
        int angle;
     
        int f_screen;
     
        //もともとの映像情報
        ofxCvColorImage colorImg;
     
        //HSV系に変換した映像情報
        ofxCvColorImage colorImgHSV;
     
        //HSV系の色相、彩度、明度のマップ
        ofxCvGrayscaleImage hueImg;
        ofxCvGrayscaleImage satImg;
        ofxCvGrayscaleImage briImg;
     
        //色を追跡して輪郭を出すための映像情報
        ofxCvGrayscaleImage reds;
     
        //追跡する色
        Color one;
     
        //もとの映像情報のピクセルの彩度と明度が
        //指定した色に近ければ255を代入、遠ければ0を代入
        unsigned char * colorTrackedPixelsRed;
     
        //二値画像
        ofTexture trackedTextureRed;
     
        //輪郭を判別
        ofxCvContourFinder finderRed;
        ofxCvContourFinder contourFinder;
     
        ofTexture           calibratedTex;
     
        int                 threshold;
        bool                bLearnBakground;
     
        deque <MyCircle *> circles;
};