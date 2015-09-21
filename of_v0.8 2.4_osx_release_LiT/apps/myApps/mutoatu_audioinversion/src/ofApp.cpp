#include "ofApp.h"

//int型の変数iを宣言
int i;

//rgb
int r = 0;
int g = 0;
int b = 0;

int r_1 = 25;
int g_1 = 25;
int b_1 = 25;

int r_2 = 50;
int g_2 = 50;
int b_2 = 50;

int r_3 = 75;
int g_3 = 75;
int b_3 = 75;

int r_4 = 100;
int g_4 = 100;
int b_4 = 100;

int r_5 = 125;
int g_5 = 125;
int b_5 = 125;

//boxの間隔
float spacing = 200;

//position(位置の情報)
float x,y,z;

//移動速度
float movementSpeed = 0.05;

//for-cam
float cam_a = 0;
float cam_b = 0;
float cam_c = 0;
float cam_speed = 0.1;

float phase;

int camtime;
int camrooptime;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofEnableNormalizedTexCoords();
    
    ofSetVerticalSync(true); //画面の垂直同期
    ofEnableNormalizedTexCoords(); //場所のテクスチャに画像を自動調整
    ofEnableAlphaBlending(); //透明度有効化
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    // ofEnableBlendMode(OF_BLENDMODE_ADD); //加算合成にする
    
    BackgroundImage.loadImage("forof-img.jpg"); //画像をimage1として読み込む
    ofLogo.loadImage("newgadget-logo.jpg");
    
    mySound.loadSound("forlit.wav");
    //mySound.setLoop(true); //ループ再生をonに
    mySound.play(); //Sound再生
    
    soundStream.listDevices();
    soundStream.setDeviceID( 2 );
    
    ofBaseSoundInput();
    
    ofSetFrameRate(100); //更新頻度
    
    elapsedTime=0; //経過時間を初期化
    
    int bufferSize = 512; //bufferSizeを256に設定
    
    left.assign(bufferSize, 0.0); //ベクトルの大きさをbufferSize, 成分0.0とする(まずは初期化)
    
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4); //設定した引数でストリームを開始します
    
    radius = 200.0;
    
    camrooptime = 60;
}

//--------------------------------------------------------------
void ofApp::update(){
    volume = ofSoundGetSpectrum(GetPrecision); //再生中のサウンドのwav
    
    elapsedTime++; //経過時間一秒に100回count
    
    if (camtime < 5)  { phase += 0.001; radius += 0.0001; }
    else if (camtime < 10){  phase -= 0.01; radius -= 6.0;  }
    else if (camtime  < 20){  phase += 0.01; radius += 2.0;  }
    else if (camtime < 42){ phase -= 0.01; radius -= 5.0; }
    else if (camtime < 50){ radius += 15.0; }
    else if (camtime < 60){  phase -= 0.01; radius -= 6.0;  }
    //else if (ofGetElapsedTimef() < 56){ radius += 50.0; }
    
    cam.setPosition(pos.x, pos.y, 200);
    
    // 注視点の変更
    cam.lookAt(ofVec3f(ofGetWidth()/2,ofGetHeight()/2,0));
    
    //RGB乱数
    r_1=ofRandom(0, 255);
    g_1=ofRandom(0, 255);
    b_1=ofRandom(0, 255);
    
    r_2=ofRandom(0, 255);
    g_2=ofRandom(0, 255);
    b_2=ofRandom(0, 255);
    
    r_3=ofRandom(0, 255);
    g_3=ofRandom(0, 255);
    b_3=ofRandom(0, 255);
    
    r_4=ofRandom(0, 255);
    g_4=ofRandom(0, 255);
    b_4=ofRandom(0, 255);
    
    r_5=ofRandom(0, 255);
    g_5=ofRandom(0, 255);
    b_5=ofRandom(0, 255);
    
    camtime = (int)ofGetElapsedTimef()%camrooptime;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    // startCamera
    cam.begin();
    
    //ここから新Camera関連
        //半径の設定(ifで指定済)
        //float radius = 200.0;
    
        //原点を画面の中心点に
        //円の座標を三角関数を利用して計算
        pos.x = cos(phase) * radius;
        pos.y = sin(phase) * radius;
    //ここまで新Camera関連

//    ofDisableNormalizedTexCoords();
    ofEnableNormalizedTexCoords();
    //ofBackground(0, 0, 0);
    
    //背景リセット
    ofSetColor(255, 255, 255);
    
    //読み込んだ画像データを画面に描写
    //qBackgroundImage.draw(-ofGetHeight()*5,-ofGetHeight()*5,-ofGetHeight() *3,ofGetWidth()*10,ofGetHeight()*10);
    BackgroundImage.bind();
    ofFill();
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofDrawBox(ofGetHeight()*2);
    BackgroundImage.unbind();
    ofNoFill();
    ofPopMatrix();
    
    
    // ---------------音の波形を描画--------------- //
    ofSetColor(245, 58, 135);
    ofSetLineWidth(3);
    slide++; //波形をずらしていく変数をインクリメント
    if(slide==130)slide=0; //130ずれたらリセット
    ofBeginShape(); //点を結んだ集合を以下で描画
    for (unsigned int i = 0; i < left.size()-2; i++) {//左チャンネルの配列が終わるまで描画
        //第一引数はx,第二引数はy(leftの配列の値を表現)
        ofVertex(i*10, 500 -left[i+slide]*3000.0f);
    }
    ofEndShape(false); //点の集合の終わり
    
    //単位ベクトルを定数倍するための変数cloudSizeを用意しておく
    float cloudSize = ofGetWidth()/2;
    
    // startfor
    for (i = 0; i < 25 ; i++) {
    
    // positionを一時的に保存
    ofPushMatrix();
        
    //変数tに起動時間を使って絶対かぶらない値を用意する
    float t = (ofGetElapsedTimef() + i*spacing) * movementSpeed;
    
    //x方向のベクトルに対して、一連の規則性のある乱数を返す。
    x=ofSignedNoise(t, 0, 0);
    //y方向のベクトルに対して、一連の規則性のある乱数を返す。
    y=ofSignedNoise(0, 0, t);
    //z方向のベクトルに対して、一連の規則性のある乱数を返す。
    z=ofSignedNoise(0, t, 0);
    
    ofVec3f pos(x,y,z); //位置を記録するためのオブジェクト
    
    //単位ベクトルposに対して定数倍する
    pos *= cloudSize;
        pos.x = pos.x+ofGetWidth()/2;
        pos.y = pos.y+ofGetHeight()/2;
    
    //以下のベクトルを基準として座標系を変換する。
    ofTranslate(pos.x-200,pos.y-200);
//        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //cube-01
    //基準座標系からzに45度回転させる
    ofRotateX(0);
    ofRotateY(0);
    ofRotateZ(pos.z);
//    ofRotateZ(0);

    //cl
    ofSetColor(r_1, g_1, b_1);
    // ofRect(200, 200, 100, 50);
    //立方体size
    box.set(50);
    //立方体position
    //box.setPosition(x, y, z);
    //立方体のwireframeをdrow
    box.drawWireframe();
    
    ofEnableNormalizedTexCoords();
        
        //ofSetColor(r, g, b);
        if(i == 1) {
            ofSetColor(r_1, g_1, b_1);
        }else if (i == 2) {
            ofSetColor(r_2, g_2, b_2);
        }else if (i == 3) {
            ofSetColor(r_3, g_3, b_3);
        }else if (i == 4) {
            ofSetColor(r_4, g_4, b_4);
        }else if (i == 5) {
            ofSetColor(r_5, g_5, b_5);
        }
    ofLogo.bind(); //imageを側面にdraw
        
    //枠を埋める
    ofFill();
    //立方体をdraw
    ofDrawBox(50); //0*volume[0]
    
    ofLogo.unbind(); //bind()を呼び出した後は必須の項目
    
    //枠を埋める
    ofNoFill();
    //立方体をdraw
    ofDrawBox(100); //0*volume[0]
    box.drawWireframe();
    ofPopMatrix();
    
    //sphere-01
    //基準座標系からzに45度回転させる

    ofRotateX(pos.z);
//        ofRotateX(0);
        
    ofRotateY(0);
    ofRotateZ(0);
    cout << pos.z << "\n";
    //cl
    ofSetColor(r_2, g_2, b_2);
    //球体size
    sphere.set(70,5);
    //球体position
//        sphere.setPosition(480, 0, 0);
    sphere.setPosition(pos.x, pos.y, pos.z);
    //球体のwireframeをdrow
    sphere.drawWireframe();
    
    }// endfor
        
    // endCamera
     cam.end();
    
    //text
    
    //このプログラムのタイトルを出力
    //ofDrawBitmapString("myCube Media Art Course Capter3:v.0.0.1",20,20);
    
    //今のboxsizeを出力
    //ofDrawBitmapString("Now box Size:"+ofToString(volume[0]*5000), 20, 40);
    
    //今回のmovementSpeedを出力
    //ofDrawBitmapString("MovementSpeed:"+ofToString(movementSpeed), 20, 60);
    
    //ofDrawBitmapString("Timecode;"+ofToString(ofGetElapsedTimef()), 20, 80);
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float *input, int bufferSize, int nChannels){
    
    if (elapsedTime%1==0){//(/100)秒に一回波形を取得
        for (int i = 0; i < bufferSize; i++){//
            left[i]     = input[i*2]*0.5;//偶数はleftに(Lchだけ取得)
            red=ofRandom(0,255);
            green==ofRandom(0,255);
            blue==ofRandom(0,255);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {//fを押すとフルスクリーン
        ofToggleFullscreen();
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
