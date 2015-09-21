#include "ofApp.h"

//この下にdefine NUM を書いたら　エラーが消えるはずだよ！
#define NUM 100

float maxSpeed;//ボックスの動くスピードの最大値
int maxScope;//ボックスの動ける最大範囲の半分
int boxSize;//ボックスのサイズ
int x[NUM],y[NUM],z[NUM];//ボックスのx,y,z座標
int speed_x[NUM],speed_y[NUM],speed_z[NUM];//ボックスのx,y,z方向の速度
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofSetVerticalSync(true);//画面の垂直同期をONに,素早い動きをした際に画面が途中までしか更新されずちらついてしまう現象を防いでいます。
    ofEnableAlphaBlending();//透明度を使用可能に
    maxSpeed=5;//ボックスの動くスピードの最大値
    maxScope = ofGetWidth()/4;//ボックスの動ける範囲の半分
    boxSize =60;


    for(int i=0;i<NUM;i++){//for文(0からNUM未満まで同じ処理を繰り返す。)
        x[i]=ofRandom(-1*maxScope,maxScope);//最初のx座標をランダムに入れる
        y[i]=ofRandom(-1*maxScope,maxScope);//最初のy座標をランダムに入れる
        z[i]=ofRandom(-1*maxScope,maxScope);//最初のz座標をランダムに入れる
        
        speed_x[i]=ofRandom(-1*maxSpeed,maxSpeed);
        speed_y[i]=ofRandom(-1*maxSpeed,maxSpeed);
        speed_z[i]=ofRandom(-1*maxSpeed,maxSpeed);
        
    }//for文の終了
    
}

//--------------------------------------------------------------
void ofApp::update(){

    for(int i=0;i<NUM;i++){//for文(0からNUM未満まで同じ処理を繰り返す。)
        
        if(abs(x[i])>maxScope){
            speed_x[i]*=-1;
        }
        
        x[i]+=speed_x[i];//x座標にx方向の速度を加えることで座標の更新を行う。
        y[i]+=speed_y[i];//y座標にy方向の速度を加えることで座標の更新を行う。
        z[i]+=speed_z[i];//z座標にz方向の速度を加えることで座標の更新を行う。
        
    }//for文の終了

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(255, 255, 255);//背景を(R,G,B)で白に指定
    cam.begin();// カメラ開始
    ofPushMatrix();//現在の座標系を一時的に保存する
    
    ofSetColor(0, 0, 200, 30);
    ofDrawBox(maxScope*2);
    ofNoFill();
    ofSetColor(0, 0, 200, 100);
    ofDrawBox(maxScope*2);
    ofFill();
    
    //ボックスの描画
    // ofSetColor(0, 190, 0,100);//ボックスの色を指定
    for(int i=0;i<NUM;i++){//for文(0からNUM未満まで同じ処理を繰り返す。)
        ofColor c;
        c.setHsb((i+127)%255,i%127+127,i%127+127);
        ofSetColor(c,ofRandom(255));
        ofDrawBox(x[i],y[i],z[i],boxSize);//i番目のボックスを描画
    }
    
    ofPopMatrix();//以前の座標系を復元
    cam.end();//カメラ終了
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key=='f'){//もしキーボードで'f'を入力したとき
        ofToggleFullscreen();//画面をフルスクリーンモードにする。
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
