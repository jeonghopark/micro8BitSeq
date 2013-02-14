#include "myApp.h"

ofVec2f tempoLineOnOff, tempoLineSize;
int tempoLineDefaultLength;
ofVec2f mousePos, mouseDraggedPos, mouseClickPos, mouseReleasePos;
ofVec2f preMousePosition;
ofVec2f mousePosition;

float distMouseSize, distMouseOnOff;

bool mouseButton;
bool mouseRelease;


ofVec2f setSizePosition, setOnOffPosition;

int firstLineDefaultLength;

float tempoLength;

float postionPitchLine;

int pitchIndex;

float pitchHigh;

string fileName = "bell_sample_01.wav";

int speed;

float hightVolume;

//--------------------------------------------------------------
void myApp::setup(){
//    ofSetDataPathRoot("../Resources/");
    
    ofBackground(20);
    ofSetFrameRate(30);
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofNoFill();
    
    ofEnableAlphaBlending();
    ofSetCircleResolution(24);
    
    mouseButton = false;

    tempoLineDefaultLength = 400;
    tempoLineOnOff = ofVec2f(-tempoLineDefaultLength/2+ofGetWidth()/2, ofGetHeight()/2);
    tempoLineSize = ofVec2f(tempoLineDefaultLength/2+ofGetWidth()/2, ofGetHeight()/2);
    
    firstLine = new PitchLine;
    secondLine = new PitchLine;
    thirdLine = new PitchLine;
    forthLine = new PitchLine;
    fifthLine = new PitchLine;
    sixthLine = new PitchLine;
    seventhLine = new PitchLine;
    eighthLine = new PitchLine;

    // !!!: new Sound player - sample player
    
    hightVolume = 0.3;

    
    piano1.loadSound(fileName);
    piano1.setVolume(hightVolume);
    piano1.setMultiPlay(true);
    piano2.loadSound(fileName);
    piano2.setVolume(hightVolume);
    piano2.setMultiPlay(true);
    piano3.loadSound(fileName);
    piano3.setVolume(hightVolume);
    piano3.setMultiPlay(true);
    piano4.loadSound(fileName);
    piano4.setVolume(hightVolume);
    piano4.setMultiPlay(true);
    piano5.loadSound(fileName);
    piano5.setVolume(hightVolume);
    piano5.setMultiPlay(true);
    piano6.loadSound(fileName);
    piano6.setVolume(hightVolume);
    piano6.setMultiPlay(true);
    piano7.loadSound(fileName);
    piano7.setVolume(hightVolume);
    piano7.setMultiPlay(true);
    piano8.loadSound(fileName);
    piano8.setVolume(hightVolume);
    piano8.setMultiPlay(true);
    
    pitchIndex = -1;
    
    pitchHigh = 7.0;
    
    speed = 5;
    
}

//--------------------------------------------------------------
void myApp::update(){
    ofSoundUpdate();

    mousePosition = ofVec2f(ofGetMouseX(),ofGetMouseY());
    
    if (ofGetFrameNum()%speed==0) {
        pitchIndex = pitchIndex + 1;
    }
    
    if (pitchIndex>7) {
        pitchIndex = 0;
    }
    
    cout << pitchIndex << endl;
 
}

//--------------------------------------------------------------
void myApp::draw(){
    
    ofPushStyle();
    distMouseSize = tempoLineSize.distance(mousePosition);
    if ((distMouseSize<8)&&(mouseButton==true)) {
        ofSetColor(255, 255);
        tempoLineSize = ofVec2f(mousePosition.x, ofGetHeight()/2);
        tempoLineOnOff = tempoLineSize-ofVec2f((-ofGetWidth()/2+mousePosition.x)*2, 0);
    } else {
        ofSetColor(255, 100);
        tempoLineSize = tempoLineSize;
        tempoLineOnOff = tempoLineOnOff;
    }
    ofRect(tempoLineOnOff, 10, 10);
    ofCircle(tempoLineSize, 6);
    ofLine(tempoLineOnOff, tempoLineSize);
    ofPopStyle();

    tempoLength = tempoLineOnOff.distance(tempoLineSize);

    ofPushMatrix();
    float postionPitchLine1 = (tempoLineOnOff.x+tempoLength*1/10+tempoLength*1/20);
    ofTranslate(postionPitchLine1, ofGetHeight()/2);
    firstLine->_positionPitchLine = postionPitchLine1;
    firstLine->mouseButton = mouseButton;
    firstLine->mousePosition = mousePosition;
    firstLine->drawing();

    if (pitchIndex==0) {
        firstLine->trigger = true;
    } else {
        firstLine->trigger = false;
    }

    if (firstLine->signalOnOff) {
        piano1.setVolume(0.0);
    } else {
        piano1.setVolume(hightVolume);
    }
        
    if (ofGetFrameNum()%(speed*8)==(speed*0)) {
        piano1.play();
        piano1.setSpeed(ofMap(firstLine->lineSize.y, 0, 300, pitchHigh, 0));
    }
    
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine2 = (tempoLineOnOff.x+tempoLength*2/10+tempoLength*1/20);
    ofTranslate(postionPitchLine2, ofGetHeight()/2);
    secondLine->_positionPitchLine = postionPitchLine2;
    secondLine->mouseButton = mouseButton;
    secondLine->mousePosition = mousePosition;
    secondLine->drawing();
    if (pitchIndex==1) {
        secondLine->trigger = true;
    } else {
        secondLine->trigger = false;
    }

    if (secondLine->signalOnOff) {
        piano2.setVolume(0.0);
    } else {
        piano2.setVolume(hightVolume);
    }
    
    if (ofGetFrameNum()%(speed*8)==(speed*1)) {
        piano2.play();
        piano2.setSpeed(ofMap(secondLine->lineSize.y, 0, 300, pitchHigh, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine3 = (tempoLineOnOff.x+tempoLength*3/10+tempoLength*1/20);
    ofTranslate(postionPitchLine3, ofGetHeight()/2);
    thirdLine->_positionPitchLine = postionPitchLine3;
    thirdLine->mouseButton = mouseButton;
    thirdLine->mousePosition = mousePosition;
    thirdLine->drawing();
    if (pitchIndex==2) {
        thirdLine->trigger = true;
    } else {
        thirdLine->trigger = false;
    }

    if (thirdLine->signalOnOff) {
        piano3.setVolume(0.0);
    } else {
        piano3.setVolume(hightVolume);
    }
    
    if (ofGetFrameNum()%(speed*8)==(speed*2)) {
        piano3.play();
        piano3.setSpeed(ofMap(thirdLine->lineSize.y, 0, 300, pitchHigh, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine4 = (tempoLineOnOff.x+tempoLength*4/10+tempoLength*1/20);
    ofTranslate(postionPitchLine4, ofGetHeight()/2);
    forthLine->_positionPitchLine = postionPitchLine4;
    forthLine->mouseButton = mouseButton;
    forthLine->mousePosition = mousePosition;
    forthLine->drawing();
    if (pitchIndex==3) {
        forthLine->trigger = true;
    } else {
        forthLine->trigger = false;
    }

    if (forthLine->signalOnOff) {
        piano4.setVolume(0.0);
    } else {
        piano4.setVolume(hightVolume);
    }
    
    if (ofGetFrameNum()%(speed*8)==(speed*3)) {
        piano4.play();
        piano4.setSpeed(ofMap(forthLine->lineSize.y, 0, 300, pitchHigh, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine5 = (tempoLineOnOff.x+tempoLength*5/10+tempoLength*1/20);
    ofTranslate(postionPitchLine5, ofGetHeight()/2);
    fifthLine->_positionPitchLine = postionPitchLine5;
    fifthLine->mouseButton = mouseButton;
    fifthLine->mousePosition = mousePosition;
    fifthLine->drawing();
    if (pitchIndex==4) {
        fifthLine->trigger = true;
    } else {
        fifthLine->trigger = false;
    }

    if (fifthLine->signalOnOff) {
        piano5.setVolume(0.0);
    } else {
        piano5.setVolume(hightVolume);
    }

    if (ofGetFrameNum()%(speed*8)==(speed*4)) {
        piano5.play();
        piano5.setSpeed(ofMap(fifthLine->lineSize.y, 0, 300, pitchHigh, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine6 = (tempoLineOnOff.x+tempoLength*6/10+tempoLength*1/20);
    ofTranslate(postionPitchLine6, ofGetHeight()/2);
    sixthLine->_positionPitchLine = postionPitchLine6;
    sixthLine->mouseButton = mouseButton;
    sixthLine->mousePosition = mousePosition;
    sixthLine->drawing();
    if (pitchIndex==5) {
        sixthLine->trigger = true;
    } else {
        sixthLine->trigger = false;
    }

    if (sixthLine->signalOnOff) {
        piano6.setVolume(0.0);
    } else {
        piano6.setVolume(hightVolume);
    }
    if (ofGetFrameNum()%(speed*8)==(speed*5)) {
        piano6.play();
        piano6.setSpeed(ofMap(sixthLine->lineSize.y, 0, 300, pitchHigh, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine7 = (tempoLineOnOff.x+tempoLength*7/10+tempoLength*1/20);
    ofTranslate(postionPitchLine7, ofGetHeight()/2);
    seventhLine->_positionPitchLine = postionPitchLine7;
    seventhLine->mouseButton = mouseButton;
    seventhLine->mousePosition = mousePosition;
    seventhLine->drawing();
    if (pitchIndex==6) {
        seventhLine->trigger = true;
    } else {
        seventhLine->trigger = false;
    }

    if (seventhLine->signalOnOff) {
        piano7.setVolume(0.0);
    } else {
        piano7.setVolume(hightVolume);
    }
    if (ofGetFrameNum()%(speed*8)==(speed*6)) {
        piano7.play();
        piano7.setSpeed(ofMap(seventhLine->lineSize.y, 0, 300, pitchHigh, 0));
    }
    ofPopMatrix();

    ofPushMatrix();
    float postionPitchLine8 = (tempoLineOnOff.x+tempoLength*8/10+tempoLength*1/20);
    ofTranslate(postionPitchLine8, ofGetHeight()/2);
    eighthLine->_positionPitchLine = postionPitchLine8;
    eighthLine->mouseButton = mouseButton;
    eighthLine->mousePosition = mousePosition;
    eighthLine->drawing();
    if (pitchIndex==7) {
        eighthLine->trigger = true;
    } else {
        eighthLine->trigger = false;
    }

    if (eighthLine->signalOnOff) {
        piano8.setVolume(0.0);
    } else {
        piano8.setVolume(hightVolume);
    }
    if (ofGetFrameNum()%(speed*8)==(speed*7)) {
        piano8.play();
        piano8.setSpeed(ofMap(eighthLine->lineSize.y, 0, 300, pitchHigh, 0));
    }
    ofPopMatrix();

}




//--------------------------------------------------------------
bool myApp::toggle(bool b) {
    if (b) {
        return false;
    } else {
        return true;
    }
}


//--------------------------------------------------------------
void myApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void myApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void myApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void myApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void myApp::mousePressed(int x, int y, int button){
    if (button==0) {
        mouseButton = true;
    }
}

//--------------------------------------------------------------
void myApp::mouseReleased(int x, int y, int button){
    if (button==0) {
        mouseButton = false;
    } 
}

//--------------------------------------------------------------
void myApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void myApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void myApp::dragEvent(ofDragInfo dragInfo){
    
}