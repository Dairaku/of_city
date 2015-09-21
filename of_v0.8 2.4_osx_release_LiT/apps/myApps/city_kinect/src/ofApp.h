#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int 　y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofPoint pos;
    //半径の設定
    float radius;
    
    ofBoxPrimitive box; //直方体
    ofSpherePrimitive sphere; //球体
    ofCamera cam; //cam
    ofImage BackgroundImage; //BackgroundImageの名前
    ofImage ofLogo; //cubeに貼り付ける画像の名前
    
    //Sound
    ofSoundPlayer mySound; //クラスをインスタンス化
    int GetPrecision=1; //waveの精度
    float *volume; //変数ポインタ
    
    void audioIn(float * input, int bufferSize, int nChannels); //サウンドinするためのイベント
    vector <float> left; //Lchのベクトル(L出力について)
    ofSoundStream soundStream; //サウンドストリーム(音声の出力入力等をコントロールしている)
    
    int slide; //波形を心電図のようにずらしていくための変数
    int elapsedTime; //経過時間
    int red,green,blue; //rgb値(ランダムでつかう?)
    
};